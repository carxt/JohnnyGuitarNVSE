#pragma once

#include <string>
#include <vector>

#include "nvse/PluginAPI.h"

class PluginManager
{
public:
	PluginManager();
	~PluginManager();

	bool	Init(void);
	void	DeInit(void);

	PluginInfo *	GetInfoByName(const char * name);
	PluginInfo *	GetInfoFromHandle(PluginHandle handle);
	PluginInfo *	GetInfoFromBase(uint32_t baseOpcode);
	const char *	GetPluginNameFromHandle(PluginHandle handle);

	uint32_t			GetNumPlugins(void);
	uint32_t			GetBaseOpcode(uint32_t idx);
	PluginHandle	LookupHandleFromBaseOpcode(uint32_t baseOpcode);
	PluginHandle	LookupHandleFromName(const char* pluginName);
	PluginHandle	LookupHandleFromPath(const char* pluginPath);

	static bool			RegisterCommand(CommandInfo * _info);
	static bool			RegisterTypedCommand(CommandInfo * _info, CommandReturnType retnType);
	static void			SetOpcodeBase(uint32_t opcode);
	static void *		QueryInterface(uint32_t id);
	static PluginHandle	GetPluginHandle(void);
	static const char *	GetFalloutDir();

	static bool Dispatch_Message(PluginHandle sender, uint32_t messageType, void * data, uint32_t dataLen, const char* receiver);
	static bool	RegisterListener(PluginHandle listener, const char* sender, NVSEMessagingInterface::EventCallback handler);

private:
	struct LoadedPlugin
	{
		HMODULE		handle;
		PluginInfo	info;
		uint32_t		baseOpcode;

		_NVSEPlugin_Query	query;
		_NVSEPlugin_Load	load;

		char path[MAX_PATH];			// Added version 4.5 Beta 7
	};

	bool	FindPluginDirectory(void);
	bool	InstallPlugin(std::string pluginPath);
	void	InstallPlugins(void);

	const char *	SafeCallQueryPlugin(LoadedPlugin * plugin, const NVSEInterface * nvse);
	const char *	SafeCallLoadPlugin(LoadedPlugin * plugin, const NVSEInterface * nvse);

	const char *	CheckPluginCompatibility(LoadedPlugin * plugin);

	typedef std::vector <LoadedPlugin>	LoadedPluginList;

	std::string			m_pluginDirectory;
	LoadedPluginList	m_plugins;

	static LoadedPlugin		* s_currentLoadingPlugin;
	static PluginHandle		s_currentPluginHandle;
};

extern PluginManager	g_pluginManager;

extern CommandInfo kCommandInfo_IsPluginInstalled;
extern CommandInfo kCommandInfo_GetPluginVersion;
