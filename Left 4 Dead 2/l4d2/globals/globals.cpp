#include "globals.h"

#include "../modules/modules.h"

s_g g;

c_base_player* s_g::get_local()
{
	return reinterpret_cast<c_base_player*>(g_l4d2.m_entity_list->get_client_entity(g_l4d2.m_engine->get_local_player()));
}