#include "IFileStream.h"
#include <direct.h>

IFileStream::IFileStream()
:theFile(NULL)
{
	
}

IFileStream::IFileStream(const char * name)
:theFile(NULL)
{
	Open(name);
}

IFileStream::~IFileStream()
{
	Close();
}

/**
 *	Opens a file for reading and attaches it to the stream
 */
bool IFileStream::Open(const char *name)
{
	Close();
	theFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE) return false;
	streamLength = GetFileSize(theFile, NULL);
	streamOffset = 0;
	return true;
}

bool IFileStream::OpenWrite(const char *name)
{
	Close();
	theFile = CreateFile(name, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE) return false;
	streamOffset = streamLength = GetFileSize(theFile, NULL);
	SetFilePointer(theFile, streamLength, NULL, FILE_BEGIN);
	return true;
}

bool IFileStream::OpenWriteEx(char *name, bool append)
{
	MakeAllDirs(name);
	bool result = append ? OpenWrite(name) : Create(name);
	if (result && streamLength) Write8('\n');
	return result;
}

static UINT_PTR CALLBACK BrowseEventProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

bool IFileStream::BrowseOpen(void)
{
	bool			result = false;
	OPENFILENAME	info;
	char			path[4096];

	path[0] = 0;

	info.lStructSize =			sizeof(info);
	info.hwndOwner =			NULL;
	info.hInstance =			NULL;
	info.lpstrFilter =			NULL;
	info.lpstrCustomFilter =	NULL;
	info.nMaxCustFilter =		0;
	info.nFilterIndex =			0;
	info.lpstrFile =			path;
	info.nMaxFile =				sizeof(path);
	info.lpstrFileTitle =		NULL;
	info.nMaxFileTitle =		0;
	info.lpstrInitialDir =		NULL;
	info.lpstrTitle =			NULL;
	info.Flags =				OFN_EXPLORER | OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_ENABLEHOOK | OFN_NOCHANGEDIR;
	info.lpstrDefExt =			NULL;
	info.lCustData =			NULL;
	info.lpfnHook =				BrowseEventProc;
	info.lpTemplateName =		NULL;
//	info.pvReserved =			NULL;
//	info.dwReserved =			NULL;
//	info.FlagsEx =				0;

	if(GetOpenFileName(&info))
	{
		result = Open(path);
	}

	return result;
}

/**
 *	Creates a new file for writing, overwriting any previously-existing files,
 *	and attaches it to the stream
 */
bool IFileStream::Create(const char *name)
{
	Close();
	theFile = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (theFile == INVALID_HANDLE_VALUE) return false;
	streamOffset = streamLength = 0;
	return true;
}

bool IFileStream::BrowseCreate(const char * defaultName, const char * defaultPath, const char * title)
{
	bool			result = false;
	OPENFILENAME	info;
	char			path[4096];

	if(defaultName)
		strcpy_s(path, sizeof(path), defaultName);

	info.lStructSize =			sizeof(info);
	info.hwndOwner =			NULL;
	info.hInstance =			NULL;
	info.lpstrFilter =			NULL;
	info.lpstrCustomFilter =	NULL;
	info.nMaxCustFilter =		0;
	info.nFilterIndex =			0;
	info.lpstrFile =			path;
	info.nMaxFile =				sizeof(path);
	info.lpstrFileTitle =		NULL;
	info.nMaxFileTitle =		0;
	info.lpstrInitialDir =		defaultPath;
	info.lpstrTitle =			title;
	info.Flags =				OFN_EXPLORER | OFN_ENABLESIZING | OFN_ENABLEHOOK |
								OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
	info.lpstrDefExt =			NULL;
	info.lCustData =			NULL;
	info.lpfnHook =				BrowseEventProc;
	info.lpTemplateName =		NULL;
//	info.pvReserved =			NULL;
//	info.dwReserved =			NULL;
//	info.FlagsEx =				0;

	if(GetSaveFileName(&info))
	{
		result = Create(path);
	}

	return result;
}

/**
 *	Closes the current file
 */
void IFileStream::Close(void)
{
	if(theFile)
	{
		CloseHandle(theFile);
		theFile = NULL;
	}
}

void IFileStream::ReadBuf(void * buf, UInt32 inLength)
{
	UInt32	bytesRead;

	ReadFile(theFile, buf, inLength, &bytesRead, NULL);

	streamOffset += bytesRead;
}

void IFileStream::WriteBuf(const void * buf, UInt32 inLength)
{
	UInt32	bytesWritten;

	// check for file expansion
	if(streamOffset > streamLength)
		SetEndOfFile(theFile);

	WriteFile(theFile, buf, inLength, &bytesWritten, NULL);

	streamOffset += bytesWritten;

	if(streamLength < streamOffset)
		streamLength = streamOffset;
}

void IFileStream::SetOffset(UInt32 inOffset)
{
	SetFilePointer(theFile, inOffset, NULL, FILE_BEGIN);
	streamOffset = inOffset;
}

void IFileStream::MakeAllDirs(char *path)
{
	char *traverse = path, curr;
	while (curr = *traverse)
	{
		if ((curr == '\\') || (curr == '/'))
		{
			*traverse = 0;
			_mkdir(path);
			*traverse = '\\';
		}
		traverse++;
	}
}

char * IFileStream::ExtractFileName(char * path)
{
	char	* traverse = path;
	char	* lastSlash = NULL;

	while(1)
	{
		char	data = *traverse++;

		if((data == '\\') || (data == '/'))
			lastSlash = traverse;

		if(!data)
			break;
	}

	return lastSlash;
}
