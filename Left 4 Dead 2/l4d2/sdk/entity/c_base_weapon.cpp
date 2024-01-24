#include "c_base_entity.h"

#include "../../pattern_list/pattern_list.h"
#include "../../../utils/utils.h"

int c_base_weapon::get_weapon_id()
{
	return *(int*)(reinterpret_cast<uintptr_t>(this) + 0x958);
}

m_weapon_id c_base_weapon::get_item_definition_index()
{
	using original_fn = m_weapon_id(__thiscall*)(c_base_weapon*);
	return (*(original_fn * *)this)[383](this);
}

bool c_base_weapon::is_allowed_to_switch()
{
	using original_fn = bool(__thiscall*)(c_base_weapon*);
	return (*(original_fn * *)this)[10](this);
}

bool c_base_weapon::can_be_selected()
{
	using original_fn = bool(__thiscall*)(c_base_weapon*);
	return (*(original_fn * *)this)[11](this);
}

bool c_base_weapon::visible_in_weapon_selection()
{
	using original_fn = bool(__thiscall*)(c_base_weapon*);
	return (*(original_fn * *)this)[12](this);
}

bool c_base_weapon::has_ammo()
{
	using original_fn = bool(__thiscall*)(c_base_weapon*);
	return (*(original_fn * *)this)[13](this);
}

file_weapon_info_t* c_base_weapon::get_weapon_data()
{
	using original_fn = file_weapon_info_t*(__thiscall*)(c_base_weapon*);
	static original_fn fn = reinterpret_cast<original_fn>(g_pl.m_get_weapon_data_fn);
	return fn(this);
}