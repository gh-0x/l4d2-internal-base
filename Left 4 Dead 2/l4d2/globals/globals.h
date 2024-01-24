#pragma once

#include "../../std.h"

class c_base_player;

struct s_g {
public:
	bool m_unload;
	bool* m_send_packet;
public:
	c_base_player* get_local();
};

extern s_g g;