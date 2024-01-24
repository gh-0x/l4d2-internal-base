#pragma once

#include "../sdk/vec/vec3.h"

struct math {
public:
	void sin_cos(float radians, float* sine, float* cosine);
	void angle_vectors(vec3 angles, vec3& f);
};

extern math g_math;