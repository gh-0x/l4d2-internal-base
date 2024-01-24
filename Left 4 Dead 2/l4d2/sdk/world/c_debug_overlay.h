#pragma once

#include "../vec/vec.h"

#define DEBUG_OVERLAY_INTERFACE_VERSION "VDebugOverlay003"

class debug_overlay {
public:
	bool screen_position(const vec3& in, vec3& out);
};