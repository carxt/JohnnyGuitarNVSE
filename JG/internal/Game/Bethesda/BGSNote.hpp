#pragma once

#include "BGSPickupPutdownSounds.hpp"
#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESIcon.hpp"
#include "TESModel.hpp"

class TESDescription;
class TESActorBase;
class TESTopic;
class TESQuest;

class BGSNote : public TESBoundObject, public TESModel, public TESFullName, public TESIcon, public BGSPickupPutdownSounds {
public:
	BGSNote();
	~BGSNote();

	struct _NoteType {
		enum Type : uint8_t {
			SOUND	= 0,
			TEXT	= 1,
			IMAGE	= 2,
			VOICE	= 3,
		};
	};
	using NoteType = _NoteType::Type;

	union {
		TESSound*		__restrict pNoteSound;
		TESDescription* __restrict pNoteText;
		TESTexture*		__restrict pNotePicture;
		TESTopic*		__restrict pNoteTopic;
	};
	TESActorBase*				pSpeaker;
	BSSimpleList<TESQuest*>		kOwnerQuests;
	NoteType					eNoteType;
	bool						bHasBeenRead;

	TESFORM_TYPE(BGSNote);

	BGSNote::NoteType GetNoteType() const;
	void SetNoteType(BGSNote::NoteType aeType);

	TESSound* GetNoteSound() const;
	void SetNoteSound(TESSound* apSound);

	TESDescription* GetNoteText() const;
	void SetNoteText(TESDescription* apText);

	TESTexture* GetNoteImage() const;
	void SetNoteImage(TESTexture* apImage);

	TESTopic* GetNoteTopic() const;
	void SetNoteTopic(TESTopic* apTopic);

	TESActorBase* GetNoteSpeaker() const;
	void SetNoteSpeaker(TESActorBase* apSpeaker);

	bool GetHasBeenRead() const;
	void SetHasBeenRead(bool abRead);
};

ASSERT_SIZE(BGSNote, 0x80);