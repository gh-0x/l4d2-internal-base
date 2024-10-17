#include "math.h"
#include <cmath>

math g_math;

void math::sin_cos(float radians, float* sine, float* cosine)
{
	*sine = std::sin(radians);
	*cosine = std::cos(radians);
}

void math::angle_vectors(vec3 angles, vec3& f)
{
	float sp, sy, sr, cp, cy, cr;

	sin_cos(DEG2RAD(angles[0]), &sp, &cp);
	sin_cos(DEG2RAD(angles[1]), &sy, &cy);
	sin_cos(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;
}
