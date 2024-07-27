#include "speedhack.h"

#include "../../config/config.h"
#include "../../input_manager/input_manager.h"
#include "../../modules/modules.h"
#include "../../globals/globals.h"

speedhack g_speed_hack;

void speedhack::run(c_user_cmd* cmd, float& m_speed)
{
	const float def_value = 1.0f;

	if (!g_var.m_speed_hack_var)
		return;

	if (!g_l4d2.m_engine->is_playing())
		return;

	if (!g.get_local())
		return;

	switch (g_var.m_speed_hack_mode_var) {
	case 0: {
		m_speed = g_input.is_key_down(0x45) ? g_var.m_speed_hack_speed_var : def_value;
		break;
	}
	case 1: {
		m_speed = (cmd->buttons & in_use) ? g_var.m_speed_hack_speed_var : def_value;
		break;
	}
	case 2: {
		m_speed = (cmd->buttons & in_speed) ? g_var.m_speed_hack_speed_var : def_value;
		break;
	}
	case 3: {
		m_speed = (cmd->buttons & in_attack) ? g_var.m_speed_hack_speed_var : def_value;
		break;
	}}
}