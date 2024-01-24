#pragma once

#include "../../std.h"

#include "steamworks/steamworks.h"
#include "d3dx9.h"

#include "../sdk/sdk.h"

struct l4d2 {
public:
	void initialize();
	void undo();
private:
	template <typename m_interface>
	m_interface* get_interface(const std::string& module_name, const std::string& interface_name);
	template <typename m_steam_interface>
	m_steam_interface get_steam_interface(const std::string& interface_name);
	DWORD_PTR get_module_base_address();
public:
	engine_client* m_engine;
	entity_list* m_entity_list;
	surface* m_surface;
	player_info_manager* m_player_manager;
	global_vars_base* m_globals;
	panel* m_panel;
	base_client* m_client;
	IDirect3DDevice9* m_device;
	client_mode* m_client_mode;
	trace_ray* m_tracers;
	debug_overlay* m_dbg_overlay;
	inputsystem* m_input_system;
	enginevgui* m_engine_vgui;
	model_info* m_model_info;
	ISteamClient* m_steam_client;
	ISteamUser* m_steam_user;
	ISteamUtils* m_steam_utils;
	ISteamFriends* m_steam_friends;
	ISteamInventory* m_steam_inventory;
	ISteamGameCoordinator* m_steam_game_coordinator;
};

extern l4d2 g_l4d2;