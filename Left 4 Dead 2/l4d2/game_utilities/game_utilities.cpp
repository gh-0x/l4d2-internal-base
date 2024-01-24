#include "game_utilities.h"

#include "../modules/modules.h"

game_utils g_game;

static bool screen_transform(const vec3& in, vec3& out)
{
	auto& matrix = g_l4d2.m_engine->world_to_screen_matrix();

	out.x = matrix.m[0][0] * in.x + matrix.m[0][1] * in.y + matrix.m[0][2] * in.z + matrix.m[0][3];
	out.y = matrix.m[1][0] * in.x + matrix.m[1][1] * in.y + matrix.m[1][2] * in.z + matrix.m[1][3];
	out.z = 0.0f;

	float w = matrix.m[3][0] * in.x + matrix.m[3][1] * in.y + matrix.m[3][2] * in.z + matrix.m[3][3];

	if (w < 0.001f)
	{
		out.x *= 100000;
		out.y *= 100000;

		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool game_utils::w2s(const vec3& in, vec3& out, w2s_method method)
{
	if (method == in_game)
		return (g_l4d2.m_dbg_overlay->screen_position(in, out) != 1);

	int w, h;
	g_l4d2.m_engine->get_screen_size(w, h);

	if (!screen_transform(in, out))
		return false;

	out.x = (w / 2.0f) + (out.x * w) / 2.0f;
	out.y = (h / 2.0f) - (out.y * h) / 2.0f;

	return true;
}