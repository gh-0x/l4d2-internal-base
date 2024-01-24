#pragma once

#include "c_globals_vars_base.h"

#define PLAYER_INFO_MANAGER_INTERFACE_VERSION "PlayerInfoManager002"

class player_info_manager {
public:
	global_vars_base* get_global_vars();
};