#pragma once

#include "GameTypes.h"
#include "NiTypes.h"
#include "Bethesda/QueuedFile.hpp"
//#include "NiNodes.h"

/*******************************************************
*
* BSTask
*	IOTask
*		QueuedFile
*			QueuedFileEntry
*				QueuedModel
*					QueuedDistantLOD
*					QueuedTreeModel
*				QueuedTexture
*					QueuedTreeBillboard
*				QueuedKF
*					QueuedAnimIdle
*				DistantLODLoaderTask
*				TerrainLODQuadLoadTask
*				SkyTask
*				LipTask
*				GrassLoadTask
*			QueuedReference
*				QueuedTree
*				QueuedActor
*					QueuedCharacter
*						QueuedPlayer
*					QueuedCreature
*			QueuedHead
*			QueuedHelmet
*			QueuedMagicItem
*		AttachDistant3DTask
*		ExteriorCellLoaderTask
*
* NiTArray< NiPointer<QueuedFile> >
*	QueuedChildren
*
*********************************************************/

class TESObjectREFR;
class TESModel;
class QueuedCharacter;
class TESNPC;
class BSFaceGenNiNode;
class BackgroundCloneThread;
class TESAnimGroup;
class BSFaceGenModel;
class QueuedChildren;
class QueuedReference;
class Character;
class AttachDistant3DTask;
class BSTaskManagerThread;

class ModelLoader;

class NiNode;
class NiControllerSequence;
class RefNiRefObject;
class NiRefObject;
class RefNiObject;

class BSAnimGroupSequence;
struct BSAData;
class TESWorldSpace;

// 40
class QueuedReference : public QueuedFile {
public:
	QueuedReference();
	~QueuedReference();

	virtual void Unk_0B(void);			// Initialize validBip01Names (and cretae the 3D model ?)
	virtual void Unk_0C(void);
	virtual void Unk_0D(NiNode* arg0);
	virtual bool Unk_0E(void);
	virtual void Unk_0F(void);
	virtual void Unk_10(void);			// doesNothing

	TESObjectREFR* refr;				// 028
	RefNiRefObject* unk02C;			// OBSE QueuedChildren	* queuedChildren;	// 02C
	NiRefObject* unk030;			// 030
	NiRefObject* unk034;			// 034
	RefNiRefObject* unk038;			// 038
	uint32_t			unk03C;				// 03C uninitialized
};

// 40
class QueuedActor : public QueuedReference {
public:
	QueuedActor();
	~QueuedActor();
};

// 40
class QueuedCreature : public QueuedActor {
public:
	QueuedCreature();
	~QueuedCreature();
};

// 48
class QueuedCharacter : public QueuedActor {
public:
	QueuedCharacter();
	~QueuedCharacter();

	typedef RefNiRefObject RefQueuedHead;

	RefQueuedHead* refQueuedHead;	// 040
	RefNiRefObject* unk044;	// 044
};

// 48
class QueuedPlayer : public QueuedCharacter {
public:
	QueuedPlayer();
	~QueuedPlayer();
};

// 030
class QueuedFileEntry : public QueuedFile {
public:
	QueuedFileEntry();
	~QueuedFileEntry();

	virtual bool Unk_0B(void) = 0;

	char* name;		// 028
	BSAData* bsaData;	// 02C
};

class Model // NiObject
{
	const char* path;		// 004
	uint32_t		counter;	// 008
	NiNode* ninode;	// 00C
};

// 58
class BGSDistantObjectBlockLoadTask : public QueuedFileEntry
{
public:
	BGSDistantObjectBlockLoadTask();
	~BGSDistantObjectBlockLoadTask();

	virtual void Unk_0C(void);

	uint8_t byte30; // 30
	uint8_t byte31; // 31
	uint8_t byte32; // 32
	uint8_t byte33; // 33
	int cellX; // 34
	int cellY; // 38
	uint32_t lodLevel; // 3C
	void* lodNode14; // 40
	TESWorldSpace* worldSpc; // 44
	NiRefObject* object48; // 48
	NiRefObject* object4C; // 4C
	uint8_t byte50; // 50
	uint8_t byte51; // 51
	uint8_t byte52; // 52
	uint8_t byte53; // 53
	uint32_t unk54; // 54
};

static_assert(sizeof(BGSDistantObjectBlockLoadTask) == 0x58);

// 44
class QueuedModel : public QueuedFileEntry {
public:
	QueuedModel();
	~QueuedModel();

	virtual void Unk_0C(uint32_t arg0);

	Model* model;		// 030
	TESModel* tesModel;		// 034
	uint32_t		baseFormClass;	// 038	table at offset : 0x045C708. Pickable, invisible, unpickable ? 6 is VisibleWhenDistant or internal
	uint8_t		flags;			// 03C	bit 0 and bit 1 init'd by parms, bit 2 set after textureSwap, bit 3 is model set, bit 4 is file found.
	uint8_t		pad03D[3];		// 03D
	float		flt040;			// 040

	// There are at least 3 Create/Initiator
};

// 30
class QueuedTexture : public QueuedFileEntry {
public:
	QueuedTexture();
	~QueuedTexture();

	void* niTexture;	// 030
};

// 014
class KFModel {
	const char* path;					// 000
	BSAnimGroupSequence* controllerSequence;	// 004
	TESAnimGroup* animGroup;			// 008
	uint32_t				unk0C;					// 00C
	uint32_t				unk10;					// 010
};

// 30
class QueuedKF : public QueuedFileEntry {
public:
	QueuedKF();
	~QueuedKF();

	KFModel* kf;		// 030
	uint8_t		unk034;		// 034
	uint8_t		pad035[3];	// 035
};

// 040
class QueuedAnimIdle : public QueuedKF {
public:
	QueuedAnimIdle();
	~QueuedAnimIdle();

	ModelLoader* modelLoader;	// 038	Init"d by arg2
	RefNiObject* unk03C;		// 03C	Init"d by arg1
};

// 38
class QueuedHead : public QueuedFile {
public:
	QueuedHead();
	~QueuedHead();

	TESNPC* npc;				// 028
	BSFaceGenNiNode* faceNiNodes[2];	// 02C OBSE presumably male and female
	uint32_t			unk034;				// 034
};

/*
// 38
class QueuedHelmet : public QueuedFile
{
public:
	QueuedHelmet();
	~QueuedHelmet();

	QueuedCharacter		* queuedCharacter;		// 18
	QueuedChildren		* queuedChildren;		// 1C
	void				* unk20;				// 20
	QueuedModel			* queuedModel;			// 24
	BSFaceGenModel		* faceGenModel;			// 28
	NiNode				* niNode;				// 2C
	Character			* character;			// 30
	uint32_t				unk34;					// 34
};

// 30
class BSTaskManager : public LockFreeMap< NiPointer< BSTask > >
{
public:
	virtual void Unk_0F(uint32_t arg0) = 0;
	virtual void Unk_10(uint32_t arg0) = 0;
	virtual void Unk_11(uint32_t arg0) = 0;
	virtual void Unk_12(void) = 0;
	virtual void Unk_13(uint32_t arg0) = 0;

	uint32_t				unk1C;			// 1C
	uint32_t				unk20;			// 20
	uint32_t				numThreads;		// 24
	BSTaskManagerThread	** threads;		// 28 array of size numThreads
	uint32_t				unk2C;			// 2C
};

// 3C
class IOManager : public BSTaskManager
{
public:
	virtual void Unk_14(uint32_t arg0) = 0;

	static IOManager* GetSingleton();

	uint32_t									unk30;			// 30
	LockFreeQueue< NiPointer< IOTask > >	* taskQueue;	// 34
	uint32_t									unk38;			// 38

	bool IsInQueue(TESObjectREFR *refr);
	void QueueForDeletion(TESObjectREFR* refr);
	void DumpQueuedTasks();
};

extern IOManager** g_ioManager;
*/

template <typename T_Key, typename T_Data> class LockFreeMap {
public:
	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual bool	Lookup(T_Key key, void** result);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);

	void* ptr04;			// 04
	uint32_t		numBuckets;		// 08
	void* ptr0C;			// 0C
	uint32_t		unk10;			// 10
	void* ptr14;			// 14
	uint32_t		numItems;		// 18
};

class AnimIdle;
class Animation;
class QueuedReplacementKFList;
class QueuedHelmet;
class BSFileEntry;
class LoadedFile;
class TESBoundObject;

// 1C
class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();

	LockFreeMap<const char*, Model*>* modelMap;			// 00
	LockFreeMap<const char*, KFModel*>* kfMap;				// 04
	LockFreeMap<TESObjectREFR*, QueuedReference*>* refMap1;			// 08
	LockFreeMap<TESObjectREFR*, QueuedReference*>* refMap2;			// 0C
	LockFreeMap<AnimIdle*, QueuedAnimIdle*>* idleMap;			// 10
	LockFreeMap<Animation*, QueuedReplacementKFList*>* animMap;			// 14
	LockFreeMap<TESObjectREFR*, QueuedHelmet*>* helmetMap;			// 18
	void* attachQueue;		// 1C
	LockFreeMap<BSFileEntry*, QueuedTexture*>* textureMap;		// 20
	LockFreeMap<const char*, LoadedFile*>* fileMap;			// 24
	BackgroundCloneThread* bgCloneThread;		// 28

	static ModelLoader* GetSingleton();
	void QueueReference(TESObjectREFR* apRef, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing);

	TESModel* GetModelForBoundObject(TESBoundObject* apBoundObject, TESObjectREFR* apRef);

	// GAME - 0x447080
	// GECK - 0x4C0040
	NiNode* LoadFile(const char* apPath, uint32_t  aeLODFadeMult = 0, bool abAssignShaders = true, bool abSuppressWarning = false, bool abKeepUV = false, bool abNoUseCountIncrease = false) {
		return ThisCall<NiNode*>(0x447080, this, apPath, aeLODFadeMult, abAssignShaders, abSuppressWarning, abKeepUV, abNoUseCountIncrease);
	}

};

class NiAVObject;

class TaskQueueInterface {
public:
	static TaskQueueInterface* GetSingleton() {
		return *reinterpret_cast<TaskQueueInterface**>(0x11DF1A8);
	}

	void QueueBiped3DDetach(NiAVObject* apObject) {
		ThisCall(0x87AD00, this, apObject);
	}
};