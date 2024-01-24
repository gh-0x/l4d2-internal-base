#include "c_collideable.h"

vec3& collideable_t::mins() {
	using original_fn = vec3 & (__thiscall*)(void*);
	return (*(original_fn * *)this)[1](this);
}

vec3& collideable_t::maxs() {
	using original_fn = vec3 & (__thiscall*)(void*);
	return (*(original_fn * *)this)[2](this);
}