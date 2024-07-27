#include "esp.h"

#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../modules/modules.h"
#include "../../render_manager/render_manager.h"
#include "../../game_utilities/game_utilities.h"

esp g_esp;

static void draw_players(c_base_player* entity, int i);
static void draw_infected(c_base_player* entity);
static void draw_special_infected(c_base_player* entity);

void esp::run()
{
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

		draw_players(entity, i);
		
		if (g_var.m_esp_infected_var)
			draw_infected(entity);

		if (g_var.m_esp_special_infected_var)
			draw_special_infected(entity);
	}
}

static void draw_players(c_base_player* entity, int i)
{
	vec3 entity_position, entity_origin;
	entity_origin = entity->origin();

	c_client_class* m_classes = entity->client_class();

	if (!m_classes)
		return;

	if (!g_game.w2s(entity_origin, entity_position))
		return;

	switch (m_classes->class_id) {
	case ET_CTERRORPLAYER:
	case ET_SURVIVORBOT: {
		if (g_var.m_esp_player_name_var) {
			player_info_t info;
			if (!g_l4d2.m_engine->get_player_info(i, &info))
				return;
			g_render.draw_text(info.name, entity_position.x, entity_position.y, g_fonts.m_font,
				g_render.create_col(g_var.m_esp_player_name_color_var), true, false);
		}
		break;
	}}
}

static void draw_infected(c_base_player* entity)
{
	vec3 entity_position, entity_origin;
	entity_origin = entity->origin();

	c_client_class* m_classes = entity->client_class();

	if (!m_classes)
		return;

	if (!g_game.w2s(entity_origin, entity_position))
		return;

	if (entity_origin.distance_to(g.get_local()->origin()) > g_var.m_esp_infected_distance_var)
		return;

	if (m_classes->class_id != ET_INFECTED)
		return;

	g_render.draw_text(X_("Infected"), entity_position.x, entity_position.y, g_fonts.m_font,
		g_render.create_col(g_var.m_esp_infected_color_var), true, false);
}

static void draw_special_infected(c_base_player* entity)
{
	c_client_class* m_classes = entity->client_class();

	if (!m_classes)
		return;

	vec3 entity_position, entity_origin;
	entity_origin = entity->origin();

	if (!g_game.w2s(entity_origin, entity_position))
		return;

	switch (m_classes->class_id) {
	case ET_HUNTER:
		g_render.draw_text(X_("hunter"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_TANK:
		g_render.draw_text(X_("tank"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_JOCKEY:
		g_render.draw_text(X_("jockey"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_WITCH:
		g_render.draw_text(X_("witch"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_BOOMER:
		g_render.draw_text(X_("boomer"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_SMOKER:
		g_render.draw_text(X_("smoker"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_SPITTER:
		g_render.draw_text(X_("spitter"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	case ET_CHARGER:
		g_render.draw_text(X_("charger"), entity_position.x, entity_position.y, g_fonts.m_font,
			g_render.create_col(g_var.m_esp_special_infected_color_var), true, false);
		break;
	};
}