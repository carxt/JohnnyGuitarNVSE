#pragma once

#include "common/IDataStream.h"

/**
 *	An input file stream
 */
class IFileStream : public IDataStream
{
	public:
		IFileStream();
		IFileStream(const char * name);
		~IFileStream();

		bool	Open(const char * name);
		bool	OpenWrite(const char * name);
		bool	OpenWriteEx(char *name, bool append);
		bool	BrowseOpen(void);

		bool	Create(const char * name);
		bool	BrowseCreate(const char * defaultName = NULL, const char * defaultPath = NULL, const char * title = NULL);

		void	Close(void);

		HANDLE	GetHandle(void)	{ return theFile; }

		virtual void	ReadBuf(void * buf, UInt32 inLength);
		virtual void	WriteBuf(const void * buf, UInt32 inLength);
		virtual void	SetOffset(UInt32 inOffset);

		static void		MakeAllDirs(char *path);
		static char		*ExtractFileName(char * path);

	protected:
		HANDLE	theFile;
};
