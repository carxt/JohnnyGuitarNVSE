#pragma once

#include "GameAPI.h"

// 0C
class Setting {
public:
	Setting() {};
	virtual ~Setting() {};

	virtual void Unk_01(void) {};

	enum EType {
		kSetting_Bool = 0,
		kSetting_c,
		kSetting_h,
		kSetting_Integer,
		kSetting_Unsigned,
		kSetting_Float,
		kSetting_String,
		kSetting_r,
		kSetting_a,
		kSetting_Other
	};

	union Info {
		UInt32		uint;
		int			i;
		float		f;
		char* str;
	};

	Info		data;	// 04
	const char* name;	// 08

	UInt32 GetType();
	bool ValidType();
	void Get(double* out);
	void Set(float newVal);
	void Set(const char* str, bool doFree);
};

template<class T> class SettingCollection {
	UInt8	byt0004;
	UInt8	fil0005[3];
	UInt32	arr0008[0x0100];
	UInt32	unk0108;
};

// 0014
template<class M, class T> class NiTStringTemplateMap : M {
	UInt8	byt0010;	// 0010
	UInt8	fil0011[3];	// 0011
};

template<class T> class NiTStringMap : NiTStringTemplateMap<NiTMap<char const*, T>, T> {};

template<class T> class BSTCaseInsensitiveStringMap : NiTStringMap<T> {};

template<class T> class SettingCollectionMap {
	SettingCollection<T>					coll000;
	const BSTCaseInsensitiveStringMap<T*>	map010C;
};

template<class T> class SettingCollectionList {
	SettingCollection<T>	coll000;
	tList<UInt32>			lst010C;
};

// 120
class GameSettingCollection			// Contains SettingCollectionMap<Setting> and SettingCollection<Setting>
{
public:
	GameSettingCollection();
	virtual ~GameSettingCollection();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);

	// BSTCaseInsensitiveStringMap <Setting *>
	typedef NiTMapBase <const char*, Setting*>	SettingMap;

	// void		** vtbl							// 000
	UInt32		unk004[(0x10C - 0x004) >> 2];	// 004
	SettingMap	settingMap;						// 10C BSTCaseInsensitiveStringMap
	UInt8		unk11C;							// 11C
	UInt8		pad11D[3];

	bool GetGameSetting(char* settingName, Setting** out);
	static GameSettingCollection* GetSingleton();
};

STATIC_ASSERT(sizeof(GameSettingCollection) == 0x120);

// 114
// actually 2 classes used: IniSettingCollection and IniPrefSettingCollection. Layouts are the same
class IniSettingCollection {
public:
	IniSettingCollection();
	~IniSettingCollection();

	virtual IniSettingCollection* Destroy(bool doFree);
	virtual void	Unk_01(UInt32 arg);
	virtual void	Unk_02(UInt32 arg);
	virtual void	Unk_03(UInt32 arg);
	virtual void	Unk_04(UInt32 arg);
	virtual void	Unk_05(Setting* setting);
	virtual void	Unk_06(UInt32 arg);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);

	char				iniPath[0x100];		// 004
	UInt32				unk104;				// 104
	UInt32				unk108;				// 108
	tList<Setting>		settings;			// 10C;

	static IniSettingCollection* GetIniSettings();
	static IniSettingCollection* GetIniPrefs();
};

STATIC_ASSERT(sizeof(IniSettingCollection) == 0x114);

bool GetNumericGameSetting(char* settingName, double* result);
bool GetINISetting(const char* settingName, Setting** out);
bool GetNumericINISetting(char* settingName, double* result);