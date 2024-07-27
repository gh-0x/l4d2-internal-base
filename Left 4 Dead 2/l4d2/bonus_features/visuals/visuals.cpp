#include "visuals.h"

#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../modules/modules.h"
#include "../../render_manager/render_manager.h"
#include "../../game_utilities/game_utilities.h"
#include "../../../utils/utils.h"

visuals g_visuals;

static void draw_drop(c_base_player* entity);
static void draw_other_drop(c_base_player* entity);

void visuals::run()
{
	if (!g_l4d2.m_engine->is_playing())
		return;

	if (!g.get_local())
		return;

	for (auto i = 1; i < g_l4d2.m_entity_list->get_max_entity(); i++)
	{
		auto entity = reinterpret_cast<c_base_player*>(g_l4d2.m_entity_list->get_client_entity(i));

		if (!entity)
			continue;

		if (g_var.m_visuals_drop_var)
		{
			draw_drop(entity);
			draw_other_drop(entity);
		}
	}
}

static void draw_drop(c_base_player* entity)
{
	c_client_class* m_classes = entity->client_class();

	if (!m_classes)
		return;

	if (m_classes->class_id != ET_WeaponSpawn)
		return;

	vec3 entity_position, entity_origin;
	entity_origin = entity->origin();

	if (entity_origin.distance_to(g.get_local()->origin()) > g_var.m_visuals_drop_distance)
		return;

	if (!g_game.w2s(entity_origin, entity_position))
		return;

	auto weapon = reinterpret_cast<c_base_weapon*>(entity);

	if (!weapon)
		return;

	g_render.draw_text(
		g_var.m_visuals_drop_type_var == 0 ? weap_list[weapon->get_weapon_id()].name : weap_icon_list[weapon->get_weapon_id()].name,
		entity_position.x, entity_position.y, g_var.m_visuals_drop_type_var == 0 ? g_fonts.m_font : g_fonts.m_icons_font,
		g_render.create_col(g_var.m_visuals_drop_color_var), true, false
	);
}

static void draw_other_drop(c_base_player* entity)
{
	c_client_class* m_classes = entity->client_class();

	if (!m_classes)
		return;

	vec3 entity_position, entity_origin;
	entity_origin = entity->origin();

	if (entity_origin.distance_to(g.get_local()->origin()) > g_var.m_visuals_drop_distance)
		return;

	if (!g_game.w2s(entity_origin, entity_position))
		return;

	switch (m_classes->class_id) {
	case ET_WeaponCola: {
		g_render.draw_text(g_var.m_visuals_drop_type_var == 0 ? X_("cola") : X_("q"), entity_position.x, entity_position.y,
			g_var.m_visuals_drop_type_var == 0 ? g_fonts.m_font : g_fonts.m_icons_font, g_render.create_col(g_var.m_visuals_drop_color_var), true, false);
		break;
	}
	case ET_WeaponAmmoSpawn: {
		g_render.draw_text(g_var.m_visuals_drop_type_var == 0 ? X_("ammo") : X_("t"), entity_position.x, entity_position.y,
			g_var.m_visuals_drop_type_var == 0 ? g_fonts.m_font : g_fonts.m_icons_font, g_render.create_col(g_var.m_visuals_drop_color_var), true, false);
		break;
	}}
}