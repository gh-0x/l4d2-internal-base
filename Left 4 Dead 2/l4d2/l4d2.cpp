#include "l4d2.h"

#include "globals/globals.h"
#include "config/config.h"
#include "modules/modules.h"
#include "hooks/hooks.h"
#include "render_manager/render_manager.h"
#include "input_manager/input_manager.h"
#include "ui/ui.h"

#include "../utils/utils.h"

void h::initialize(void* instance)
{
	g_cfg.initialize();
	g_l4d2.initialize();
	g_input.initialize();
	g_hooks.initialize();

	g_input.add_hotkey(VK_END, []() {
		g.m_unload = true;
	});

	g_input.add_hotkey(VK_INSERT, []() {
		g_ui.toggle();
	});

	while (!g.m_unload)
		g_utils.set_sleeping(50);

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

void h::undo()
{
	g_hooks.undo();
	g_input.undo();
	g_ui.undo();
	g_l4d2.undo();
}

bool WINAPI DllMain(HINSTANCE i, int r, int)
{
	DisableThreadLibraryCalls(i);

	switch (r) {
	case DLL_PROCESS_ATTACH: {
		if (auto h = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)h::initialize, i, 0, 0))
			CloseHandle(h);
		break;
	}
	case DLL_PROCESS_DETACH: {
		if (g.m_unload)
			h::undo();
		break;
	}}

	return true;
}