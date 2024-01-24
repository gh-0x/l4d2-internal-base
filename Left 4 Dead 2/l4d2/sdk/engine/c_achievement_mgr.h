#pragma once

#include "iachievement.h"

#define ACHIEVEMENTMGR_INTERFACE_VERSION "ACHIEVEMENTMGR_INTERFACE_VERSION001"

class achievement_mgr {
public:
	i_achievement* get_achievement_by_index(int index, int player_slot);
	c_base_achievement* get_achievement_by_id(int id, int player_slot);
	int get_achievement_count(bool assets = false);
	void award_achievement(int achievement_id, int player_slot);
};