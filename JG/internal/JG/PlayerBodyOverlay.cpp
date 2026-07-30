#include "PlayerBodyOverlay.hpp"

#include "Bethesda/BSExtraData.hpp"
#include "Bethesda/TESMain.hpp"
#include "netimmerse.h"
#include "utility.h"
#include "shared/SafeWrite/SafeWrite.hpp"

#include <GameObjects.h>
#include <decoding.h>

#include <Windows.h>
#include <cstddef>
#include <cmath>
#include <cstring>

namespace PlayerBodyOverlay {
namespace {

	constexpr uint32_t kNiFlagHidden		= 0x00000001;
	constexpr uint32_t kNiFlagNotVisible	= 0x00100000;
	constexpr uint32_t kNiFlagSkipDraw		= kNiFlagHidden | kNiFlagNotVisible;

	constexpr uint32_t kVtblNiTriStrips		= 0x109CD44;
	constexpr uint32_t kVtblNiTriShape		= 0x109D454;
	constexpr uint32_t kVtblNiGeometry		= 0x109E04C;
	constexpr uint32_t kVtblBSResizable		= 0x109E704;
	constexpr uint32_t kVtblBSSegmented		= 0x109E834;

	constexpr uint32_t kVtblBSDismemberSkin		= 0x1069A84;
	constexpr uint32_t kVtblBSShaderPPLighting	= 0x10AE0D0;
	constexpr uint32_t kVtblLighting30Shader	= 0x10B9910;
	constexpr uint32_t kVtblHairShaderProperty	= 0x10BABF8;

	constexpr uint32_t kOffDismember_NumParts	= 0x34;
	constexpr uint32_t kOffDismember_Parts		= 0x38;
	constexpr uint32_t kOffDismember_Visible	= 0x3C;
	constexpr uint32_t kOffShader_RefractionPower = 0xE0;

	constexpr uint32_t kShaderFlag1_Refraction		= 1u << 15;
	constexpr uint32_t kShaderFlag1_FireRefraction	= 1u << 16;
	constexpr uint32_t kShaderFlag2_RefractionTint	= 1u << (36 - 32);
	constexpr uint32_t kShaderFlag2_FirstPerson		= 1u << (38 - 32);
	constexpr uintptr_t kAddrSetAccumulator			= 0xB54AC0;
	constexpr uintptr_t kAddrSetCurrentAccumulator	= 0xB54B10;

	static_assert(sizeof(BSExtraData) == 0xC);
	static_assert(sizeof(NiAVObject) == 0x9C);
	static_assert(offsetof(NiAVObject, m_uiFlags) == 0x30);
	static_assert(offsetof(NiAVObject, m_kWorld) == 0x68);
	static_assert(sizeof(NiNode) == 0xAC);
	static_assert(sizeof(NiGeometry) == 0xC4);
	static_assert(offsetof(NiGeometry, shaderProp) == 0xA8);
	static_assert(offsetof(NiGeometry, unkBC) == 0xBC);
	static_assert(sizeof(BSShaderProperty) == 0x60);
	static_assert(offsetof(BSShaderProperty, ulFlags) == 0x20);
	static_assert(offsetof(BSShaderProperty, iLastRenderPassState) == 0x38);
	static_assert(sizeof(BSShaderAccumulator) == 0x280);
	static_assert(offsetof(BSShaderAccumulator, bIs1stPerson) == 0x85);
	static_assert(sizeof(TESMain) == 0xA4);
	static_assert(offsetof(TESMain, spDraw1stPersonAccum) == 0x8C);

	bool g_hooksInstalled = false;
	bool g_hooksOk = false;
	volatile LONG g_enabled = 0;
	volatile LONG g_partMode = 0;
	volatile LONG g_partBits = 0;
	volatile LONG g_disableSuppressFrames = 10;
	volatile LONG g_disableSuppressFrameBudget = 0;

	struct ExtraRefractionPropertyView : BSExtraData {
		float fRefractionAmount;
	};
	static_assert(sizeof(ExtraRefractionPropertyView) == 0x10);
	static_assert(offsetof(ExtraRefractionPropertyView, fRefractionAmount) == 0xC);

	NiNode* GetPlayerBodyRootFast() {
		__try {
			PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
			NiNode* pBody3p = pPlayer ? pPlayer->Get3DSimple() : nullptr;
			if (!pBody3p)
				return nullptr;
			(void)pBody3p->m_uiFlags.GetField(); // probe read so a dead pointer faults here instead of mid render
			return pBody3p;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}

	bool PlayerHasActiveRefraction(float* apRefractionOut) {
		float fRefraction = 0.0f;
		__try {
			PlayerCharacter* pPlayer = PlayerCharacter::GetSingleton();
			BSExtraData* pExtra = pPlayer
				? pPlayer->extraDataList.GetExtraData(EXTRA_DATA_TYPE::ExtraRefractionProperty)
				: nullptr;
			if (pExtra)
				fRefraction = reinterpret_cast<ExtraRefractionPropertyView*>(pExtra)->fRefractionAmount;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			fRefraction = 0.0f;
		}
		if (apRefractionOut)
			*apRefractionOut = fRefraction;
		return std::isfinite(fRefraction) && fRefraction > 0.0f;
	}

	bool IsBodyLeafGeometry(NiAVObject* apObject) {
		// IsGeometry also accepts particles. Exact types only.
		const uint32_t uiVtbl = static_cast<uint32_t>(
			reinterpret_cast<uintptr_t>(*reinterpret_cast<void**>(apObject)));
		return uiVtbl == kVtblNiTriStrips ||
		       uiVtbl == kVtblNiTriShape ||
		       uiVtbl == kVtblNiGeometry ||
		       uiVtbl == kVtblBSResizable ||
		       uiVtbl == kVtblBSSegmented;
	}

	const char* const kNonBodyGeomTokens[] = {
		"head", "hair", "eye", "brow", "mouth", "teeth", "tongue",
		"lash", "hat", "helm", "glasses", "mask", "beard", "stache",
		"facegen", "glove", "hand", "arms01",
		"glow", "shadow", "emit",
		"bloodcap",
		"pipboy",
	};

	bool IsNonBodyGeom(NiAVObject* apObject) {
		const char* pName = apObject->GetName();
		if (!pName)
			return false;
		for (const char* pToken : kNonBodyGeomTokens)
			if (SubStr(pName, pToken))
				return true;
		return false;
	}

	const char* const kPruneNodeTokens[] = {
		"hair",
		"earrings",
		"facegen",
		"clavicle",
		"lefthand",
		"righthand",
		"weapon",
		"##nm",
		"projectilenode",
		"shellcasingnode",
		"ingestible",
		"b42grb",
		"b42attach",
		"backpack",
		"pauldron",
		"camera3rd",
		"bnb",
		"pipboy",
	};

	bool IsPrunedNode(NiAVObject* apObject) {
		const char* pName = apObject->GetName();
		if (!pName)
			return false;
		for (const char* pToken : kPruneNodeTokens)
			if (SubStr(pName, pToken))
				return true;
		return false;
	}

	void RegisterBodyGeometry(NiAVObject* apObject, BSShaderAccumulator* apAccum, uint32_t auiDepth) {
		if (!apObject || auiDepth > 64)
			return;
		const uint32_t uiFlags = apObject->m_uiFlags.GetField();
		const bool bIsGeom = IsBodyLeafGeometry(apObject);
		const bool bCulled = (uiFlags & kNiFlagSkipDraw) != 0;

		if (bIsGeom) {
			if (!bCulled && !IsNonBodyGeom(apObject))
				apAccum->RegisterObject(static_cast<NiGeometry*>(apObject));
			return;
		}
		NiNode* pNode = apObject->IsNode();
		if (!pNode)
			return;
		if (bCulled || IsPrunedNode(pNode))
			return;
		const uint32_t uiChildCount = pNode->GetArrayCount();
		if (uiChildCount > 1024)
			return;
		for (uint32_t i = 0; i < uiChildCount; ++i)
			if (NiAVObject* pChild = pNode->GetAt(i))
				RegisterBodyGeometry(pChild, apAccum, auiDepth + 1);
	}

	bool RegisterBodyGuarded(NiNode* apBody3p, BSShaderAccumulator* apAccum) {
		__try {
			RegisterBodyGeometry(apBody3p, apAccum, 0);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
		return true;
	}

	struct TransformBackup {
		NiAVObject*	pObject;
		NiMatrix3	kWorldRotate;
		NiPoint3	kWorldTranslate;
	};

	struct DismemberPartition {
		uint8_t		ucEnabled;
		uint8_t		ucStateChange;
		uint16_t	usBodyPart;
	};
	static_assert(sizeof(DismemberPartition) == 4);

	struct PartitionBackup {
		DismemberPartition*	pPartition;
		uint8_t				ucSavedEnabled;
		uint8_t*			pVisible;
		uint8_t				ucSavedVisible;
	};

	struct FlagBackup {
		uint32_t*	pFlags;
		uint32_t	uiSavedFlags;
	};

	struct ShaderBackup {
		BSShaderProperty*	pShader;
		uint32_t			uiSavedFlags1;
		uint32_t			uiSavedFlags2;
		float				fSavedRefractionPower;
	};

	constexpr uint32_t kTransformMax	= 1024;
	constexpr uint32_t kPartitionMax	= 256;
	constexpr uint32_t kFlagMax			= 512;
	constexpr uint32_t kShaderMax		= 128;

	// Do not zero these arrays. This runs on the render path.
	struct InjectionState {
		bool* pIs1stPerson = nullptr;
		bool bSavedIs1stPerson = false;
		TransformBackup kTransforms[kTransformMax];
		PartitionBackup kPartitions[kPartitionMax];
		ShaderBackup kShaders[kShaderMax];
		uint32_t uiTransformCount = 0;
		uint32_t uiPartitionCount = 0;
		uint32_t uiShaderCount = 0;
		bool bActive = false;
	};

	bool IsFinitePoint(const NiPoint3& arPoint) {
		return std::isfinite(arPoint.x) && std::isfinite(arPoint.y) && std::isfinite(arPoint.z);
	}

	bool IsFiniteMatrix(const NiMatrix3& arMatrix) {
		for (uint32_t i = 0; i < 3; ++i)
			for (uint32_t j = 0; j < 3; ++j)
				if (!std::isfinite(arMatrix.m_pEntry[i][j]))
					return false;
		return true;
	}

	bool TryReadWorldTranslate(NiAVObject* apObject, NiPoint3& arOut) {
		if (!apObject)
			return false;
		__try {
			arOut = apObject->m_kWorld.m_kTranslate;
			return IsFinitePoint(arOut);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	bool TryReadWorldTransform(NiAVObject* apObject, NiPoint3& arOutTranslate, NiMatrix3& arOutRotate) {
		if (!apObject)
			return false;
		__try {
			arOutRotate = apObject->m_kWorld.m_kRotate;
			arOutTranslate = apObject->m_kWorld.m_kTranslate;
			return IsFinitePoint(arOutTranslate) && IsFiniteMatrix(arOutRotate);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	bool NormalizePoint(NiPoint3& arP) {
		if (!IsFinitePoint(arP))
			return false;
		const double fLenSq =
			static_cast<double>(arP.x) * arP.x +
			static_cast<double>(arP.y) * arP.y +
			static_cast<double>(arP.z) * arP.z;
		if (!std::isfinite(fLenSq) || fLenSq < 0.000001)
			return false;
		const float fInvLen = static_cast<float>(1.0 / std::sqrt(fLenSq));
		arP.x *= fInvLen;
		arP.y *= fInvLen;
		arP.z *= fInvLen;
		return true;
	}

	// dir = col 0, right = col 2
	bool CameraPitchDeltaMatrix(const NiMatrix3& arCamRot, NiMatrix3& arOut) {
		NiPoint3 kCamDir = arCamRot.GetCol(0);
		NiPoint3 kCamRight = arCamRot.GetCol(2);
		if (!NormalizePoint(kCamDir) || !NormalizePoint(kCamRight))
			return false;

		NiPoint3 kFlatDir(kCamDir.x, kCamDir.y, 0.0f);
		if (!NormalizePoint(kFlatDir))
			return false;

		const float fSin = kFlatDir.Cross(kCamDir).Dot(kCamRight);
		const float fCos = kFlatDir.Dot(kCamDir);
		const float fAngle = std::atan2(fSin, fCos);
		if (!std::isfinite(fAngle) || std::fabs(fAngle) < 0.000001f)
			return false;

		// MakeRotation builds the transpose of what this math wants, hence the negated angle
		arOut.MakeRotation(-fAngle, kCamRight);
		return true;
	}

	void RestoreTransforms(TransformBackup* apBackups, uint32_t auiCount) {
		__try {
			while (auiCount) {
				--auiCount;
				if (NiAVObject* pObject = apBackups[auiCount].pObject) {
					pObject->m_kWorld.m_kRotate = apBackups[auiCount].kWorldRotate;
					pObject->m_kWorld.m_kTranslate = apBackups[auiCount].kWorldTranslate;
				}
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}

	bool TransformObjectTree(NiAVObject* apObject, const NiPoint3& arDelta,
			const NiPoint3& arRotateSourcePivot, const NiPoint3& arRotateTargetPivot,
			const NiMatrix3& arCameraDeltaRot, bool abRotateWithCamera,
			TransformBackup* apBackups, uint32_t auiMax, uint32_t& arCount, uint32_t auiDepth) {
		if (!apObject || auiDepth > 64)
			return true;

		const bool bIsGeom = IsBodyLeafGeometry(apObject);
		NiNode* pNode = bIsGeom ? nullptr : apObject->IsNode();
		if (!bIsGeom && !pNode)
			return true;

		if (arCount >= auiMax)
			return false;

		NiTransform& rWorld = apObject->m_kWorld;
		apBackups[arCount].pObject = apObject;
		apBackups[arCount].kWorldRotate = rWorld.m_kRotate;
		apBackups[arCount].kWorldTranslate = rWorld.m_kTranslate;
		++arCount;

		if (abRotateWithCamera) {
			const NiPoint3 kRel = rWorld.m_kTranslate - arRotateSourcePivot;
			rWorld.m_kTranslate = arRotateTargetPivot + arCameraDeltaRot * kRel;
			rWorld.m_kRotate = arCameraDeltaRot * rWorld.m_kRotate;
		} else {
			rWorld.m_kTranslate += arDelta;
		}

		if (!pNode)
			return true;
		const uint32_t uiChildCount = pNode->GetArrayCount();
		if (uiChildCount > 1024)
			return true;
		for (uint32_t i = 0; i < uiChildCount; ++i)
			if (NiAVObject* pChild = pNode->GetAt(i))
				if (!TransformObjectTree(pChild, arDelta,
						arRotateSourcePivot, arRotateTargetPivot,
						arCameraDeltaRot, abRotateWithCamera, apBackups, auiMax, arCount, auiDepth + 1))
					return false;
		return true;
	}

	bool ApplyTransformsGuarded(NiNode* apBody3p, const NiPoint3& arDelta,
			const NiPoint3& arRotateSourcePivot, const NiPoint3& arRotateTargetPivot,
			const NiMatrix3& arCameraDeltaRot, bool abRotateWithCamera,
			TransformBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		arCount = 0;
		if (!abRotateWithCamera && arDelta.SqrLength() < 0.0001f)
			return true;

		bool bOk = false;
		__try {
			bOk = TransformObjectTree(apBody3p, arDelta,
				arRotateSourcePivot, arRotateTargetPivot,
				arCameraDeltaRot, abRotateWithCamera, apBackups, auiMax, arCount, 0);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			bOk = false;
		}
		if (!bOk)
			RestoreTransforms(apBackups, arCount);
		return bOk;
	}

	uint16_t NormalizeBodyPart(uint16_t ausBodyPart) {
		if (ausBodyPart >= 1000 && (ausBodyPart % 1000) == 0)
			return ausBodyPart / 1000;
		if (ausBodyPart >= 100 && ausBodyPart < 1000)
			return ausBodyPart % 100; // caps fold onto the base part
		return ausBodyPart;
	}

	uint32_t PartBit(uint16_t ausBodyPart) {
		const uint16_t usPart = NormalizeBodyPart(ausBodyPart);
		return usPart < 32 ? (1u << usPart) : 0;
	}

	struct CullConfig {
		LONG iPartMode;
		LONG iPartBits;
	};

	CullConfig GetCullConfig() {
		CullConfig kConfig;
		kConfig.iPartMode = g_partMode;
		kConfig.iPartBits = g_partBits;
		return kConfig;
	}

	bool IsKeptPart(uint16_t ausBodyPart, const CullConfig& arConfig) {
		const uint32_t uiBit = PartBit(ausBodyPart);
		if (arConfig.iPartMode == 2)
			return !(uiBit && (static_cast<uint32_t>(arConfig.iPartBits) & uiBit));
		return uiBit && (static_cast<uint32_t>(arConfig.iPartBits) & uiBit);
	}

	bool RecomputeDismemberVisible(uint8_t* apSkin) {
		uint32_t uiNumParts = *reinterpret_cast<uint32_t*>(apSkin + kOffDismember_NumParts);
		DismemberPartition* pParts = *reinterpret_cast<DismemberPartition**>(apSkin + kOffDismember_Parts);
		if (!pParts || uiNumParts > 128)
			return false;

		uint8_t ucVisible = 0;
		for (uint32_t i = 0; i < uiNumParts; ++i)
			ucVisible |= pParts[i].ucEnabled ? 1 : 0;
		*(apSkin + kOffDismember_Visible) = ucVisible;
		return true;
	}

	bool CullPartitionsForGeom(NiGeometry* apGeom, const CullConfig& arConfig,
			PartitionBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		// unkBC is the skin instance slot
		uint8_t* pSkin = reinterpret_cast<uint8_t*>(apGeom->unkBC);
		if (!pSkin || static_cast<uint32_t>(reinterpret_cast<uintptr_t>(
				*reinterpret_cast<void**>(pSkin))) != kVtblBSDismemberSkin)
			return true;

		uint32_t uiNumParts = *reinterpret_cast<uint32_t*>(pSkin + kOffDismember_NumParts);
		DismemberPartition* pParts = *reinterpret_cast<DismemberPartition**>(pSkin + kOffDismember_Parts);
		uint8_t* pVisible = pSkin + kOffDismember_Visible;
		if (!pParts || uiNumParts > 128)
			return true;

		for (uint32_t i = 0; i < uiNumParts; ++i) {
			if (!pParts[i].ucEnabled || IsKeptPart(pParts[i].usBodyPart, arConfig))
				continue;
			if (arCount >= auiMax)
				return false;
			apBackups[arCount].pPartition = &pParts[i];
			apBackups[arCount].ucSavedEnabled = pParts[i].ucEnabled;
			apBackups[arCount].pVisible = pVisible;
			apBackups[arCount].ucSavedVisible = *pVisible;
			++arCount;
			pParts[i].ucEnabled = 0;
		}
		return RecomputeDismemberVisible(pSkin);
	}

	void RestorePartitions(PartitionBackup* apBackups, uint32_t auiCount) {
		__try {
			while (auiCount) {
				--auiCount;
				if (apBackups[auiCount].pPartition)
					apBackups[auiCount].pPartition->ucEnabled = apBackups[auiCount].ucSavedEnabled;
				if (apBackups[auiCount].pVisible)
					*apBackups[auiCount].pVisible = apBackups[auiCount].ucSavedVisible;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}

	void RestoreFlags(FlagBackup* apBackups, uint32_t auiCount) {
		__try {
			while (auiCount) {
				--auiCount;
				if (apBackups[auiCount].pFlags)
					*apBackups[auiCount].pFlags = apBackups[auiCount].uiSavedFlags;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}

	bool HidePreviewObject(NiAVObject* apObject, FlagBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		uint32_t& rFlags = apObject->m_uiFlags.GetField();
		const uint32_t uiSaved = rFlags;
		if (uiSaved & kNiFlagSkipDraw)
			return true;
		if (arCount >= auiMax)
			return false;
		apBackups[arCount].pFlags = &rFlags;
		apBackups[arCount].uiSavedFlags = uiSaved;
		++arCount;
		rFlags = uiSaved | kNiFlagSkipDraw;
		return true;
	}

	bool CullTree(NiAVObject* apObject, const CullConfig& arConfig,
			PartitionBackup* apPartitionBackups, uint32_t auiMaxPartitions, uint32_t& arPartitionCount,
			FlagBackup* apFlagBackups, uint32_t auiMaxFlags, uint32_t& arFlagCount, uint32_t auiDepth) {
		if (!apObject || auiDepth > 64)
			return true;

		const bool bIsGeom = IsBodyLeafGeometry(apObject);
		NiNode* pNode = bIsGeom ? nullptr : apObject->IsNode();
		if (bIsGeom) {
			NiGeometry* pGeom = static_cast<NiGeometry*>(apObject);
			if (!CullPartitionsForGeom(pGeom, arConfig, apPartitionBackups, auiMaxPartitions, arPartitionCount))
				return false;
			return (apFlagBackups && arConfig.iPartMode == 1 && IsNonBodyGeom(apObject))
				? HidePreviewObject(apObject, apFlagBackups, auiMaxFlags, arFlagCount)
				: true;
		}
		if (!pNode)
			return true;

		if (IsPrunedNode(pNode)) {
			return (apFlagBackups && arConfig.iPartMode == 1)
				? HidePreviewObject(pNode, apFlagBackups, auiMaxFlags, arFlagCount)
				: true;
		}

		const uint32_t uiChildCount = pNode->GetArrayCount();
		if (uiChildCount > 1024)
			return true;
		for (uint32_t i = 0; i < uiChildCount; ++i)
			if (NiAVObject* pChild = pNode->GetAt(i))
				if (!CullTree(pChild, arConfig,
						apPartitionBackups, auiMaxPartitions, arPartitionCount,
						apFlagBackups, auiMaxFlags, arFlagCount, auiDepth + 1))
					return false;
		return true;
	}

	bool CullPartitionsGuarded(NiNode* apBody3p, const CullConfig& arConfig,
			PartitionBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		arCount = 0;
		uint32_t uiUnusedFlagCount = 0;
		bool bOk = false;
		__try {
			bOk = CullTree(apBody3p, arConfig, apBackups, auiMax, arCount,
				nullptr, 0, uiUnusedFlagCount, 0);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			bOk = false;
		}
		if (!bOk)
			RestorePartitions(apBackups, arCount);
		return bOk;
	}

	bool ApplyCullPreviewBracket(NiNode* apBody3p, const CullConfig& arConfig,
			PartitionBackup* apPartitionBackups, uint32_t auiMaxPartitions, uint32_t& arPartitionCount,
			FlagBackup* apFlagBackups, uint32_t auiMaxFlags, uint32_t& arFlagCount) {
		arPartitionCount = 0;
		arFlagCount = 0;
		if (!arConfig.iPartMode)
			return true;
		if (!apBody3p)
			return false;

		bool bOk = false;
		__try {
			bOk = CullTree(apBody3p, arConfig,
				apPartitionBackups, auiMaxPartitions, arPartitionCount,
				apFlagBackups, auiMaxFlags, arFlagCount, 0);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			bOk = false;
		}
		if (!bOk) {
			RestoreFlags(apFlagBackups, arFlagCount);
			RestorePartitions(apPartitionBackups, arPartitionCount);
			arPartitionCount = 0;
			arFlagCount = 0;
		}
		return bOk;
	}

	bool IsRefractionShader(BSShaderProperty* apShader) {
		if (!apShader)
			return false;
		const uint32_t uiVtbl = static_cast<uint32_t>(
			reinterpret_cast<uintptr_t>(*reinterpret_cast<void**>(apShader)));
		return uiVtbl == kVtblBSShaderPPLighting ||
		       uiVtbl == kVtblLighting30Shader ||
		       uiVtbl == kVtblHairShaderProperty;
	}

	bool HasShaderBackup(const ShaderBackup* apBackups, uint32_t auiCount, BSShaderProperty* apShader) {
		for (uint32_t i = 0; i < auiCount; ++i)
			if (apBackups[i].pShader == apShader)
				return true;
		return false;
	}

	bool PatchRefractionShaderForGeom(NiGeometry* apGeom, float afRefraction,
			ShaderBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		BSShaderProperty* pShader = apGeom->shaderProp;
		if (!IsRefractionShader(pShader))
			return true;
		if (HasShaderBackup(apBackups, arCount, pShader))
			return true;
		if (arCount >= auiMax)
			return false;

		uint32_t& rFlags1 = pShader->ulFlags[0].GetField();
		uint32_t& rFlags2 = pShader->ulFlags[1].GetField();
		float* pRefractionPower = reinterpret_cast<float*>(
			reinterpret_cast<uint8_t*>(pShader) + kOffShader_RefractionPower);

		apBackups[arCount].pShader = pShader;
		apBackups[arCount].uiSavedFlags1 = rFlags1;
		apBackups[arCount].uiSavedFlags2 = rFlags2;
		apBackups[arCount].fSavedRefractionPower = *pRefractionPower;
		++arCount;

		rFlags1 = (rFlags1 | kShaderFlag1_Refraction) & ~kShaderFlag1_FireRefraction;
		rFlags2 = (rFlags2 & ~kShaderFlag2_RefractionTint) | kShaderFlag2_FirstPerson;
		*pRefractionPower = afRefraction;
		pShader->InvalidateState();
		return true;
	}

	bool PatchRefractionTree(NiAVObject* apObject, float afRefraction,
			ShaderBackup* apBackups, uint32_t auiMax, uint32_t& arCount, uint32_t auiDepth) {
		if (!apObject || auiDepth > 64)
			return true;

		const uint32_t uiFlags = apObject->m_uiFlags.GetField();
		const bool bIsGeom = IsBodyLeafGeometry(apObject);
		NiNode* pNode = bIsGeom ? nullptr : apObject->IsNode();
		const bool bCulled = (uiFlags & kNiFlagSkipDraw) != 0;

		if (bIsGeom) {
			if (bCulled || IsNonBodyGeom(apObject))
				return true;
			return PatchRefractionShaderForGeom(static_cast<NiGeometry*>(apObject),
				afRefraction, apBackups, auiMax, arCount);
		}
		if (!pNode)
			return true;
		if (bCulled || IsPrunedNode(pNode))
			return true;

		const uint32_t uiChildCount = pNode->GetArrayCount();
		if (uiChildCount > 1024)
			return true;
		for (uint32_t i = 0; i < uiChildCount; ++i)
			if (NiAVObject* pChild = pNode->GetAt(i))
				if (!PatchRefractionTree(pChild, afRefraction, apBackups, auiMax, arCount, auiDepth + 1))
					return false;
		return true;
	}

	void RestoreShaders(ShaderBackup* apBackups, uint32_t auiCount) {
		__try {
			while (auiCount) {
				--auiCount;
				BSShaderProperty* pShader = apBackups[auiCount].pShader;
				if (!pShader)
					continue;
				pShader->ulFlags[0] = apBackups[auiCount].uiSavedFlags1;
				pShader->ulFlags[1] = apBackups[auiCount].uiSavedFlags2;
				*reinterpret_cast<float*>(
					reinterpret_cast<uint8_t*>(pShader) + kOffShader_RefractionPower) =
					apBackups[auiCount].fSavedRefractionPower;
				pShader->InvalidateState();
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}

	bool PatchRefractionGuarded(NiNode* apBody3p, float afRefraction,
			ShaderBackup* apBackups, uint32_t auiMax, uint32_t& arCount) {
		arCount = 0;
		if (afRefraction <= 0.0f)
			return true;
		if (afRefraction > 1.0f)
			afRefraction = 1.0f;

		bool bOk = false;
		__try {
			bOk = PatchRefractionTree(apBody3p, afRefraction, apBackups, auiMax, arCount, 0);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			bOk = false;
		}
		if (!bOk)
			RestoreShaders(apBackups, arCount);
		return bOk;
	}

	void RestoreInjectedBody(InjectionState& arState) {
		if (!arState.bActive)
			return;
		__try {
			if (arState.uiShaderCount)
				RestoreShaders(arState.kShaders, arState.uiShaderCount);
			if (arState.uiPartitionCount)
				RestorePartitions(arState.kPartitions, arState.uiPartitionCount);
			if (arState.uiTransformCount)
				RestoreTransforms(arState.kTransforms, arState.uiTransformCount);
			if (arState.pIs1stPerson)
				*arState.pIs1stPerson = arState.bSavedIs1stPerson;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
		arState.bActive = false;
	}

	void InjectBodyIntoAccum(NiCamera* apCamera, BSShaderAccumulator* apAccum,
			InjectionState& arState, float afRefraction) {
		if (!apCamera)
			return;
		NiNode* pBody3p = GetPlayerBodyRootFast();
		if (!pBody3p)
			return;

		NiCamera* pWorldCamera = TESMain::GetWorldRootCamera();
		NiPoint3 kCamPos, kWorldCamPos;
		NiMatrix3 kCameraDeltaRot;
		NiMatrix3 kCamRot;
		const bool bHaveCamPos = TryReadWorldTransform(apCamera, kCamPos, kCamRot);
		const bool bRotateWithCamera = bHaveCamPos && CameraPitchDeltaMatrix(kCamRot, kCameraDeltaRot);
		if ((!bHaveCamPos && !TryReadWorldTranslate(apCamera, kCamPos)) ||
				!TryReadWorldTranslate(pWorldCamera, kWorldCamPos))
			return;

		// the callers finally block puts this back
		arState.pIs1stPerson = &apAccum->bIs1stPerson;
		arState.bSavedIs1stPerson = apAccum->bIs1stPerson;
		arState.bActive = true;

		apAccum->bIs1stPerson = true;
		CdeclCall(kAddrSetAccumulator, apAccum); // BSShaderManager::SetAccumulator
		CdeclCall(kAddrSetCurrentAccumulator, apAccum); // BSShaderManager::SetCurrentAccumulator
		apAccum->StartAccumulating(apCamera);

		const NiPoint3 kDelta = kCamPos - kWorldCamPos;
		if (!ApplyTransformsGuarded(pBody3p, kDelta, kWorldCamPos, kCamPos,
				kCameraDeltaRot, bRotateWithCamera,
				arState.kTransforms, kTransformMax, arState.uiTransformCount)) {
			arState.uiTransformCount = 0;
			return;
		}

		const CullConfig kConfig = GetCullConfig();
		if (kConfig.iPartMode) {
			if (!CullPartitionsGuarded(pBody3p, kConfig,
					arState.kPartitions, kPartitionMax, arState.uiPartitionCount)) {
				arState.uiPartitionCount = 0;
				return;
			}
		} else {
			arState.uiPartitionCount = 0;
		}

		if (afRefraction > 0.0f &&
				!PatchRefractionGuarded(pBody3p, afRefraction,
					arState.kShaders, kShaderMax, arState.uiShaderCount)) {
			arState.uiShaderCount = 0;
			return;
		}

		RegisterBodyGuarded(pBody3p, apAccum);
	}

	constexpr uintptr_t kAddrDrawScene		= 0x873200;
	constexpr uintptr_t kAddrRenderScene	= 0xB6C0D0;
	constexpr uintptr_t kAddrRenderNormals	= 0xB64570;

	constexpr uintptr_t kSiteWorldCull1		= 0x870AE8;	// Render::Wireframe
	constexpr uintptr_t kSiteWorldCull2		= 0x870E18;	// Render::Default
	constexpr uintptr_t kSiteRenderScene1	= 0x87550F;	// Render1stPerson
	constexpr uintptr_t kSiteRenderScene2	= 0x8755F4;	// Render1stPerson
	// Leave 0x875801 and 0x875AED alone. The overlay is single pass.
	constexpr uintptr_t kSiteRenderNormals	= 0x87590A;	// Render1stPerson

	enum HookIndex : uint32_t {
		kHookWorldCull1,
		kHookWorldCull2,
		kHookRenderScene1,
		kHookRenderScene2,
		kHookRenderNormals,
		kHookCount,
	};
	HookUtils::CallDetour g_callDetours[kHookCount];

	void RestoreBodyFlagsGuarded(uint32_t* apFlags, uint32_t auiSaved) {
		__try {
			*apFlags = auiSaved;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
		}
	}

	template <uint32_t aiHookIndex>
	void __fastcall HookedDrawScene(void* apThis, void* edx, void* apSun,
			int abRenderHands, int abIsWireframe, int abIsInVATS) {
		uint32_t* pBodyFlags = nullptr;
		uint32_t uiSaved = 0;
		PartitionBackup kPreviewPartitions[kPartitionMax];
		FlagBackup kPreviewFlags[kFlagMax];
		uint32_t uiPreviewPartitionCount = 0;
		uint32_t uiPreviewFlagCount = 0;
		const LONG iSuppressFrames = g_disableSuppressFrameBudget;
		const bool bSuppressBody = g_enabled || iSuppressFrames > 0;
		if (bSuppressBody) {
			if (NiNode* pBody3p = GetPlayerBodyRootFast()) {
				__try {
					pBodyFlags = &pBody3p->m_uiFlags.GetField();
					uiSaved = *pBodyFlags;
					*pBodyFlags = uiSaved | kNiFlagHidden;
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {
					pBodyFlags = nullptr;
				}
			}
		} else {
			const CullConfig kPreviewConfig = GetCullConfig();
			if (kPreviewConfig.iPartMode) {
				if (NiNode* pBody3p = GetPlayerBodyRootFast())
					ApplyCullPreviewBracket(pBody3p, kPreviewConfig,
						kPreviewPartitions, kPartitionMax, uiPreviewPartitionCount,
						kPreviewFlags, kFlagMax, uiPreviewFlagCount);
			}
		}
		__try {
			ThisCall(g_callDetours[aiHookIndex].GetOverwrittenAddr(),
				apThis, apSun, abRenderHands, abIsWireframe, abIsInVATS);
		}
		__finally {
			if (uiPreviewFlagCount)
				RestoreFlags(kPreviewFlags, uiPreviewFlagCount);
			if (uiPreviewPartitionCount)
				RestorePartitions(kPreviewPartitions, uiPreviewPartitionCount);
			if (iSuppressFrames > 0)
				InterlockedDecrement(&g_disableSuppressFrameBudget);
			if (pBodyFlags)
				RestoreBodyFlagsGuarded(pBodyFlags, uiSaved);
		}
	}

	// Keep this out of the hook frame. Its locals are about 60 KB.
	DECLSPEC_NOINLINE void CallWithInjectedBody(bool abRefractionPass,
			uintptr_t auiOriginalTarget, NiCamera* apCamera,
			BSShaderAccumulator* apAccum, void* apTexture) {
		InjectionState kInjected;
		float fRefraction = 0.0f;
		const bool bHasRefraction = PlayerHasActiveRefraction(&fRefraction);
		__try {
			if (bHasRefraction == abRefractionPass)
				InjectBodyIntoAccum(apCamera, apAccum, kInjected, abRefractionPass ? fRefraction : 0.0f);
			if (abRefractionPass)
				ThisCall(auiOriginalTarget, apAccum, apCamera, apTexture);
			else
				CdeclCall(auiOriginalTarget, apCamera, apAccum);
		}
		__finally {
			RestoreInjectedBody(kInjected);
		}
	}

	bool IsViewmodelAccum(BSShaderAccumulator* apAccum) {
		if (!apAccum)
			return false;
		TESMain* pMain = TESMain::GetSingleton();
		return pMain && apAccum == pMain->spDraw1stPersonAccum;
	}

	template <uint32_t aiHookIndex>
	void __cdecl HookedRenderScene(NiCamera* apCamera, BSShaderAccumulator* apAccum) {
		const uintptr_t uiOriginalTarget = g_callDetours[aiHookIndex].GetOverwrittenAddr();
		if (g_enabled && IsViewmodelAccum(apAccum)) {
			CallWithInjectedBody(false, uiOriginalTarget, apCamera, apAccum, nullptr);
			return;
		}
		CdeclCall(uiOriginalTarget, apCamera, apAccum);
	}

	template <uint32_t aiHookIndex>
	void __fastcall HookedRenderNormals(BSShaderAccumulator* apAccum, void* edx,
			NiCamera* apCamera, void* apTexture) {
		(void)edx;
		const uintptr_t uiOriginalTarget = g_callDetours[aiHookIndex].GetOverwrittenAddr();
		if (g_enabled && IsViewmodelAccum(apAccum)) {
			CallWithInjectedBody(true, uiOriginalTarget, apCamera, apAccum, apTexture);
			return;
		}
		ThisCall(uiOriginalTarget, apAccum, apCamera, apTexture);
	}

	uintptr_t ReadCallTarget(uintptr_t auiSite) {
		if (*reinterpret_cast<uint8_t*>(auiSite) != 0xE8)
			return 0;
		return *reinterpret_cast<int32_t*>(auiSite + 1) + auiSite + 5;
	}

	struct HookSite {
		uint32_t uiIndex;
		uintptr_t uiSite;
		uintptr_t uiVanillaTarget;
		void* pHook;
		const char* pName;
	};

}

void Install() {
	if (g_hooksInstalled)
		return;
	g_hooksInstalled = true;

	const HookSite kSites[] = {
		{ kHookWorldCull1, kSiteWorldCull1, kAddrDrawScene,
			reinterpret_cast<void*>(&HookedDrawScene<kHookWorldCull1>), "world-cull 0x870AE8" },
		{ kHookWorldCull2, kSiteWorldCull2, kAddrDrawScene,
			reinterpret_cast<void*>(&HookedDrawScene<kHookWorldCull2>), "world-cull 0x870E18" },
		{ kHookRenderScene1, kSiteRenderScene1, kAddrRenderScene,
			reinterpret_cast<void*>(&HookedRenderScene<kHookRenderScene1>), "viewmodel 0x87550F" },
		{ kHookRenderScene2, kSiteRenderScene2, kAddrRenderScene,
			reinterpret_cast<void*>(&HookedRenderScene<kHookRenderScene2>), "viewmodel 0x8755F4" },
		{ kHookRenderNormals, kSiteRenderNormals, kAddrRenderNormals,
			reinterpret_cast<void*>(&HookedRenderNormals<kHookRenderNormals>), "refraction 0x87590A" },
	};

	// Fail closed on any foreign hook. Chaining an unknown overlay here means double rendering.
	for (const HookSite& rSite : kSites) {
		const uintptr_t uiCurrent = ReadCallTarget(rSite.uiSite);
		if (uiCurrent != rSite.uiVanillaTarget) {
			_MESSAGE("PlayerBodyOverlay: %s already modified (target 0x%08X) - overlay disabled",
				rSite.pName, uiCurrent);
			g_hooksOk = false;
			return;
		}
	}
	for (const HookSite& rSite : kSites)
		g_callDetours[rSite.uiIndex].ReplaceCall(rSite.uiSite, rSite.pHook);
	for (const HookSite& rSite : kSites) {
		if (ReadCallTarget(rSite.uiSite) != reinterpret_cast<uintptr_t>(rSite.pHook)) {
			_MESSAGE("PlayerBodyOverlay: %s patch did not stick - overlay disabled", rSite.pName);
			g_hooksOk = false;
			return;
		}
	}

	_MESSAGE("PlayerBodyOverlay: render hooks installed (5 sites)");
	g_hooksOk = true;
}

void Reset() {
	InterlockedExchange(&g_enabled, 0);
	InterlockedExchange(&g_disableSuppressFrameBudget, 0);
	InterlockedExchange(&g_partMode, 0);
	InterlockedExchange(&g_partBits, 0);
}

int32_t SetEnabled(bool abEnable, int32_t aiDisableSuppressFrames) {
	Install();
	const LONG iPrevious = g_enabled;

	if (aiDisableSuppressFrames >= 0) {
		if (aiDisableSuppressFrames > 60)
			aiDisableSuppressFrames = 60;
		InterlockedExchange(&g_disableSuppressFrames, aiDisableSuppressFrames);
	}

	if (abEnable) {
		if (!g_hooksOk)
			return -1;
		InterlockedExchange(&g_enabled, 1);
		InterlockedExchange(&g_disableSuppressFrameBudget, 0);
	} else {
		InterlockedExchange(&g_enabled, 0);
		if (iPrevious)
			InterlockedExchange(&g_disableSuppressFrameBudget, g_disableSuppressFrames);
	}
	return iPrevious;
}

bool IsEnabled() {
	return g_enabled != 0;
}

uint32_t SetCullParts(int32_t aiMode, uint32_t auiPartBits) {
	Install();
	const LONG iPreviousBits = g_partBits;
	if (aiMode < 0 || aiMode > 2)
		aiMode = 0;
	if (aiMode && !g_hooksOk)
		return static_cast<uint32_t>(iPreviousBits);
	InterlockedExchange(&g_partMode, aiMode);
	InterlockedExchange(&g_partBits, static_cast<LONG>(aiMode ? auiPartBits : 0));
	return static_cast<uint32_t>(iPreviousBits);
}

uint32_t GetCullPartBits() {
	return static_cast<uint32_t>(g_partBits);
}

uint32_t BuildPartBits(const int32_t* apParts, uint32_t auiCount) {
	uint32_t uiBits = 0;
	for (uint32_t i = 0; i < auiCount; ++i)
		if (apParts[i] >= 0 && apParts[i] <= UINT16_MAX)
			uiBits |= PartBit(static_cast<uint16_t>(apParts[i]));
	return uiBits;
}

}
