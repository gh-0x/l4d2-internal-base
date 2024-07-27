#include "knifebot.h"

#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../modules/modules.h"

knifebot g_knifebot;

void knifebot::run(c_user_cmd* cmd)
{
	if (!g_var.m_knifebot_var)
		return;

	if (!g_l4d2.m_engine->is_playing())
		return;

	if (!g.get_local())
		return;

	for (auto i = 1; i < g_l4d2.m_entity_list->get_max_entity(); i++)
	{
		if (i == g_l4d2.m_engine->get_local_player())
			continue;

		auto entity = reinterpret_cast<c_base_player*>(g_l4d2.m_entity_list->get_client_entity(i));

		if (!entity)
			continue;

		if (entity->team() == g.get_local()->team() & !g_var.m_knifebot_team_var)
			continue;

		auto distance = g.get_local()->get_eye_pos().distance_to(entity->get_eye_pos());

		if (is_gun_weapon(g.get_local()->get_active_weapon()->get_item_definition_index()))
			return;

		if (distance <= g_var.m_knifebot_distance_var)
			cmd->buttons |= in_attack;
	}
}