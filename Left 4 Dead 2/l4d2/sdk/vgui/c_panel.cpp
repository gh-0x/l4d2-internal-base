#include "c_panel.h"

const char* panel::get_panel_name(unsigned int panel_id)
{
	using original_fn = const char* (__thiscall*)(panel*, unsigned int);
	return (*(original_fn * *)this)[36](this, panel_id);
}