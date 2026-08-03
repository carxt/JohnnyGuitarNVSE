#pragma once

#include "BipedAnim.hpp"
#include "QueuedFile.hpp"

class QueuedModel;
class BSFaceGenModel;

class QueuedHelmet : public QueuedFile {
public:
	QueuedHelmet();
	virtual ~QueuedHelmet();

	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			FINISHED_QUEUING = 1u << 0,
		};

		bool bFinishedQueuing : 1;
	};
	using Flags = _Flags::Flags;

	BipedAnim*					pBipedAnim;
	NiPointer<QueuedModel>		spQueuedHelmetModels[20];
	NiPointer<BSFaceGenModel>	spHelmetFaceGenModels[20];
	NiPointer<NiNode>			spClonedHelmetNodes[20];
	TESObjectREFR*				pRef;
	Bitfield<_Flags>			ucFlags;

	bool GetFinishedQueuing() const;
	void SetFinishedQueuing(bool abVal);
};

ASSERT_SIZE(QueuedHelmet, 0x128)