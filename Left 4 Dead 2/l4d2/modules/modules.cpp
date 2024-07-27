#include "modules.h"

#include "../globals/globals.h"
#include "../pattern_list/pattern_list.h"
#include "../../utils/utils.h"

l4d2 g_l4d2;

void l4d2::initialize()
{
	g_console.initialize(X_("Left 4 Dead 2"));

	g_pl.initialize();

	m_client = get_interface<base_client>(X_("client.dll"), X_(CLIENT_INTERFACE_VERSION));
	m_engine = get_interface<engine_client>(X_("engine.dll"), X_(ENGINE_INTERFACE_VERSION));
	m_entity_list = get_interface<entity_list>(X_("client.dll"), X_(CLIENT_ENTITY_INTERFACE_VERSION));
	m_surface = get_interface<surface>(X_("vguimatsurface.dll"), X_(VGUI_MAT_SURFACE_INTERFACE_VERSION));
	m_player_manager = get_interface<player_info_manager>(X_("server.dll"), X_(PLAYER_INFO_MANAGER_INTERFACE_VERSION));
	m_panel = get_interface<panel>(X_("vgui2.dll"), X_(VGUI_INTERFACE_VERSION));
	m_engine_vgui = get_interface<enginevgui>(X_("engine.dll"), X_(VENGINE_VGUI_VERSION));
	m_tracers = get_interface<trace_ray>(X_("engine.dll"), X_(TRACE_RAY_INTERFACE_VERSION));
	m_dbg_overlay = get_interface<debug_overlay>(X_("engine.dll"), X_(DEBUG_OVERLAY_INTERFACE_VERSION));
	m_input_system = get_interface<inputsystem>(X_("inputsystem.dll"), X_(INPUTSYSTEM_INTERFACE_VERSION));
	m_model_info = get_interface<model_info>(X_("engine.dll"), X_(MODEL_INFO_INTERFACE_VERSION));

	m_device = **reinterpret_cast<IDirect3DDevice9***>(g_pl.m_device_fn);
	m_globals = m_player_manager->get_global_vars();
	
	m_client_mode = **(client_mode***)(g_pl.m_client_mode_fn);

	m_steam_client = get_steam_interface<ISteamClient*>(
		X_(STEAMAPI_CLIENT)
	);
	
	m_steam_user = m_steam_client->GetISteamUser(
		get_steam_interface<HSteamUser>(X_(STEAMAPI_GETHSTEAMUSER)),
		get_steam_interface<HSteamPipe>(X_(STEAMAPI_GETHSTEAMPIPE)),
		X_(STEAMUSER_INTERFACE_VERSION)
	);
	
	m_steam_utils = m_steam_client->GetISteamUtils(
		get_steam_interface<HSteamPipe>(X_(STEAMAPI_GETHSTEAMPIPE)),
		X_(STEAMUTILS_INTERFACE_VERSION)
	);

	m_steam_friends = m_steam_client->GetISteamFriends(
		get_steam_interface<HSteamUser>(X_(STEAMAPI_GETHSTEAMUSER)),
		get_steam_interface<HSteamPipe>(X_(STEAMAPI_GETHSTEAMPIPE)),
		X_(STEAMFRIENDS_INTERFACE_VERSION)
	);

	m_steam_inventory = m_steam_client->GetISteamInventory(
		get_steam_interface<HSteamUser>(X_(STEAMAPI_GETHSTEAMUSER)),
		get_steam_interface<HSteamPipe>(X_(STEAMAPI_GETHSTEAMPIPE)),
		X_(STEAMINVENTORY_INTERFACE_VERSION)
	);

	m_steam_game_coordinator = (ISteamGameCoordinator*)m_steam_client->GetISteamGenericInterface(
		get_steam_interface<HSteamUser>(X_(STEAMAPI_GETHSTEAMUSER)),
		get_steam_interface<HSteamPipe>(X_(STEAMAPI_GETHSTEAMPIPE)),
		X_(STEAMGAMECOORDINATOR_INTERFACE_VERSION)
	);
}

void l4d2::undo()
{
	g_console.undo();
}

template <typename m_interface>
m_interface* l4d2::get_interface(const std::string& module_name, const std::string& interface_name)
{
	using create_interface_fn = void*(*)(const char*, int*);
	const auto fn = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA(module_name.c_str()), X_("CreateInterface")));

	if (!fn)
		return 0;

	return static_cast<m_interface*>(fn(interface_name.c_str(), {}));
}

template <typename m_steam_interface>
m_steam_interface l4d2::get_steam_interface(const std::string& interface_name)
{
	return ((m_steam_interface(__cdecl*)(void))GetProcAddress(GetModuleHandleA(X_("steam_api.dll")), interface_name.c_str()))();
}