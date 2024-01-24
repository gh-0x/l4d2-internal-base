#pragma once

#include "../../std.h"

struct config {
public:
	void initialize();
public:
	void load_cfg(std::string file);
	void save_cfg(std::string file);
private:
	std::string m_cfg_directory;
};

struct vars {
public:
	bool m_auto_pistol_var;
	bool m_trigger_bot_var;
	bool m_trigger_bot_team_var;
	bool m_trigger_bot_head = true;
	bool m_trigger_bot_body = true;
	bool m_trigger_bot_left_arm = true;
	bool m_trigger_bot_right_arm = true;
	bool m_trigger_bot_left_leg = true;
	bool m_trigger_bot_right_leg = true;
	float m_knifebot_distance_var = 40.0f;
	bool m_knifebot_var;
	bool m_knifebot_team_var;
	bool m_visuals_drop_var;
	int m_visuals_drop_type_var;
	float m_visuals_drop_distance = 2000.0f;
	float m_visuals_drop_color_var[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool m_esp_infected_var;
	float m_esp_infected_distance_var = 2000.0f;
	float m_esp_infected_color_var[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool m_esp_special_infected_var;
	float m_esp_special_infected_color_var[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool m_esp_player_name_var;
	float m_esp_player_name_color_var[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool m_speed_hack_var;
	int m_speed_hack_mode_var;
	float m_speed_hack_speed_var = 1.0f;
	bool m_bunny_hop_var;
};

extern config g_cfg;
extern vars g_var;