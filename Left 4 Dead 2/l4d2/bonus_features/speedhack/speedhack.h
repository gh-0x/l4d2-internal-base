#pragma once

#include "../../sdk/sdk.h"

struct speedhack {
public:
	void run(c_user_cmd* cmd, float&);
};

extern speedhack g_speed_hack;