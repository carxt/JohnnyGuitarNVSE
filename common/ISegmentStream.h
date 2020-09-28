#pragma once

#include "common/IDataStream.h"
#include <vector>

/**
 *	An stream composed of many non-contiguous segments of a larger stream
 */
class ISegmentStream : public IDataStream
{
	public:
		ISegmentStream();
		~ISegmentStream();

		void	AttachStream(IDataStream * inStream);
		
		void	AddSegment(UInt32 offset, UInt32 length, UInt32 parentOffset);

		virtual void	ReadBuf(void * buf, UInt32 inLength);
		virtual void	WriteBuf(const void * buf, UInt32 inLength);
		virtual void	SetOffset(UInt32 inOffset);

	protected:
		IDataStream	* parent;

		struct SegmentInfo
		{
			SegmentInfo(UInt32 inOffset, UInt32 inLength, UInt32 inParentOffset)
			{
				offset = inOffset;
				length = inLength;
				parentOffset = inParentOffset;
			}

			UInt32	offset;
			UInt32	length;
			UInt32	parentOffset;
		};

		typedef std::vector <SegmentInfo>	SegmentInfoListType;
		SegmentInfoListType					segmentInfo;

		SegmentInfo *	LookupInfo(UInt32 offset);
};
