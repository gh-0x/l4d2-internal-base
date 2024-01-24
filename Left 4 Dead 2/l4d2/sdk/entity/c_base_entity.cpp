#include "c_base_entity.h"

void* c_base_entity::networkable()
{
	return reinterpret_cast<void*>(uintptr_t(this) + 8);
}

collideable_t* c_base_entity::get_collideable()
{
	using original_fn = collideable_t * (__thiscall*)(void*);
	return (*(original_fn * *)this)[3](this);
}

vec3 c_base_entity::get_absolute_origin()
{
	if (!this)
		return vec3(0, 0, 0);

	using original_fn = vec3 & (__thiscall*)(c_base_entity*);
	return (*(original_fn * *)this)[10](this);
}

c_client_class* c_base_entity::client_class()
{
	using original_fn = c_client_class * (__thiscall*)(void*);
	return (*(original_fn * *)networkable())[1](networkable());
}

bool c_base_entity::is_dormant()
{
	using original_fn = bool(__thiscall*)(void*);
	return (*static_cast<original_fn**>(networkable()))[7](networkable());
}

vec3 c_base_entity::get_eye_pos()
{
	return origin() + view_offset();
}