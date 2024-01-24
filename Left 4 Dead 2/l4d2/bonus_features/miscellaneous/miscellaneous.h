#pragma once

#include "../../sdk/sdk.h"

struct miscellaneous {
public:
	void run(c_user_cmd* cmd);
private:
	void bunny_hop(c_user_cmd* cmd);
};

extern miscellaneous g_misc;