#include "c_engine_vgui.h"

unsigned int enginevgui::get_panel_type(panel_t panel_id)
{
	using original_fn = unsigned int(__thiscall*)(enginevgui*, panel_t);
	return (*(original_fn * *)this)[1](this, panel_id);
}

bool enginevgui::is_game_ui_visible()
{
	using original_fn = bool(__thiscall*)(enginevgui*);
	return (*(original_fn * *)this)[2](this);
}