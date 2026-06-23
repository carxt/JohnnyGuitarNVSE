#pragma once

struct hkVector4 {
	float	x, y, z, w;
};

template <typename T_Data> class hkArray {
public:
	enum {
		kFlag_NoDealloc = 0x80000000,	// data not owned by us
		kFlag_Locked = 0x40000000,	// will never be destroyed
	};

	T_Data* data;				// 00
	uint32_t		size;				// 04
	uint32_t		capacityAndFlags;	// 08

	class Iterator {
	protected:
		friend hkArray;

		T_Data* pData;
		uint32_t		count;

	public:
		bool End() const { return !count; }
		void operator++() {
			count--;
			pData++;
		}

		T_Data& operator*() const { return *pData; }
		T_Data& operator->() const { return *pData; }
		T_Data& Get() const { return *pData; }

		Iterator(hkArray& source) : pData(source.data), count(source.size) {}
	};
};

class hkpRigidBody;
class hkStatisticsCollector;
class hkpSimpleConstraintContactMgr;
class hkpWorld;
class bhkWorldObject;
class NiStream;
class ahkpWorld;
class hkpContinuousSimulation;
class hkpRigidBody;
class hkpDefaultWorldMaintenanceMgr;
class hkpBroadPhase;
class hkpBroadPhaseListener;
class hkpPhantomBroadPhaseListener;
class hkpEntityEntityBroadPhaseListener;
class hkpBroadPhaseBorderListener;
class hkpCollisionDispatcher;
class bhkCollisionFilter;
class hkpDefaultConvexListFilter;
class hkpEntityListener;
class hkpContactListener;
class bhkShape;
class hkpCachingShapePhantom;

// 04
class hkBaseObject {
public:
	virtual ~hkBaseObject();
};

// 08
class hkReferencedObject : public hkBaseObject {
public:
	hkReferencedObject();
	~hkReferencedObject();

	virtual void	CalcStatistics(hkStatisticsCollector* collector);
	virtual void	Unk_02(void);

	uint16_t			sizeAndFlags;		// 04
	uint16_t			refCount;			// 06
};

// 04
class hkpEntityListener {
public:
	hkpEntityListener();
	~hkpEntityListener();

	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
};

// 04
class hkpPhantomListener {
public:
	hkpPhantomListener();
	~hkpPhantomListener();

	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
};

// D0
class hkpCharacterProxy : public hkReferencedObject {
public:
	hkpCharacterProxy();
	~hkpCharacterProxy();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);

	hkpEntityListener		entityListener;		// 08
	hkpPhantomListener		phantomListener;	// 0C

	float					velocity[3];		// 10
	float					unk1C;				// 1C
	uint32_t					unk20[4];			// 20
	hkpCachingShapePhantom* shapePhantom;		// 30
	uint32_t					unk34[39];			// 34
};
static_assert(sizeof(hkpCharacterProxy) == 0xD0);

// D0
class ahkpCharacterProxy : public hkpCharacterProxy {
public:
	ahkpCharacterProxy();
	~ahkpCharacterProxy();
};

// 10
struct hkCdBody {
	hkReferencedObject* shape;			// 00
	uint32_t					shapeKey;		// 04
	void* motion;		// 08 - either hkTransform or hkMotionState
	hkCdBody* parent;		// 0C

	hkpWorldObject* GetWorldObj() const { return (hkpWorldObject*)((uint8_t*)this - 0x10); }
};

// 80
struct ContactData {
	uint16_t							unk00;
	uint16_t							flags;
	uint32_t							key;
	hkpSimpleConstraintContactMgr* contactMgr;
	uint32_t							unk0C;
	hkCdBody* cdBody1;
	hkCdBody* cdBody2;
	uint32_t							unk18[26];
};

// 08
struct CdBodyLinker {
	ContactData* data;
	hkCdBody* cdBody;
};

// 10
struct CdParentObj {
	void* unk00;
	uint32_t		unk04;
	void* object;
	uint32_t		unk0C;
};

// 8C
class hkpWorldObject : public hkReferencedObject {
public:
	hkpWorldObject();
	~hkpWorldObject();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);

	hkpWorld* pWorld;		// 08
	bhkWorldObject* object;		// 0C
	hkCdBody				cdBody;			// 10
	uint32_t					unk20[2];		// 20
	uint8_t					collisionType;	// 28	Known: 1 - hkpRigidBody, 2 - hkpPhantom
	uint8_t					unk29[3];		// 29
	uint8_t					layerType;		// 2C
	uint8_t					filterFlags;	// 2D
	uint8_t					unk2E[2];		// 2E
	uint32_t					unk30[12];		// 30
	hkArray<CdBodyLinker>	cdRgdBodies;	// 60
	uint32_t					unk6C[3];		// 6C
	hkArray<CdParentObj>	parentObjs;		// 78
	uint32_t					unk84[2];		// 84
};
static_assert(sizeof(hkpWorldObject) == 0x8C);

// 10
class hkpShape : public hkReferencedObject {
public:
	hkpShape();
	~hkpShape();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);

	bhkShape* shape;		// 08
	uint32_t			unk0C;		// 0C
};

// 0C
class bhkRefObject : public NiObject {
public:
	bhkRefObject();
	~bhkRefObject();

	virtual void	SetObject(hkReferencedObject* object);
	virtual void	UpdateRefCount(bool incRef);	// inc/dec ref, depending on arg

	hkReferencedObject* refObject;		// 08
};

// 10
class bhkSerializable : public bhkRefObject {
public:
	bhkSerializable();
	~bhkSerializable();

	virtual void		Unk_25(uint32_t arg);
	virtual hkpWorld* GetWorld(void);
	virtual bool		Unk_27(uint32_t arg);
	virtual bool		Unk_28(void);
	virtual void		FreeData(bool del);	// free hkData
	virtual uint32_t		Unk_2A(void);
	virtual void		LoadHavokData(NiStream* stream);	// called from bhkSerializable::Load after primary load is done
	virtual void		Unk_2C(void);	// create object
	virtual void* CreateHavokData(uint8_t* arg);	// create Cinfo, return hkData
	virtual void		Unk_2E(void);		// destroy object
	virtual void		Unk_2F(void);
	virtual void		Unk_30(void);

	void* hkData;	// 0C - stores hkConstraintData (descriptor used to build hkObj)
};

// 14
class bhkWorldObject : public bhkSerializable {
public:
	bhkWorldObject();
	~bhkWorldObject();

	virtual void		Unk_31(void);
	virtual void		Unk_32(void);
	virtual void		Unk_33(void);
	virtual void		Unk_34(void);

	uint32_t				bodyFlags;		// 10

	void ApplyForce(hkVector4* forceVector);
};

// 18
class bhkPhantom : public bhkWorldObject {
public:
	bhkPhantom();
	~bhkPhantom();

	uint32_t				unk14;		// 14
};

// 18
class bhkShapePhantom : public bhkPhantom {
public:
	bhkShapePhantom();
	~bhkShapePhantom();
};

// 18
class bhkSimpleShapePhantom : public bhkShapePhantom {
public:
	bhkSimpleShapePhantom();
	~bhkSimpleShapePhantom();
};

class bhkCachingShapePhantom : public bhkShapePhantom {
public:
	bhkCachingShapePhantom();
	~bhkCachingShapePhantom();
};

// 10
class hkpTransformShape : public hkpShape {
public:
	hkpTransformShape();
	~hkpTransformShape();
};

// 14
class bhkShape : public bhkSerializable {
public:
	bhkShape();
	~bhkShape();

	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);

	uint32_t			unk10;		// 10
};

// 14
class bhkTransformShape : public bhkShape {
public:
	bhkTransformShape();
	~bhkTransformShape();
};

struct hkpCdBodyPair {
	hkCdBody* cdBody1;
	uint32_t			unk04;
	hkCdBody* cdBody2;
	uint32_t			unk0C;
};

// 14
class hkpCdBodyPairCollector {
public:
	hkpCdBodyPairCollector();

	virtual ~hkpCdBodyPairCollector();
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

	uint32_t					unk04;			// 04
	hkArray<hkpCdBodyPair>	cdPairs;		// 08
};

// 114
class hkpAllCdBodyPairCollector : public hkpCdBodyPairCollector {
public:
	hkpAllCdBodyPairCollector();
	~hkpAllCdBodyPairCollector();

	hkpCdBodyPair			cdPairsLoc[16];	// 14
};
static_assert(sizeof(hkpAllCdBodyPairCollector) == 0x114);

// A4
class hkpPhantom : public hkpWorldObject {
public:
	hkpPhantom();
	~hkpPhantom();

	virtual uint8_t	PhantomType();
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);

	uint32_t			unk8C[6];		// 8C
};
static_assert(sizeof(hkpPhantom) == 0xA4);

// E0
class hkpAabbPhantom : public hkpPhantom {
public:
	hkpAabbPhantom();
	~hkpAabbPhantom();

	uint32_t					unkA4[11];	// A4
	hkArray<hkCdBody*>		cdBodies;	// D0
	uint32_t					unkDC;		// DC
};
static_assert(sizeof(hkpAabbPhantom) == 0xE0);

// 160
class hkpShapePhantom : public hkpPhantom {
public:
	hkpShapePhantom();
	~hkpShapePhantom();

	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(hkpCdBodyPairCollector* pairCollector, uint32_t arg2);
	virtual void	GetCdBodyData(hkpCdBodyPairCollector* pairCollector, uint32_t arg2);

	uint32_t				unk0A4[47];		// 0A4
};
static_assert(sizeof(hkpShapePhantom) == 0x160);

// 170
class hkpSimpleShapePhantom : public hkpShapePhantom {
public:
	hkpSimpleShapePhantom();
	~hkpSimpleShapePhantom();

	hkArray<hkCdBody*>		cdBodies;	// 160
	uint32_t					unk16C;		// 16C
};
static_assert(sizeof(hkpSimpleShapePhantom) == 0x170);

// 170
class hkpCachingShapePhantom : public hkpShapePhantom {
public:
	hkpCachingShapePhantom();
	~hkpCachingShapePhantom();

	hkArray<CdBodyLinker>	cdBodies;	// 160
	uint32_t					unk16C;		// 16C
};
static_assert(sizeof(hkpCachingShapePhantom) == 0x170);

class hkpConstraintOwner : public hkReferencedObject {
public:
	hkpConstraintOwner();
	~hkpConstraintOwner();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
};

// 6C
class hkpSimulationIsland : public hkpConstraintOwner {
public:
	hkpSimulationIsland();
	~hkpSimulationIsland();

	uint32_t					unk08[4];		// 08
	ahkpWorld* world;			// 18
	uint32_t					unk1C[11];		// 1C
	hkArray<hkpRigidBody*>	rigidBodies;	// 48
	hkpRigidBody* rgdBody54;		// 54
	uint32_t					unk58;			// 58
	hkArray<ContactData*>	contactData;	// 5C
	ContactData* data68;		// 68
};

// 1B8
class hkpWorld : public hkReferencedObject {
public:
	hkpWorld();
	~hkpWorld();

	hkpContinuousSimulation* simulation;				// 008
	float								flt00C;						// 00C
	hkVector4							gravity;					// 010
	hkpSimulationIsland* fixedIsland;				// 020
	hkpRigidBody* fixedRigidBody;			// 024
	hkArray<hkpSimulationIsland*>		activeSimulationIslands;	// 028
	hkArray<hkpSimulationIsland*>		inactiveSimulationIslands;	// 034
	hkArray<hkpSimulationIsland*>		dirtySimulationIslands;		// 040
	hkpDefaultWorldMaintenanceMgr* maintenanceMgr;			// 04C
	uint32_t								unk050;						// 050
	uint32_t								unk054;						// 054
	hkpBroadPhase* broadPhase;				// 058
	uint32_t								unk05C;						// 05C
	uint32_t								unk060;						// 060
	hkpBroadPhaseListener** broadPhaseListeners;		// 064
	hkpPhantomBroadPhaseListener* phantomBroadPhaseListener;	// 068
	hkpEntityEntityBroadPhaseListener* entityBroadPhaseListener;	// 06C
	hkpBroadPhaseBorderListener* broadPhaseBorderListener;	// 070
	void* ptr074;					// 074
	void* ptr078;					// 078
	bhkCollisionFilter* collisionFilter;			// 07C
	hkpCollisionDispatcher* collisionDispatcher;		// 080
	hkpDefaultConvexListFilter* convexListFilter;			// 084
	void* ptr088;					// 088
	uint32_t								unk08C[13];					// 08C
	void* ptr0C0;					// 0C0
	uint32_t								unk0C4[19];					// 0C4
	hkArray<hkpPhantom*>				phantoms;					// 110
	uint32_t								unk11C[3];					// 11C
	hkArray<hkpEntityListener*>			entityListeners1;			// 128
	hkArray<hkpEntityListener*>			entityListeners2;			// 134
	uint32_t								unk140[6];					// 140
	hkArray<hkpContactListener*>		contactListeners;			// 158
	uint32_t								unk164[15];					// 164
	hkArray<hkpContactListener*>		collisionListeners;			// 1A0
	uint32_t								unk1AC[3];					// 1AC
};
static_assert(sizeof(hkpWorld) == 0x1B8);

// 354
class ahkpWorld : public hkpWorld {
public:
	ahkpWorld();
	~ahkpWorld();

	uint32_t			unk1B8[83];			// 1B8
	uint8_t			byte304;			// 304
	uint8_t			byte305;			// 305
	uint8_t			byte306;			// 306
	uint8_t			byte307;			// 307
	uint32_t			unk308[19];			// 308
};
static_assert(sizeof(ahkpWorld) == 0x354);

// 94
class bhkWorld : public bhkSerializable {
public:
	bhkWorld();
	~bhkWorld();

	void* unk10;		// 10 - 0x108 byte object
	NiRefObject* visDebug;	// 14
	uint8_t				unk18;		// 18
	uint8_t				enabled;	// 19
	uint8_t				unk1A;		// 1A
	uint8_t				pad1B;		// 1B
	uint32_t				unk1C[3];	// 1C
	void* unk28;		// 28 - 0x2EE0 byte buffer
	uint32_t				unk2C;		// 2C
	void* unk30;		// 30 - 0x320 byte buffer
	uint32_t				unk34;		// 34
	void* unk38;		// 38 - 0x190 byte buffer
	uint32_t				unk3C;		// 3C
	void* unk40;		// 40 - 0x320 byte buffer
	uint32_t				unk44;		// 44
	void* unk48;		// 48 - 0x2EE0 byte buffer
	uint32_t				unk4C;		// 4C
	NiPoint4			unk50;		// 50
	NiRefObject** unk60;	// 60 - simple array
	uint32_t				unk64;		// 64 - num elements in 060
	uint32_t				unk68;		// 68
	void* unk6C;		// 6C
	uint32_t				unk70[9];	// 70
};
static_assert(sizeof(bhkWorld) == 0x94);

// E0
class bhkWorldM : public bhkWorld {
public:
	bhkWorldM();
	~bhkWorldM();

	float			unk94;			// 94
	float			unk98;			// 98
	float			unk9C;			// 9C
	NiPoint4		borderSize;		// A0
	NiPoint4		worldTotalSize;	// B0
	NiPoint4		vectorC0;		// C0
	uint32_t			unkD0[4];		// D0
};
static_assert(sizeof(bhkWorldM) == 0xE0);

// 0C
class NiCollisionObject : public NiObject {
public:
	NiCollisionObject();
	~NiCollisionObject();

	virtual void	Attach(NiAVObject* obj);
	virtual void	Unk_24(uint32_t arg);
	virtual void	Unk_25(void);
	virtual void	LoadBoundingVolume(uint32_t arg);
	virtual void	Unk_27(uint32_t version, uint32_t arg1);

	NiNode* linkedNode;	// 08
};

// 14
class bhkNiCollisionObject : public NiCollisionObject {
public:
	bhkNiCollisionObject();
	~bhkNiCollisionObject();

	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);

	uint32_t			flags;			// 0C
	bhkWorldObject* worldObj;		// 10

	enum SyncMode : uint32_t {
		SYNC_BOTH		= 0,
		SYNC_TO_HAVOK	= 1,
		SYNC_FROM_HAVOK = 2,
		SYNC_NONE		= 3,
	};

	static void Synchronize(NiAVObject* apObject, bhkNiCollisionObject::SyncMode aeSyncMode) {
		CdeclCall(0xC6C3D0, apObject, aeSyncMode);
	}
};

// 14
class bhkCollisionObject : public bhkNiCollisionObject {
public:
	bhkCollisionObject();
	~bhkCollisionObject();
};

// 14
class bhkPCollisionObject : public bhkNiCollisionObject {
public:
	bhkPCollisionObject();
	~bhkPCollisionObject();
};

// 14
class bhkSPCollisionObject : public bhkPCollisionObject {
public:
	bhkSPCollisionObject();
	~bhkSPCollisionObject();
};

// 08
class hkpCdPointCollector {
public:
	hkpCdPointCollector();
	~hkpCdPointCollector();

	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

	float			earlyOutDistance;	// 04
};

// 70
struct hkCdPoint {
	hkVector4		point00;		// 00
	hkVector4		point10;		// 10
	hkCdBody* cdBody1;		// 20
	uint8_t			body1Key;		// 24
	uint8_t			pad25[2];		// 25
	uint8_t			obj1Flag;		// 27
	hkVector4		point28;		// 28
	hkVector4		point38;		// 38
	hkCdBody* cdBody2;		// 48
	uint8_t			body2Key;		// 4C
	uint8_t			pad4D[2];		// 4D
	uint8_t			obj2Flag;		// 4F
	hkVector4		point50;		// 50
	hkVector4		point60;		// 60
};

// 3A0
class hkpAllCdPointCollector : public hkpCdPointCollector {
public:
	hkpAllCdPointCollector();
	~hkpAllCdPointCollector();

	virtual void	Unk_03(void);

	uint32_t					unk008[2];		// 008
	hkArray<hkCdPoint>		cdPoints;		// 010
	uint32_t					unk01C;			// 01C
	hkCdPoint				cdPointsLoc[8];	// 020
};
static_assert(sizeof(hkpAllCdPointCollector) == 0x3A0);

// 3C8
class bhkCharacterPointCollector : public hkpAllCdPointCollector {
public:
	bhkCharacterPointCollector();
	~bhkCharacterPointCollector();

	uint32_t						unk3A0;			// 3A0
	hkArray<hkpWorldObject*>	contactBodies;	// 3A4
	hkArray<uint32_t>				arr3B0;			// 3B0
	hkArray<float>				arr3BC;			// 3BC
};
static_assert(sizeof(bhkCharacterPointCollector) == 0x3C8);

// 3E0
class bhkCharacterProxy : public bhkSerializable {
public:
	bhkCharacterProxy();
	~bhkCharacterProxy();

	bhkCharacterPointCollector	pointCollecter;		// 10
	uint32_t						unk3D8[2];
};
static_assert(sizeof(bhkCharacterProxy) == 0x3E0);

// 08
class hkpCharacterState : public hkReferencedObject {
public:
	hkpCharacterState();
	~hkpCharacterState();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
};

class bhkCharacterState : public hkpCharacterState {
public:
	bhkCharacterState();
	~bhkCharacterState();
};

class bhkCharacterStateOnGround : public bhkCharacterState {
public:
	bhkCharacterStateOnGround();
	~bhkCharacterStateOnGround();
};

class bhkCharacterStateJumping : public bhkCharacterState {
public:
	bhkCharacterStateJumping();
	~bhkCharacterStateJumping();
};

class bhkCharacterStateInAir : public bhkCharacterState {
public:
	bhkCharacterStateInAir();
	~bhkCharacterStateInAir();
};

class bhkCharacterStateClimbing : public bhkCharacterState {
public:
	bhkCharacterStateClimbing();
	~bhkCharacterStateClimbing();
};

class bhkCharacterStateFlying : public bhkCharacterState {
public:
	bhkCharacterStateFlying();
	~bhkCharacterStateFlying();
};

class bhkCharacterStateSwimming : public bhkCharacterState {
public:
	bhkCharacterStateSwimming();
	~bhkCharacterStateSwimming();
};

class bhkCharacterStateProjectile : public bhkCharacterState {
public:
	bhkCharacterStateProjectile();
	~bhkCharacterStateProjectile();
};

// 34
class hkpCharacterStateManager : public hkReferencedObject {
public:
	hkpCharacterStateManager();
	~hkpCharacterStateManager();

	bhkCharacterStateOnGround* stateOnGround;		// 08
	bhkCharacterStateJumping* stateJumping;		// 0C
	bhkCharacterStateInAir* stateInAir;		// 10
	bhkCharacterStateClimbing* stateClimbing;		// 14
	bhkCharacterStateFlying* stateFlying;		// 18
	bhkCharacterStateSwimming* stateSwimming;		// 1C
	bhkCharacterStateProjectile* stateProjectile;	// 20
	uint32_t							unk24[4];			// 24
};

// 30
class hkpCharacterContext : public hkReferencedObject {
public:
	hkpCharacterContext();
	~hkpCharacterContext();

	uint32_t						unk08;			// 08
	hkpCharacterStateManager* stateMngr;		// 0C
	uint32_t						hkState;		// 10
	uint32_t						unk14[7];		// 14
};

// 04
class hkpCharacterProxyListener {
public:
	hkpCharacterProxyListener();
	~hkpCharacterProxyListener();

	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
};

// 70
class bhkCharacterListener : public hkpCharacterProxyListener {
public:
	bhkCharacterListener();
	~bhkCharacterListener();

	uint32_t			unk04[27];
};

class hkpSphereRepShape : public hkpShape {
public:
	hkpSphereRepShape();
	~hkpSphereRepShape();
};

class hkpConvexShape : public hkpSphereRepShape {
public:
	hkpConvexShape();
	~hkpConvexShape();
};

// 20
class hkpSphereShape : public hkpConvexShape {
public:
	hkpSphereShape();
	~hkpSphereShape();

	uint32_t			unk10[4];		// 10
};

// 30
class hkpBoxShape : public hkpConvexShape {
public:
	hkpBoxShape();
	~hkpBoxShape();

	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);

	float			flt10;		// 10
	float			flt14;		// 14
	float			flt18;		// 18
	float			flt1C;		// 1C
	float			flt20;		// 20
	float			flt24;		// 24
	float			flt28;		// 28
	float			flt2C;		// 2C
};
static_assert(sizeof(hkpBoxShape) == 0x30);

struct VerticesBlock {
	NiPoint4	rowX;
	NiPoint4	rowY;
	NiPoint4	rowZ;
};

// 70
class hkpConvexVerticesShape : public hkpConvexShape {
public:
	hkpConvexVerticesShape();
	~hkpConvexVerticesShape();

	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);

	float			radius;			// 10
	float			flt14;			// 14
	uint32_t			unk18;			// 18
	float			flt1C;			// 1C
	float			flt20;			// 20
	float			flt24;			// 24
	float			flt28;			// 28
	uint32_t			unk2C;			// 2C
	uint32_t			unk30;			// 30
	uint32_t			unk34;			// 34
	uint32_t			unk38;			// 38
	uint32_t			unk3C;			// 3C
	VerticesBlock* verticesArray;	// 40
	uint32_t			numBlocks;		// 44
	uint32_t			unk48;			// 48
	uint32_t			numVertices;	// 4C
	uint32_t			unk50;			// 50
	NiPoint4* normalsArray;	// 54
	uint32_t			numNormals;		// 58
	uint32_t			unk5C;			// 5C
	uint32_t			unk60;			// 60
	float			flt64;			// 64
	uint32_t			unk68;			// 68
	float			flt6C;			// 6C
};
static_assert(sizeof(hkpConvexVerticesShape) == 0x70);

// 70
class hkCharControllerShape : public hkpConvexVerticesShape {
public:
	hkCharControllerShape();
	~hkCharControllerShape();

	virtual void	Unk_12(void);
};

// 40
class hkpCapsuleShape : public hkpConvexShape {
public:
	hkpCapsuleShape();
	~hkpCapsuleShape();

	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);

	float			flt10;		// 10
	uint32_t			unk14;		// 14
	BSFadeNode* fadeNode;	// 18
	uint32_t			unk1C;		// 1C
	uint32_t			unk20;		// 20
	uint32_t			unk24;		// 24
	float			flt28;		// 28
	float			flt2C;		// 2C
	uint32_t			unk30;		// 30
	uint32_t			unk34;		// 34
	float			flt38;		// 38
	float			flt3C;		// 3C
};
static_assert(sizeof(hkpCapsuleShape) == 0x40);

// 14
class bhkSphereRepShape : public bhkShape {
public:
	bhkSphereRepShape();
	~bhkSphereRepShape();
};

// 14
class bhkConvexShape : public bhkSphereRepShape {
public:
	bhkConvexShape();
	~bhkConvexShape();
};

// 14
class bhkCapsuleShape : public bhkConvexShape {
public:
	bhkCapsuleShape();
	~bhkCapsuleShape();
};

// 14
class bhkConvexVerticesShape : public bhkConvexShape {
public:
	bhkConvexVerticesShape();
	~bhkConvexVerticesShape();
};

// 14
class bhkCharControllerShape : public bhkConvexVerticesShape {
public:
	bhkCharControllerShape();
	~bhkCharControllerShape();
};

// 660
class bhkCharacterController : public bhkCharacterProxy {
public:
	bhkCharacterController();
	~bhkCharacterController();

	virtual void			Unk_31(void);
	virtual void			Unk_32(void);
	virtual void			Unk_33(void);
	virtual void			Unk_34(void);

	hkpCharacterContext		chrContext;			// 3E0
	bhkCharacterListener	chrListener;		// 410

	uint32_t					unk480[18];			// 480
	float					unk4C8[4];			// 4C8
	uint32_t					unk4D8[4];			// 4D8
	float					timeDelta;			// 4E8
	float					unk4EC;				// 4EC
	float					velocity[3];		// 4F0
	uint32_t					unk4FC[9];			// 4FC
	uint32_t					unk520;				// 520
	uint32_t					unk524[3];			// 524
	float					fallTimeRemaining;	// 530
	float					flt534;				// 534
	float					flt538;				// 538
	float					flt53C;				// 53C
	float					flt540;				// 540
	float					startingHeight;		// 544
	float					fallTimeElapsed;	// 548
	float					flt54C;				// 54C
	uint32_t					unk550[17];			// 550
	bhkCachingShapePhantom* chrPhantom;		// 594
	uint32_t					unk598[3];			// 598
	bhkCapsuleShape* capsuleShape;		// 5A4
	bhkCharControllerShape* charCtrlShape;		// 5A8
	uint32_t					unk5AC[23];			// 5AC
	uint8_t					byte608;			// 608
	uint8_t					pad609[3];			// 609
	hkpRigidBody* bodyUnderFeet;		// 60C
	uint32_t					unk610[11];			// 610
	hkArray<hkCdPoint>		arr63C;				// 63C
	uint32_t					unk648[6];			// 648
};
static_assert(sizeof(bhkCharacterController) == 0x660);

class hkpEntity : public hkpWorldObject {
public:
	hkpEntity();
	~hkpEntity();

	virtual void	Unk_05(void);
};

class hkpConstraintData : public hkReferencedObject {
public:
	hkpConstraintData();
	~hkpConstraintData();

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
};

// 38
class hkpConstraintInstance : public hkReferencedObject {
public:
	hkpConstraintInstance();
	~hkpConstraintInstance();

	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);

	hkpSimulationIsland* simIsle;			// 08
	hkpConstraintData* constraintData;	// 0C
	uint32_t					unk10;				// 10
	hkpRigidBody* contactBody;		// 14
	hkpRigidBody* parentBody;		// 18
	uint32_t					unk1C[5];			// 1C
	void* ptr30;				// 30
	uint32_t					unk34;				// 34
};

// F0+
class hkpMotion : public hkReferencedObject {
public:
	hkpMotion();
	~hkpMotion();

	virtual void	Unk_03(void);
	virtual void	SetBodyMass(float mass);
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
	virtual void	SetLinearVelocity(NiPoint4* velocity);
	virtual void	SetAngularVelocity(NiPoint4* velocity);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	Unk_16(void);
	virtual void	Unk_17(void);
	virtual void	Unk_18(void);
	virtual void	Unk_19(void);

	enum {
		kMotionType_Sphere = 2,
		kMotionType_Box,
		kMotionType_KeyframedRigid,
		kMotionType_FixedRigid,
		kMotionType_ThinBox,
		kMotionType_Character,
	};

	uint8_t			type;			// 008
	uint8_t			byte009;		// 009
	uint16_t			word00A;		// 00A
	uint16_t			word00C;		// 00C
	uint8_t			pad00E[2];		// 00E
	NiPoint4		vector010;		// 010
	NiPoint4		vector020;		// 020
	NiPoint4		vector030;		// 030
	NiPoint4		vector040;		// 040
	NiPoint4		vector050;		// 050
	NiPoint4		vector060;		// 060
	NiPoint4		quaternion070;	// 070
	NiPoint4		quaternion080;	// 080
	NiPoint4		vector090;		// 090
	NiPoint4		vector0A0;		// 0A0
	float			flt0B0;			// 0B0
	float			linDamping;		// 0B4
	float			angDamping;		// 0B8
	uint8_t			byte0BC;		// 0BC
	uint8_t			byte0BD;		// 0BD
	uint8_t			byte0BE;		// 0BE
	uint8_t			byte0BF;		// 0BF
	float			inertiaX;		// 0C0
	float			inertiaY;		// 0C4
	float			inertiaZ;		// 0C8
	float			bodyMass;		// 0CC
	NiPoint4		linVelocity;	// 0D0
	NiPoint4		angVelocity;	// 0E0
	NiPoint4		vector0F0;		// 0F0
	NiPoint4		vector100;		// 100
	uint32_t			unk110[12];		// 110

	float GetBodyMass();
};
static_assert(sizeof(hkpMotion) == 0x140);

class hkpSphereMotion : public hkpMotion {
public:
	hkpSphereMotion();
	~hkpSphereMotion();

	virtual void	Unk_1A(void);
};

class hkpBoxMotion : public hkpMotion {
public:
	hkpBoxMotion();
	~hkpBoxMotion();

	virtual void	Unk_1A(void);
};

class hkpThinBoxMotion : public hkpBoxMotion {
public:
	hkpThinBoxMotion();
	~hkpThinBoxMotion();
};

// 30
struct ConstraintContact {
	hkpConstraintInstance* instance;		// 00
	hkpRigidBody* parentBody;	// 04
	hkpRigidBody* contactBody;	// 08
	void* ptr0C;			// 0C
	uint32_t					unk10[5];		// 10
	float					flt24[3];		// 24
};

// 220
class hkpRigidBody : public hkpEntity {
public:
	hkpRigidBody();
	~hkpRigidBody();

	virtual void	Unk_06(void);
	virtual void	Unk_07(void);

	uint8_t							byte8C;			// 8C
	uint8_t							pad8D[3];		// 8D
	float							friction;		// 90
	float							restitution;	// 94
	uint32_t							unk98[5];		// 98
	ConstraintContact* contactsArr;	// AC
	uint16_t							contactsSize;	// B0
	uint16_t							contactsCap;	// B2
	hkArray<hkpConstraintInstance*>	constraintInst;	// B4
	uint32_t							unkC0[3];		// C0
	hkpSimulationIsland* simIsle;		// CC
	uint32_t							unkD0[4];		// D0
	hkpMotion						motion;			// E0

	void UpdateMotion();
};

// 14
class bhkEntity : public bhkWorldObject {
public:
	bhkEntity();
	~bhkEntity();
};

// 1C
class bhkRigidBody : public bhkEntity {
public:
	bhkRigidBody();
	~bhkRigidBody();

	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);
	virtual void	Unk_39(void);
	virtual void	Unk_3A(void);
	virtual void	Unk_3B(void);
	virtual void	Unk_3C(void);
	virtual void	Unk_3D(void);
	virtual void	Unk_3E(void);
	virtual void	Unk_3F(void);

	uint32_t			unk14[2];		// 14
};

// 50
class bhkRigidBodyT : public bhkRigidBody {
public:
	bhkRigidBodyT();
	~bhkRigidBodyT();

	uint32_t			unk1C[13];		// 1C
};

class hkaRaycastInterface {
public:
	hkaRaycastInterface();

	virtual			~hkaRaycastInterface();
	virtual bool* castRay(bool*, hkVector4*, hkVector4*, uint32_t, float, hkVector4*);
	virtual bool* castRayAlt(bool*, hkVector4*, hkVector4*, uint32_t, hkVector4*);
};

class ALIGN16 bhkRagdollController : public hkaRaycastInterface {
public:
	// CBA to import all types

	bool GetLookIKEnable() const {
		return ThisCall<bool>(0x5BA540, this);
	}

	void SetLookIKEnable(bool abVal) {
		ThisCall(0x5BA4F0, this, abVal);
	}

	bool GetFootIKEnable() const {
		return ThisCall<bool>(0x5BA180, this);
	}

	void SetFootIKEnable(bool abVal) {
		ThisCall(0x5BA130, this, abVal);
	}

	bool GetGrabIKEnable() const {
		return ThisCall<bool>(0x5BA360, this);
	}

	void SetGrabIKEnable(bool abVal) {
		ThisCall(0x5BA310, this, abVal);
	}
};