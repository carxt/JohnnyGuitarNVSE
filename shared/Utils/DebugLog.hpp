#pragma once

#include <cstdarg>

/**
 *	A simple debug log file
 *
 *	This class supports prefix blocks describing the source of the log event.
 *	It also allows logical blocks and outlining.\n
 */
class IDebugLog
{
public:
	IDebugLog();
	IDebugLog(const char* name);
	~IDebugLog();

	static void	__fastcall Open(const char* path);
	static void	__fastcall OpenRelative(int folderID, const char* relPath);

	static void	__fastcall Message(const char* message, const char* source = NULL);
	static void	__fastcall FormattedMessage(const char* fmt, ...);
	static void	__fastcall FormattedMessage(const char* fmt, va_list args);

	enum LogLevel
	{
		kLevel_FatalError = 0,
		kLevel_Error,
		kLevel_Warning,
		kLevel_Message,
		kLevel_VerboseMessage,
		kLevel_DebugMessage
	};

	static void	__fastcall Log(LogLevel level, const char* fmt, va_list args);

	static void	__fastcall SetSource(const char* source);
	static void	__fastcall ClearSource(void);

	static void	__fastcall Indent(void);
	static void	__fastcall Outdent(void);

	static void	__fastcall OpenBlock(void);
	static void	__fastcall CloseBlock(void);

	static void	__fastcall SetAutoFlush(bool inAutoFlush);

	static void	__fastcall SetLogLevel(LogLevel in) { logLevel = in; }
	static void	__fastcall SetPrintLevel(LogLevel in) { printLevel = in; }

private:
	static void	__fastcall MakeAllDirs(const char* path);

	static void	__fastcall PrintSpaces(int numSpaces);
	static void	__fastcall PrintText(const char* buf);
	static void	__fastcall NewLine(void);

	static void	__fastcall SeekCursor(int position);

	static int	__fastcall TabSize(void);
	static int	__fastcall RoundToTab(int spaces);

	static FILE* logFile;			//!< the output file

	static char			sourceBuf[16];		//!< name of current source, used in prefix
	static char			headerText[16];		//!< current text to use as line prefix
	static char			formatBuf[8192];	//!< temp buffer used for formatted messages

	static int			indentLevel;		//!< the current indentation level (in tabs)
	static int			rightMargin;		//!< the column at which text should be wrapped
	static int			cursorPos;			//!< current cursor position
	static int			inBlock;			//!< are we in a block?

	static bool			autoFlush;			//!< automatically flush the file after writing

	static LogLevel		logLevel;			//!< least important log level to write
	static LogLevel		printLevel;			//!< least important log level to print
};

extern IDebugLog gLog;

inline void _FATALERROR(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_FatalError, fmt, args);
	va_end(args);
}

inline void _ERROR(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_Error, fmt, args);
	va_end(args);
}

inline void _WARNING(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_Warning, fmt, args);
	va_end(args);
}

inline void _MESSAGE(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_Message, fmt, args);
	va_end(args);
}

inline void _VMESSAGE(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_VerboseMessage, fmt, args);
	va_end(args);
}

inline void _DMESSAGE(const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	gLog.Log(IDebugLog::kLevel_DebugMessage, fmt, args);
	va_end(args);
}
