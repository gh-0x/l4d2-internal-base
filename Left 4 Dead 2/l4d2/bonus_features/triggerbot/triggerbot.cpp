#include "triggerbot.h"

#include "../../math/math.h"
#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../modules/modules.h"

#include "../../sdk/vec/vec3.h"

triggerbot g_triggerbot;

void triggerbot::run(c_user_cmd* cmd)
{
	if (!g_var.m_trigger_bot_var)
		return;

	if (!g_l4d2.m_engine->is_playing())
		return;

	if (!g.get_local())
		return;

	vec3 view_angles = cmd->viewangles;
	vec3 cross_forward;

	g_math.angle_vectors(view_angles, cross_forward);

	cross_forward *= 8192.0f;

	vec3 src = g.get_local()->get_eye_pos();
	vec3 dest = src + cross_forward;

	ray_t ray(src, dest);
	trace_class trace;
	trace_filter me = g.get_local();

	g_l4d2.m_tracers->get_trace_ray(ray, &me, &trace);

	if (!trace.entity)
		return;

	if (!g_var.m_trigger_bot_team_var && g.get_local()->team() == trace.entity->team())
		return;

	if (is_not_weapon_gun(g.get_local()->get_active_weapon()->get_item_definition_index()))
		return;

	if (!g.get_local()->get_active_weapon()->has_ammo())
		return;

	if ((g_var.m_trigger_bot_head && trace.hitgroup == m_hitgroup::hitgroup_head)
		|| (g_var.m_trigger_bot_body && trace.hitgroup == m_hitgroup::hitgroup_chest)
		|| (g_var.m_trigger_bot_body && trace.hitgroup == m_hitgroup::hitgroup_stomach)
		|| (g_var.m_trigger_bot_left_arm && trace.hitgroup == m_hitgroup::hitgroup_left_arm)
		|| (g_var.m_trigger_bot_right_arm && trace.hitgroup == m_hitgroup::hitgroup_right_arm)
		|| (g_var.m_trigger_bot_left_leg && trace.hitgroup == m_hitgroup::hitgroup_left_leg)
		|| (g_var.m_trigger_bot_right_leg && trace.hitgroup == m_hitgroup::hitgroup_right_leg))

		cmd->buttons |= player_controls::in_attack;
}