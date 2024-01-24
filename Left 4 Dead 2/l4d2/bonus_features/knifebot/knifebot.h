#pragma once

#include "../../sdk/sdk.h"

struct knifebot {
public:
	void run(c_user_cmd* cmd);
};

extern knifebot g_knifebot;