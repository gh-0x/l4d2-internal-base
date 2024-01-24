#include "c_debug_overlay.h"

bool debug_overlay::screen_position(const vec3& in, vec3& out)
{
	using original_fn = bool(__thiscall*)(debug_overlay*, const vec3&, vec3&);
	return (*(original_fn * *)this)[12](this, in, out);
}