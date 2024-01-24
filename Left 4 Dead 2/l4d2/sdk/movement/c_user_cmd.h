#pragma once

#include "../vec/vec.h"

enum FL {
	fl_on_ground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_water_jump = (1 << 2),
	fl_on_train = (1 << 3),
	fl_frozen = (1 << 5),
	fl_aicontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8)
};

enum player_controls
{
	in_attack = (1 << 0),
	in_jump = (1 << 1),
	in_duck = (1 << 2),
	in_forward = (1 << 3),
	in_back = (1 << 4),
	in_use = (1 << 5),
	in_cancel = (1 << 6),
	in_left = (1 << 7),
	in_right = (1 << 8),
	in_moveleft = (1 << 9),
	in_moveright = (1 << 10),
	in_attack2 = (1 << 11),
	in_run = (1 << 12),
	in_reload = (1 << 13),
	in_alt1 = (1 << 14),
	in_alt2 = (1 << 15),
	in_score = (1 << 16),
	in_speed = (1 << 17),
	in_walk = (1 << 18),
	in_zoom = (1 << 19),
	in_weapon1 = (1 << 20),
	in_weapon2 = (1 << 21),
	in_bullrush = (1 << 22)
};

class c_user_cmd {
public:
	virtual ~c_user_cmd() {};
	int command_number;
	int tick_count;
	vec3 viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
};