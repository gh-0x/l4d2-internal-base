#pragma once

#include "../../std.h"

/*
  - Some tricks in ImGui
  -
*/

namespace ImGui
{
	bool ButtonWithCustomID(const char* label, const char* label_id);
	void MakePopup(const char* name, bool* v, std::function<void(void)> func);
}