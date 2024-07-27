#include "miscellaneous.h"

#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../modules/modules.h"

miscellaneous g_misc;

void miscellaneous::run(c_user_cmd* cmd)
{
	if (!g_l4d2.m_engine->is_playing())
		return;

	if (g_var.m_bunny_hop_var)
		bunny_hop(cmd);
}

void miscellaneous::bunny_hop(c_user_cmd* cmd)
{
	static auto jumped_last_tick = false;
	static auto should_fake_jump = false;

	if (!g.get_local())
		return;

	if (!jumped_last_tick && should_fake_jump)
	{
		should_fake_jump = false;
		cmd->buttons |= in_jump;
	}
	else if (cmd->buttons & in_jump)
	{
		if (g.get_local()->get_flags() & fl_on_ground)
		{
			jumped_last_tick = true;
			should_fake_jump = true;
		}
		else
		{
			cmd->buttons &= ~in_jump;
			jumped_last_tick = false;
		}
	}
	else
	{
		jumped_last_tick = false;
		should_fake_jump = false;
	}
}