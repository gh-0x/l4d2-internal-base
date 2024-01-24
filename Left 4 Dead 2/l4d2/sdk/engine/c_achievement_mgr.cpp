#include "c_achievement_mgr.h"

i_achievement* achievement_mgr::get_achievement_by_index(int index, int player_slot)
{
	using original_fn = i_achievement * (__thiscall*)(achievement_mgr*, int, int);
	return (*(original_fn * *)this)[1](this, index, player_slot);
}

c_base_achievement* achievement_mgr::get_achievement_by_id(int id, int player_slot)
{
	using original_fn = c_base_achievement * (__thiscall*)(achievement_mgr*, int, int);
	return (*(original_fn * *)this)[2](this, id, player_slot);
}

int achievement_mgr::get_achievement_count(bool assets)
{
	using original_fn = int(__thiscall*)(achievement_mgr*, bool);
	return (*(original_fn * *)this)[3](this, assets);
}

void achievement_mgr::award_achievement(int achievement_id, int player_slot)
{
	using original_fn = void(__thiscall*)(achievement_mgr*, int, int);
	return (*(original_fn * *)this)[5](this, achievement_id, player_slot);
}