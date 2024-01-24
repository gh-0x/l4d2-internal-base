#include "c_player_info_manager.h"

global_vars_base* player_info_manager::get_global_vars()
{
	using original_fn = global_vars_base*(__thiscall*)(player_info_manager*);
	return (*(original_fn**)this)[1](this);
}