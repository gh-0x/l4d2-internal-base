#include "config.h"

#include "../../utils/utils.h"

#include <filesystem>
#include <fstream>

#include <xtea/xtea.h>
#include <json/json.h>

config g_cfg;
vars g_var;

void config::initialize()
{
	m_cfg_directory = g_filesystem.get_module_directory() + X_("\\");
	m_cfg_directory += X_(CONFIG_DIRNAME);

	if (g_filesystem.object_exists(m_cfg_directory.c_str()).as(is_failed))
		std::filesystem::create_directory(m_cfg_directory.c_str());
}

void config::load_cfg(const std::string& path)
{
	std::string m_file_directory = m_cfg_directory + X_("\\") + path;
	std::ifstream target(m_file_directory);

	if (!target.is_open())
		return;

	g_xtea.decode(m_file_directory);

	Json::Value load;

	target >> load;

	g_var.m_trigger_bot_var = load[X_("triggerbot")][X_("enabled")].asBool();
	g_var.m_trigger_bot_head = load[X_("triggerbot")][X_("hit.head")].asBool();
	g_var.m_trigger_bot_body = load[X_("triggerbot")][X_("hit.body")].asBool();
	g_var.m_trigger_bot_left_arm = load[X_("triggerbot")][X_("hit.left_arm")].asBool();
	g_var.m_trigger_bot_right_arm = load[X_("triggerbot")][X_("hit.right_arm")].asBool();
	g_var.m_trigger_bot_left_leg = load[X_("triggerbot")][X_("hit.left_leg")].asBool();
	g_var.m_trigger_bot_right_leg = load[X_("triggerbot")][X_("hit.right_leg")].asBool();

	g_var.m_knifebot_var = load[X_("knifebot")][X_("enabled")].asBool();
	g_var.m_knifebot_team_var = load[X_("knifebot")][X_("team")].asBool();
	g_var.m_knifebot_distance_var = load[X_("knifebot")][X_("distance")].asFloat();

	g_var.m_visuals_drop_var = load[X_("visuals")][X_("drop")].asBool();
	g_var.m_visuals_drop_type_var = load[X_("visuals")][X_("drop.type")].asInt();
	g_var.m_visuals_drop_distance = load[X_("visuals")][X_("drop.distance")].asFloat();

	g_var.m_visuals_drop_color_var[0] = load[X_("visuals")][X_("drop.r")].asFloat();
	g_var.m_visuals_drop_color_var[1] = load[X_("visuals")][X_("drop.g")].asFloat();
	g_var.m_visuals_drop_color_var[2] = load[X_("visuals")][X_("drop.b")].asFloat();
	g_var.m_visuals_drop_color_var[3] = load[X_("visuals")][X_("drop.a")].asFloat();

	g_var.m_esp_infected_var = load[X_("visuals")][X_("infected")].asBool();
	g_var.m_esp_infected_distance_var = load[X_("visuals")][X_("infected.distance")].asFloat();
	g_var.m_esp_infected_color_var[0] = load[X_("visuals")][X_("infected.r")].asFloat();
	g_var.m_esp_infected_color_var[1] = load[X_("visuals")][X_("infected.g")].asFloat();
	g_var.m_esp_infected_color_var[2] = load[X_("visuals")][X_("infected.b")].asFloat();
	g_var.m_esp_infected_color_var[3] = load[X_("visuals")][X_("infected.a")].asFloat();

	g_var.m_esp_special_infected_var = load[X_("visuals")][X_("spec_infected")].asBool();
	g_var.m_esp_special_infected_color_var[0] = load[X_("visuals")][X_("spec_infected.r")].asFloat();
	g_var.m_esp_special_infected_color_var[1] = load[X_("visuals")][X_("spec_infected.g")].asFloat();
	g_var.m_esp_special_infected_color_var[2] = load[X_("visuals")][X_("spec_infected.b")].asFloat();
	g_var.m_esp_special_infected_color_var[3] = load[X_("visuals")][X_("spec_infected.a")].asFloat();

	g_var.m_esp_player_name_var = load[X_("visuals")][X_("player")].asBool();
	g_var.m_esp_player_name_color_var[0] = load[X_("visuals")][X_("player.r")].asFloat();
	g_var.m_esp_player_name_color_var[1] = load[X_("visuals")][X_("player.g")].asFloat();
	g_var.m_esp_player_name_color_var[2] = load[X_("visuals")][X_("player.b")].asFloat();
	g_var.m_esp_player_name_color_var[3] = load[X_("visuals")][X_("player.a")].asFloat();

	g_var.m_speed_hack_var = load[X_("misc")][X_("speed_hack")].asBool();
	g_var.m_speed_hack_speed_var = load[X_("misc")][X_("speed_hack.speed")].asFloat();

	g_var.m_bunny_hop_var = load[X_("misc")][X_("bunnyhop")].asBool();

	g_xtea.encode(m_file_directory);
}

void config::save_cfg(const std::string& path)
{
	std::string m_file_directory = m_cfg_directory + X_("\\") + path;
	std::ofstream target(m_file_directory);

	if (!target.is_open())
		return;

	Json::Value save;

	save[X_("triggerbot")][X_("enabled")] = g_var.m_trigger_bot_var;
	save[X_("triggerbot")][X_("hit.head")] = g_var.m_trigger_bot_head;
	save[X_("triggerbot")][X_("hit.body")] = g_var.m_trigger_bot_body;
	save[X_("triggerbot")][X_("hit.left_arm")] = g_var.m_trigger_bot_left_arm;
	save[X_("triggerbot")][X_("hit.right_arm")] = g_var.m_trigger_bot_right_arm;
	save[X_("triggerbot")][X_("hit.left_leg")] = g_var.m_trigger_bot_left_leg;
	save[X_("triggerbot")][X_("hit.right_leg")] = g_var.m_trigger_bot_right_leg;

	save[X_("knifebot")][X_("enabled")] = g_var.m_knifebot_var;
	save[X_("knifebot")][X_("team")] = g_var.m_knifebot_team_var;
	save[X_("knifebot")][X_("distance")] = g_var.m_knifebot_distance_var;

	save[X_("visuals")][X_("drop")] = g_var.m_visuals_drop_var;
	save[X_("visuals")][X_("drop.type")] = g_var.m_visuals_drop_type_var;
	save[X_("visuals")][X_("drop.distance")] = g_var.m_visuals_drop_distance;

	save[X_("visuals")][X_("drop.r")] = g_var.m_visuals_drop_color_var[0];
	save[X_("visuals")][X_("drop.g")] = g_var.m_visuals_drop_color_var[1];
	save[X_("visuals")][X_("drop.b")] = g_var.m_visuals_drop_color_var[2];
	save[X_("visuals")][X_("drop.a")] = g_var.m_visuals_drop_color_var[3];

	save[X_("visuals")][X_("infected")] = g_var.m_esp_infected_var;
	save[X_("visuals")][X_("infected.distance")] = g_var.m_esp_infected_distance_var;
	save[X_("visuals")][X_("infected.r")] = g_var.m_esp_infected_color_var[0];
	save[X_("visuals")][X_("infected.g")] = g_var.m_esp_infected_color_var[1];
	save[X_("visuals")][X_("infected.b")] = g_var.m_esp_infected_color_var[2];
	save[X_("visuals")][X_("infected.a")] = g_var.m_esp_infected_color_var[3];

	save[X_("visuals")][X_("spec_infected")] = g_var.m_esp_special_infected_var;
	save[X_("visuals")][X_("spec_infected.r")] = g_var.m_esp_special_infected_color_var[0];
	save[X_("visuals")][X_("spec_infected.g")] = g_var.m_esp_special_infected_color_var[1];
	save[X_("visuals")][X_("spec_infected.b")] = g_var.m_esp_special_infected_color_var[2];
	save[X_("visuals")][X_("spec_infected.a")] = g_var.m_esp_special_infected_color_var[3];

	save[X_("visuals")][X_("player")] = g_var.m_esp_player_name_var;
	save[X_("visuals")][X_("player.r")] = g_var.m_esp_player_name_color_var[0];
	save[X_("visuals")][X_("player.g")] = g_var.m_esp_player_name_color_var[1];
	save[X_("visuals")][X_("player.b")] = g_var.m_esp_player_name_color_var[2];
	save[X_("visuals")][X_("player.a")] = g_var.m_esp_player_name_color_var[3];

	save[X_("misc")][X_("speed_hack")] = g_var.m_speed_hack_var;
	save[X_("misc")][X_("speed_hack.speed")] = g_var.m_speed_hack_speed_var;

	save[X_("misc")][X_("bunnyhop")] = g_var.m_bunny_hop_var;

	target << save;
	target.close();

	g_xtea.encode(m_file_directory);
}