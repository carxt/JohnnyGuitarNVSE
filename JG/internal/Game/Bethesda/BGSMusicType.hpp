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
	BSSimpleList<MusicFileEntry*>	kFiles;
	uint32_t						uiLastSelection;

	TESFORM_TYPE(BGSMusicType);

	float GetAttenuation() const;
	void SetAttenuation(float afAttenuation);

	bool GetLooping() const;

	const char* GetRandomEntry() const;
};

ASSERT_SIZE(BGSMusicType, 0x34);