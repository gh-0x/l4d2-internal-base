#pragma once

#include "../../sdk/sdk.h"

struct triggerbot {
public:
	void run(c_user_cmd* cmd);
};

extern triggerbot g_triggerbot;