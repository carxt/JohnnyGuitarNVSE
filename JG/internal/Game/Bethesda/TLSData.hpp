#pragma once

struct TLSData {
	uint32_t							start_padding[2];
	const class BaseExtraList* const	pLastExtraList;				// BaseExtraList
	uint32_t							uiThreadDirty;				// BaseExtraList
	class BSExtraData*					pLastExtraDatas[147];		// BaseExtraList
	bool								bLoadTexturesDegraded;		// ModelLoader
#ifdef GAME
	bool								bLoadingTempCellData;		// TESObjectCELL
	class NiAVObject*					pBackgroundLoading3D;		// TESObjectREFR
	class TESObjectREFR*				pBackgroundLoadingRef;		// TESObjectREFR
	bool								bConsoleOutput;				// Script
	class TESForm*						pCrimeVictim;				// Script
	class SCRIPT_LOCAL*					pLastVar;					// ScriptLocals
	uint32_t							uiLastVarSearchID;			// ScriptLocals
	class ScriptLocals*					pLastVarSearchScriptLocals;	// ScriptLocals
	class ScriptReferencedObject*		pLastRefObject;				// Script
	uint32_t							uiLastRefSearchIndex;		// Script
	class ScriptLocals*					pLastScriptLocals;			// Script
	class Script*						pLastRefSearchScript;		// Script
	uint32_t							uiActivateRecursionDepth;
	uint32_t							uiTriggerRecursionDepth;
	Bitfield32							uiThreadSpecificFlags;		// BGSSaveLoadGame
	bool								bCollectGarbage;			// GarbageCollector
	uint32_t							unk29C;
#else
	bool								unk25C;
	bool								unk25D;
	bool								unk25E;
	bool								bConsoleOutput;				// Script
	uint32_t							unk264;
	bool								bLoadingTempCellData;		// TESObjectCELL
	class NiAVObject*					pBackgroundLoading3D;		// TESObjectREFR
	class TESObjectREFR*				pBackgroundLoadingRef;		// TESObjectREFR
	uint32_t							unk274;
	uint32_t							unk278;
#endif
	float								fLastScaledTime;
	uint32_t							eLastCycle;
	float								fLastWeightedPhaseTime;
	float								fLastLoKeyTime;
	float								fLastHiKeyTime;
	uint32_t							eMemContext;
	int32_t								iWarningCount;				// BSCoreMessage
	int32_t								iBatchRendererIndex;		// BSShaderAccumulator
	uint32_t							eHavokSyncMode;				// bhkNiCollisionObject


	static TLSData* Get();

	static uint32_t GetMemContext();
	static uint32_t GetAndSetMemContext(uint32_t index);
	static void SetMemContext(uint32_t index);

	static uint32_t GetBatchRendererIndex();

};
#ifdef GAME
ASSERT_SIZE(TLSData, 0x2C4);
#else
ASSERT_SIZE(TLSData, 0x2A0);
#endif