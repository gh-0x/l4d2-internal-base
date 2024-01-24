#pragma once

#define ACH_LISTEN_KILL_EVENTS				0x0001
#define ACH_LISTEN_MAP_EVENTS				0x0002
#define ACH_LISTEN_COMPONENT_EVENTS			0x0004
#define ACH_HAS_COMPONENTS					0x0020
#define ACH_SAVE_WITH_GAME					0x0040
#define ACH_SAVE_GLOBAL						0x0080
#define ACH_FILTER_ATTACKER_IS_PLAYER		0x0100
#define ACH_FILTER_VICTIM_IS_PLAYER_ENEMY	0x0200
#define ACH_FILTER_FULL_ROUND_ONLY			0x0400

#define ACH_LISTEN_PLAYER_KILL_ENEMY_EVENTS		ACH_LISTEN_KILL_EVENTS | ACH_FILTER_ATTACKER_IS_PLAYER | ACH_FILTER_VICTIM_IS_PLAYER_ENEMY
#define ACH_LISTEN_KILL_ENEMY_EVENTS		ACH_LISTEN_KILL_EVENTS | ACH_FILTER_VICTIM_IS_PLAYER_ENEMY

class c_base_achievement;
class i_achievement {
public:
	int get_achievement_id();
	const char* get_name();
	int get_flags();
	int get_goal();
	int get_count();
	bool is_achieved();
	int get_point_value();
	bool should_save_with_game();
	bool should_hide_until_achieved();
};