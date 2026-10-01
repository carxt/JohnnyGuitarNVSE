#include "TESForm.hpp"
#include "TESSoundFile.hpp"

class BGSMusicType : public TESForm, public TESSoundFile {
public:
	BGSMusicType();
	~BGSMusicType();

	struct MusicFileEntry {
		char cFilename[MAX_PATH];
	};

	float							fAttenuation;
#ifdef GAME
	BSSimpleList<MusicFileEntry*>	kFiles;
	uint32_t						uiLastSelection;
#endif

	TESFORM_TYPE(BGSMusicType);

	float GetAttenuation() const;
	void SetAttenuation(float afAttenuation);

	bool GetLooping() const;
	void SetLooping(bool abLoop);

#ifdef GAME
	const char* GetRandomEntry() const;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSMusicType, 0x34);
#else
ASSERT_SIZE(BGSMusicType, 0x3C);
#endif