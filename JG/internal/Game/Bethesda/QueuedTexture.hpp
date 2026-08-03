#pragma once

#include "QueuedFileEntry.hpp"
#include "Gamebryo/NiSourceTexture.hpp"

class QueuedTexture : public QueuedFileEntry {
public:
	QueuedTexture();
	~QueuedTexture();

	struct ALIGN1 _Flags {
		enum Flags : uint8_t {
			ALREADY_LOADED			= 1u << 0,
			LOAD_DEGRADED			= 1u << 1,
			IN_QUEUED_TEXTURE_MAP	= 1u << 2,
		};

		bool bAlreadyLoaded			: 1;
		bool bLoadDegraded			: 1;
		bool bInQueuedTextureMap	: 1;
	};
	using Flags = _Flags::Flags;

	NiTexturePtr		spTexture;
	Bitfield<_Flags>	ucFlags;

	bool GetAlreadyLoaded() const;
	void SetAlreadyLoaded(bool abVal);

	bool GetLoadDegraded() const;
	void SetLoadDegraded(bool abVal);

	bool GetInQueuedTextureMap() const;
	void SetInQueuedTextureMap(bool abVal);
};

ASSERT_SIZE(QueuedTexture, 0x38)