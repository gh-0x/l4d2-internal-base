#include "c_base_entity.h"

#include "../../modules/modules.h"

vec3 c_base_player::get_eye_pos()
{
	return get_vec_origin() + get_view_offset();
}

c_base_weapon* c_base_player::get_active_weapon()
{
	auto active_weapon = read<uintptr_t>(g_netvars.get_netvar(fnv::hash("DT_CSPlayer"), fnv::hash("m_hActiveWeapon"))) & 0xFFF;
	return reinterpret_cast<c_base_weapon*>(g_l4d2.m_entity_list->get_client_entity(active_weapon));
}