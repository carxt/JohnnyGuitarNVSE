#pragma once

#include "Utilities.h"

#if RUNTIME

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
const UInt32 kNiTMapLookupAddr = 0x853130;
#else
#error
#endif

#else
const UInt32 _NiTMap_Lookup = 0;
#endif

// 08
struct NiRTTI
{
	const char		*name;
	NiRTTI			*parent;
};

// 24
struct NiMatrix33
{
	float	cr[3][3];

	void ExtractAngles(float &rotX, float &rotY, float &rotZ);
	void RotationMatrix(float rotX, float rotY, float rotZ);
	void Rotate(float rotX, float rotY, float rotZ);
	void MultiplyMatrices(NiMatrix33 &matA, NiMatrix33 &matB);
	void Dump(const char *title = NULL);
};

struct NiQuaternion;

#define DECL_FLOAT_OP(op) \
	NiPoint3 operator op(const float n) const \
	{ \
		return NiPoint3(x op n, y op n, z op n); \
	} \
	NiPoint3 operator op##=(const float n) \
	{ \
		return *this = NiPoint3(x op n, y op n, z op n); \
	} \

#define DECL_VEC_OP(op) \
	NiPoint3 operator op(const NiPoint3 v) const \
	{ \
		return NiPoint3(x op v.x, y op v.y, z op v.z); \
	} \
	NiPoint3 operator op##=(const NiPoint3 v) \
	{ \
		return *this = NiPoint3(x op v.x, y op v.y, z op v.z); \
	}

struct NiPoint3 {
	float x, y, z;

	void Scale(float scale) {
		x *= scale;
		y *= scale;
		z *= scale;
	};

	void Init(NiPoint3* point) {
		x = point->x;
		y = point->y;
		z = point->z;
	};

	NiPoint3() : x(0.f), y(0.f), z(0.f) {};

	NiPoint3(const float x, const float y, const float z) : x(x), y(y), z(z) {};

	DECL_FLOAT_OP(*);
	DECL_FLOAT_OP(/ );

	DECL_VEC_OP(+);
	DECL_VEC_OP(-);
	DECL_VEC_OP(*);
	DECL_VEC_OP(/ );

	float length() const {
		return sqrtf(x * x + y * y + z * z);
	}

	float length_sqr() const {
		return x * x + y * y + z * z;
	}

	NiPoint3 normal() const {
		const auto len = length();
		return len == 0.F ? NiPoint3() : NiPoint3(x / len, y / len, z / len);
	}

	static float dot(const NiPoint3& v1, const NiPoint3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	inline float Distance(const NiPoint3& pt) const {
		return (*this - pt).length();
	}

	static NiPoint3 cross(const NiPoint3& v1, const NiPoint3& v2) {
		return NiPoint3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	NiPoint3* Add(NiPoint3* toAdd) {
		this->x += toAdd->x;
		this->y += toAdd->y;
		this->z += toAdd->z;
		return this;
	}

	NiPoint3* Subtract(NiPoint3* point) {
		this->x -= point->x;
		this->y -= point->y;
		this->z -= point->z;
		return this;
	}

	float CalculateDistSquared(NiPoint3* to) {
		float deltaX = (x - to->x);
		float deltaY = (y - to->y);
		float deltaZ = (z - to->z);

		return deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
	}
	static float Sign(NiPoint3 p1, NiPoint3 p2, NiPoint3 p3) {
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}

	static bool PointInTriangle(NiPoint3 pt, NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		bool b1 = Sign(pt, v1, v2) < 0.0;
		bool b2 = Sign(pt, v2, v3) < 0.0;
		bool b3 = Sign(pt, v3, v1) < 0.0;

		return (b1 == b2) && (b2 == b3);
	}

	static NiPoint3 GetTriangleCenter(NiPoint3 v1, NiPoint3 v2, NiPoint3 v3) {
		return NiPoint3((v1.x + v2.x + v3.x) / 3.0f, (v1.y + v2.y + v3.y) / 3.0f, (v1.z + v2.z + v3.z) / 3.0f);
	}

};

class NiPoint4 {
public:
	float x;
	float y;
	float z;
	float w;

	NiPoint4() : x(0.f), y(0.f), z(0.f), w(0.f) {};
	NiPoint4(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {};
	NiPoint4(const NiPoint3& src) : x(src.x), y(src.y), z(src.z), w(0.f) {};

	inline const float operator[] (UInt32 i) const { return ((float*)&x)[i]; };
	inline float operator[] (UInt32 i) { return ((float*)&x)[i]; };

	operator float* () const { return (float*)this; };


	NiPoint4 operator=(NiPoint3 pt) const {
		return NiPoint4(pt.x, pt.y, pt.z, w);
	};

	void operator=(NiPoint3* pt) {
		x = pt->x;
		y = pt->y;
		z = pt->z;
	};

	void operator=(const NiPoint3& pt) {
		x = pt.x;
		y = pt.y;
		z = pt.z;
	};

	NiPoint4 operator-(NiPoint3& pt) const {
		return NiPoint4(x - pt.x, y - pt.y, z - pt.z, w);
	};

	NiPoint4 operator-(NiPoint3* pt) const {
		return NiPoint4(x - pt->x, y - pt->y, z - pt->z, w);
	};

	NiPoint4* operator-(const NiPoint3& pt) const {
		return new NiPoint4(x - pt.x, y - pt.y, z - pt.z, w);
	};

	NiPoint4* operator-(const NiPoint3* pt) const {
		return new NiPoint4(x - pt->x, y - pt->y, z - pt->z, w);
	};

	NiPoint4 operator+ (const NiPoint4& pt) const { return NiPoint4(x + pt.x, y + pt.y, z + pt.z, w + pt.w); };
	NiPoint4& operator+= (const NiPoint4& pt) {
		x += pt.x;
		y += pt.y;
		z += pt.z;
		w += pt.w;
		return *this;
	};

	NiPoint4 operator*(const float afScalar) {
		return NiPoint4(x * afScalar, y * afScalar, z * afScalar, w * afScalar);
	}

	NiPoint4& operator*= (float afScalar) {
		x *= afScalar;
		y *= afScalar;
		z *= afScalar;
		w *= afScalar;
		return *this;
	};
};

STATIC_ASSERT(sizeof(NiPoint4) == 0x10);

// 10 - always aligned?
struct NiQuaternion
{
	float	w, x, y, z;

	NiQuaternion() {}
	NiQuaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

	void EulerYPR(NiPoint3 &ypr);
	void RotationMatrix(NiMatrix33 &rotMatrix);
	void Dump();
};

// 34
struct NiTransform
{
	NiMatrix33	rotate;		// 00
	NiPoint3	translate;	// 24
	float		scale;		// 30
};

// 10
struct NiBound
{
	NiPoint3 center;
	float radius;

	NiBound() : center(NiPoint3(0.0f, 0.0f, 0.0f)), radius(0.0f) {};
	NiBound(NiPoint3 akCenter, float afRadius) : center(akCenter), radius(afRadius) {};
	~NiBound() {};

	bool IsPointWithin(const NiPoint3& arPoint) const {
		float fDistance = center.Distance(arPoint);
		return fDistance <= radius;
	}
};

// 1C
struct NiFrustum
{
	float	l;			// 00
	float	r;			// 04
	float	t;			// 08
	float	b;			// 0C
	float	n;			// 10
	float	f;			// 14
	UInt8	o;			// 18
	UInt8	pad19[3];	// 19
};

// 10
struct NiViewport
{
	float	l;
	float	r;
	float	t;
	float	b;
};

// C
struct NiColor
{
	float	r;
	float	g;
	float	b;
};

// 10
struct NiColorAlpha
{
	float	r;
	float	g;
	float	b;
	float	a;
};

// 10
struct NiPlane
{
	NiPoint3	nrm;
	float		offset;
};

// 10
// NiTArrays are slightly weird: they can be sparse
// this implies that they can only be used with types that can be NULL?
// not sure on the above, but some code only works if this is true
// this can obviously lead to fragmentation, but the accessors don't seem to care
// weird stuff
template <typename T_Data>
struct NiTArray
{
	virtual void* Destroy(UInt32 doFree);

	T_Data* data;			// 04
	UInt16		capacity;		// 08 - init'd to size of preallocation
	UInt16		firstFreeEntry;	// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16		numObjs;		// 0C - init'd to 0
	UInt16		growSize;		// 0E - init'd to size of preallocation

	T_Data operator[](UInt32 idx)
	{
		if (idx < firstFreeEntry)
			return data[idx];
		return NULL;
	}

	T_Data Get(UInt32 idx) { return data[idx]; }

	UInt16 Length() { return firstFreeEntry; }
	void AddAtIndex(UInt32 index, T_Data* item);	// no bounds checking
	void SetCapacity(UInt16 newCapacity);	// grow and copy data if needed

	class Iterator
	{
		friend NiTArray;

		T_Data* pData;
		UInt16		count;

	public:
		bool End() const { return !count; }
		void operator++()
		{
			pData++;
			count--;
		}

		T_Data& operator*() const { return *pData; }
		T_Data& operator->() const { return *pData; }
		T_Data& Get() const { return *pData; }

		Iterator(NiTArray& source) : pData(source.data), count(source.firstFreeEntry) {}
	};

	Iterator Begin() { return Iterator(*this); }
};
#if RUNTIME

template <typename T> void NiTArray<T>::AddAtIndex(UInt32 index, T* item)
{
#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
	ThisStdCall(0x00869640, this, index, item);
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
	ThisStdCall(0x00869110, this, index, item);
#else
#error unsupported Oblivion version
#endif
}

template <typename T> void NiTArray<T>::SetCapacity(UInt16 newCapacity)
{
#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525
	ThisStdCall(0x008696E0, this, newCapacity);
#elif RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525ng
	ThisStdCall(0x00869190, this, newCapacity);
#else
#error unsupported Runtime version
#endif
}

#endif

// 18
// an NiTArray that can go above 0xFFFF, probably with all the same weirdness
// this implies that they make fragmentable arrays with 0x10000 elements, wtf
template <typename T>
class NiTLargeArray
{
public:
	NiTLargeArray();
	~NiTLargeArray();

	void	** _vtbl;		// 00
	T		* data;			// 04
	UInt32	capacity;		// 08 - init'd to size of preallocation
	UInt32	firstFreeEntry;	// 0C - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt32	numObjs;		// 10 - init'd to 0
	UInt32	growSize;		// 14 - init'd to size of preallocation

	T operator[](UInt32 idx) {
		if (idx < firstFreeEntry)
			return data[idx];
		return NULL;
	}

	T Get(UInt32 idx) { return (*this)[idx]; }

	UInt32 Length(void) { return firstFreeEntry; }
};

// 8
template <typename T>
struct NiTSet
{
	T		* data;		// 00
	UInt16	capacity;	// 04
	UInt16	length;		// 06
};

// 10
// this is a NiTPointerMap <UInt32, T_Data>
// todo: generalize key
template <typename T_Data>
class NiTPointerMap
{
public:
	NiTPointerMap();
	virtual ~NiTPointerMap();

	virtual UInt32	CalculateBucket(UInt32 key);
	virtual bool	CompareKey(UInt32 lhs, UInt32 rhs);
	virtual void	Fn_03(UInt32 arg0, UInt32 arg1, UInt32 arg2);	// assign to entry
	virtual void	Fn_04(UInt32 arg);
	virtual void	Fn_05(void);	// locked operations
	virtual void	Fn_06(void);	// locked operations

	struct Entry
	{
		Entry		*next;
		UInt32		key;
		T_Data		*data;
	};

	UInt32		m_numBuckets;	// 04
	Entry		**m_buckets;	// 08
	UInt32		m_numItems;		// 0C

	T_Data *Lookup(UInt32 key) const
	{
		for (Entry *traverse = m_buckets[key % m_numBuckets]; traverse; traverse = traverse->next)
			if (traverse->key == key) return traverse->data;
		return NULL;
	}

	bool Insert(Entry *newEntry)
	{
		UInt32 bucket = newEntry->key % m_numBuckets;
		Entry *entry = m_buckets[bucket], *prev;
		if (entry)
		{
			do
			{
				if (entry->key == newEntry->key) return false;
				prev = entry;
			}
			while (entry = entry->next);
			prev->next = newEntry;
		}
		else m_buckets[bucket] = newEntry;
		m_numItems++;
		return true;
	}

	class Iterator
	{
		friend NiTPointerMap;

		NiTPointerMap* table;
		Entry** bucket;
		Entry* entry;

		void FindNonEmpty()
		{
			for (Entry** end = &table->m_buckets[table->m_numBuckets]; bucket != end; bucket++)
				if (entry = *bucket) return;
		}

	public:
		Iterator(NiTPointerMap& _table) : table(&_table), bucket(table->m_buckets), entry(NULL) { FindNonEmpty(); }

		bool End() const { return !entry; }
		void operator++()
		{
			entry = entry->next;
			if (!entry)
			{
				bucket++;
				FindNonEmpty();
			}
		}
		T_Data* Get() const { return entry->data; }
		UInt32 Key() const { return entry->key; }
	};

	Iterator Begin() { return Iterator(*this); }
};

// 10
// todo: NiTPointerMap should derive from this
// cleaning that up now could cause problems, so it will wait
template <typename T_Key, typename T_Data>
class NiTMapBase
{
public:
	NiTMapBase();
	~NiTMapBase();

	struct Entry
	{
		Entry		*next;
		T_Key		key;
		T_Data		data;
	};

	Entry* LookupEntry(T_Key key)
	{
		for (Entry* traverse = buckets[Hash(key) % numBuckets]; traverse; traverse = traverse->next)
			if constexpr (std::is_same<const char*, T_Key>::value)
				if (_stricmp(traverse->key, key) == 0) return traverse;
			else
				if (traverse->key == key) return traverse;
		return NULL;
	}

	virtual NiTMapBase	*Destructor(bool doFree);
	virtual UInt32		Hash(T_Key key);
	virtual void		Equal(T_Key key1, T_Key key2);
	virtual void		FillEntry(Entry entry, T_Key key, T_Data data);
	virtual	void		Unk_004(void *arg0);
	virtual	void		Unk_005();
	virtual	void		Unk_006();

	UInt32		numBuckets;	// 04
	Entry		**buckets;	// 08
	UInt32		numItems;	// 0C

	class Iterator
	{
		friend NiTMapBase;

		NiTMapBase		*m_table;
		Entry			*m_entry;
		UInt32			m_bucket;

		void FindValid()
		{
			for (; m_bucket < m_table->numBuckets; m_bucket++)
			{
				m_entry = m_table->buckets[m_bucket];
				if (m_entry) break;
			}
		}

	public:
		Iterator(NiTMapBase *table) : m_table(table), m_entry(NULL), m_bucket(0) {FindValid();}

		bool Done() const {return m_entry == NULL;}
		void Next()
		{
			m_entry = m_entry->next;
			if (!m_entry)
			{
				m_bucket++;
				FindValid();
			}
		}
		T_Data Get() const {return m_entry->data;}
		T_Key Key() const {return m_entry->key;}
	};

	bool Lookup(T_Key key, T_Data *dataOut);
};

template <typename T_Key, typename T_Data>
__declspec(naked) bool NiTMapBase<T_Key, T_Data>::Lookup(T_Key key, T_Data *dataOut)
{
	__asm	jmp		kNiTMapLookupAddr
}

// 14
template <typename T_Data>
class NiTStringPointerMap : public NiTPointerMap<T_Data>
{
public:
	NiTStringPointerMap();
	~NiTStringPointerMap();

	UInt32	unk010;
};

// not sure how much of this is in NiTListBase and how much is in NiTPointerListBase
// 10
template <typename T>
class NiTListBase
{
public:
	NiTListBase();
	~NiTListBase();

	struct Node
	{
		Node	* next;
		Node	* prev;
		T		* data;
	};

	virtual void	Destructor(void);
	virtual Node *	AllocateNode(void);
	virtual void	FreeNode(Node * node);

//	void	** _vtbl;	// 000
	Node	* start;	// 004
	Node	* end;		// 008
	UInt32	numItems;	// 00C
};

// 10
template <typename T>
class NiTPointerListBase : public NiTListBase <T>
{
public:
	NiTPointerListBase();
	~NiTPointerListBase();
};

// 10
template <typename T>
class NiTPointerList : public NiTPointerListBase <T>
{
public:
	NiTPointerList();
	~NiTPointerList();
};

// 4
template <class T_Data>
class NiPointer {
public:
	NiPointer(T_Data* pObject = (T_Data*)0);
	NiPointer(const NiPointer& ptr);
	~NiPointer();

	T_Data* m_pObject;

	operator T_Data* () const;
	T_Data& operator*() const;
	T_Data* operator->() const;

	__forceinline NiPointer<T_Data>& operator =(const NiPointer& ptr) {
		if (m_pObject != ptr.m_pObject) {
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = ptr.m_pObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	__forceinline NiPointer<T_Data>& operator =(T_Data* pObject) {
		if (m_pObject != pObject) {
			if (m_pObject)
				m_pObject->DecRefCount();
			m_pObject = pObject;
			if (m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	__forceinline bool operator==(T_Data* pObject) const { return (m_pObject == pObject); }

	//__forceinline bool operator!=(T_Data* pObject) const { return (m_pObject != pObject); }

	__forceinline bool operator==(const NiPointer& ptr) const { return (m_pObject == ptr.m_pObject); }

	//__forceinline bool operator!=(const NiPointer& ptr) const { return (m_pObject != ptr.m_pObject); }

	__forceinline operator bool() const { return m_pObject != nullptr; }
};

#define NiSmartPointer(className) \
    class className; \
    typedef NiPointer<className> className##Ptr;


template <class T_Data>
inline NiPointer<T_Data>::NiPointer(T_Data* pObject) {
	m_pObject = pObject;
	if (m_pObject)
		m_pObject->IncRefCount();
}

template <class T_Data>
inline NiPointer<T_Data>::NiPointer(const NiPointer& ptr) {
	m_pObject = ptr.m_pObject;
	if (m_pObject)
		m_pObject->IncRefCount();
}

template <class T_Data>
inline NiPointer<T_Data>::~NiPointer() {
	if (m_pObject)
		m_pObject->DecRefCount();
}

template <class T_Data>
inline NiPointer<T_Data>::operator T_Data* () const {
	return m_pObject;
}

template <class T_Data>
inline T_Data& NiPointer<T_Data>::operator*() const {
	return *m_pObject;
}

template <class T_Data>
inline T_Data* NiPointer<T_Data>::operator->() const {
	return m_pObject;
}

// 14
template <typename T>
class BSTPersistentList
{
public:
	BSTPersistentList();
	~BSTPersistentList();

	virtual void	Destroy(bool destroy);

//	void	** _vtbl;	// 00
	UInt32	unk04;		// 04
	UInt32	unk08;		// 08
	UInt32	unk0C;		// 0C
	UInt32	unk10;		// 10
};
