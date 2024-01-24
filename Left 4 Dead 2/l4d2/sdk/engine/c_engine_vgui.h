#pragma once

#define VENGINE_VGUI_VERSION "VEngineVGui001"

enum panel_t : unsigned int {
	panel_root = 0,
	panel_gameuidll,
	panel_clientdll,
	panel_tools,
	panel_ingamescreens,
	panel_gamedll,
	panel_clientdll_tools,
	panel_gameuibackground,
	panel_transitioneffect,
	panel_steamoverlay
};

class enginevgui {
public:
	unsigned int get_panel_type(panel_t panel_id);
	bool is_game_ui_visible();
};