#include "../../std.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

#include <d3d9.h>
#include <d3dx9.h>

struct ui {
public:
	void run();
	void initialize(IDirect3DDevice9* device);
	void undo();
	void toggle();
private:
	bool                              m_opened = {};
};

extern ui g_ui;