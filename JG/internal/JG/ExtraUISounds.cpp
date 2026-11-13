#include "ExtraUISounds.hpp"
#include "Bethesda/BSAudio.hpp"
#include "Bethesda/BSGameSound.hpp"
#include "Bethesda/TESSound.hpp"

#include "Shared/SafeWrite/SafeWrite.hpp"

namespace ExtraUISounds {

	static uint32_t uiQuestSounds[QuestUpdateManager::UpdateType::COUNT] = {};

	namespace Hooks {

		static HookUtils::CallDetour kPlayQuestSoundDetour;
		class Hook {
		public:
			bool PlayQuestSound(bool abLoop) {
				constexpr uint32_t uiSoundFlags = BSGameSound::TypeFlags::IS_2D | BSGameSound::TypeFlags::ONE_SHOT | BSGameSound::TypeFlags::SYSTEM_SOUND;

				BSSoundHandle& rSound = *reinterpret_cast<BSSoundHandle*>(this);

				auto pIter = QuestUpdateManager::kQuestNames->GetHead();
				if (pIter && pIter->GetItem()) [[likely]] {
					const QuestUpdateManager::QuestUpdate* pUpdate = pIter->GetItem();
					const QuestUpdateManager::UpdateType eType = pUpdate->eUpdateType;
					if (eType < QuestUpdateManager::UpdateType::COUNT && uiQuestSounds[eType])
						rSound = BSAudio::GetSingleton()->GetSoundHandleByFormID(uiQuestSounds[eType], uiSoundFlags);
				}
				return ThisCall<bool>(kPlayQuestSoundDetour, this, abLoop);
			}
		};
	
		static void Init() {
			kPlayQuestSoundDetour.ReplaceCall(0x77A8E9, &Hook::PlayQuestSound);
		}

	}

	void Install() {
		Hooks::Init();
	}

	void __fastcall SetQuestSound(TESSound* apSound, QuestUpdateManager::UpdateType aeType) {
		if (aeType < QuestUpdateManager::UpdateType::COUNT)
			uiQuestSounds[aeType] = apSound ? apSound->GetFormID() : 0;
	}
}