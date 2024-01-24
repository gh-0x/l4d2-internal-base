#include "iachievement.h"

int i_achievement::get_achievement_id()
{
	using original_fn = int(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[1](this);
}

const char* i_achievement::get_name()
{
	using original_fn = const char*(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[2](this);
}

int i_achievement::get_flags()
{
	using original_fn = int(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[3](this);
}

int i_achievement::get_goal()
{
	using original_fn = int(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[4](this);
}

int i_achievement::get_count()
{
	using original_fn = int(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[5](this);
}

bool i_achievement::is_achieved()
{
	using original_fn = bool(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[6](this);
}

int i_achievement::get_point_value()
{
	using original_fn = int(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[7](this);
}

bool i_achievement::should_save_with_game()
{
	using original_fn = bool(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[8](this);
}

bool i_achievement::should_hide_until_achieved()
{
	using original_fn = bool(__thiscall*)(i_achievement*);
	return (*(original_fn * *)this)[9](this);
}