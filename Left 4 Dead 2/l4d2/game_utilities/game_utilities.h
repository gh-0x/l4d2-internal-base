#pragma once

#include "../../std.h"

class vec3;

enum w2s_method {
	custom,
	in_game
};

struct game_utils {
public:
	bool w2s(const vec3& in, vec3& out, w2s_method method = w2s_method::in_game);
};

extern game_utils g_game;