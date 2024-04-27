#include "GameTypes.h"
#include "GameAPI.h"
#include "Utilities.h"
struct FileFinder {
	BSSimpleArray<const char*> Paths;

	enum LOOKIN_FLAGS : UInt8 {
		SKIP_NONE = 0x0,
		SKIP_ARCHIVE = 0x1,
		SKIP_CWD = 0x2,
		SKIP_PATHS = 0x4,
	};
	enum OpenMode {
		READ_ONLY = 0x0,
		WRITE_ONLY = 0x1,
		APPEND_ONLY = 0x2,
	};
	enum ARCHIVE_TYPE {
		ARCHIVE_TYPE_ALL_ = 0xFFFFFFFF,
		ARCHIVE_TYPE_ALL = 0xFFFF,
		ARCHIVE_TYPE_MESHES = 0x1,
		ARCHIVE_TYPE_TEXTURES = 0x2,
		ARCHIVE_TYPE_MENUS = 0x4,
		ARCHIVE_TYPE_SOUNDS = 0x8,
		ARCHIVE_TYPE_VOICES = 0x10,
		ARCHIVE_TYPE_SHADERS = 0x20,
		ARCHIVE_TYPE_TREES = 0x40,
		ARCHIVE_TYPE_FONTS = 0x80,
		ARCHIVE_TYPE_MISC = 0x100,
		ARCHIVE_TYPE_COUNT = 9,
	};

	static FileFinder* GetSingleton();
	static BSFile* GetFile(const char* apName, OpenMode aeMode, int aiSize, ARCHIVE_TYPE aeArchiveType);
	static bool Locate(const char* apName, const char* apFilePath, UInt32 aiFlags, ARCHIVE_TYPE aiArchiveType);
	bool Exist(const char* apName, const char* apFilePath, UInt32 aiFlags, ARCHIVE_TYPE aiArchiveType);
};