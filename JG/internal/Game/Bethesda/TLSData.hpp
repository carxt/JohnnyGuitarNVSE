#pragma once

struct TLSData {
	uint32_t							start_padding[2];
#ifdef GAME
	const class BaseExtraList* const	pLastExtraList;				// BaseExtraList
	uint32_t							uiThreadDirty;				// BaseExtraList
	class BSExtraData*					pLastExtraDatas[0x93];		// BaseExtraList
	bool								bLoadTexturesDegraded;		// ModelLoader
	bool								bLoadingTempCellData;		// TESObjectCELL
	class NiAVObject*					pBackgroundLoading3D;		// TESObjectREFR
	class TESObjectREFR*				pBackgroundLoadingRef;		// TESObjectREFR
	bool								bConsoleOutput;				// Script
	class TESForm*						pCrimeVictim;				// Script
	class SCRIPT_LOCAL*					pLastVar;					// ScriptLocals
	uint32_t							uiLastVarSearchID;			// ScriptLocals
	class ScriptLocals*					pLastVarSearchScriptLocals;	// ScriptLocals
	class SCRIPT_REFERENCED_OBJECT*		pLastRefObject;				// Script
	uint32_t							uiLastRefSearchIndex;		// Script
	class ScriptLocals*					pLastScriptLocals;			// Script
	class Script*						pLastRefSearchScript;		// Script
	uint32_t							uiActivateRecursionDepth;
	uint32_t							unk290;
	Bitfield32							uiThreadSpecificFlags;		// BGSSaveLoadGame
	bool								bCollectGarbage;			// GarbageCollector
	uint32_t							unk29C;
	float								fLastScaledTime;
	uint32_t							eLastCycle;
	float								fLastWeightedPhaseTime;
	float								fLastLoKeyTime;
	float								fLastHiKeyTime;
	uint32_t							eMemContext;
	int32_t								iWarningCount;				// BSCoreMessage
	int32_t								iBatchRendererIndex;		// BSShaderAccumulator
    uint32_t							eHavokSyncMode;				// bhkNiCollisionObject
#else
	class ExtraDataList*				pLastExtraList;
	uint32_t							uiThreadDirty;
	class BSExtraData*					pLastExtraDatas[147];
	bool								bLoadTexturesDegraded;
	bool								unk25C;
	bool								unk25D;
	bool								unk25E;
	bool								bConsoleOutput;
	uint32_t							unk264;
	bool								bLoadingTempCellData;
	class NiNode*						pBackgroundLoading3D;
	class TESObjectREFR*				pBackgroundLoadingRef;
	uint32_t							unk274;
	uint32_t							unk278;
	uint32_t							unk27C;
	uint32_t							unk280;
	uint32_t							unk284;
	uint32_t							unk288;
	uint32_t							unk28C;
	uint32_t							eMemContext; // 290
	uint32_t							iWarningCount;
	uint32_t							iBatchRendererIndex;
	uint32_t							eHavokSyncMode;
	uint32_t							unk2A0;
	uint32_t							unk2A4;
#endif

	static TLSData* Get();

	static uint32_t GetMemContext();
	static void SetMemContext(uint32_t index);

	static uint32_t GetBatchRendererIndex();

};
#ifdef GAME
ASSERT_SIZE(TLSData, 0x2C4);
#endif