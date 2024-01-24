#pragma once

#include "../vec/vec3.h"

class collideable_t {
public:
	vec3& mins();
	vec3& maxs();
};