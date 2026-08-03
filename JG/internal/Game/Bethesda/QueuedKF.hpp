#pragma once

#include "QueuedFileEntry.hpp"
#include "KFModel.hpp"

class QueuedKF : public QueuedFileEntry {
public:
	QueuedKF();
	~QueuedKF();
	
	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			ALREADY_LOADED	= 1u << 0,
		};

		bool bAlreadyLoaded	: 1;
	};
	using Flags = _Flags::Flags;

	KFModelPtr			spKFModel;
	Bitfield<_Flags>	ucFlags;

	bool GetAlreadyLoaded() const;
	void SetAlreadyLoaded(bool abVal);
};

ASSERT_SIZE(QueuedKF, 0x38)