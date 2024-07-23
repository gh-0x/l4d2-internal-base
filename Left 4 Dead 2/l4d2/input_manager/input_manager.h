#pragma once

#include "../../std.h"

enum class m_state
{
	none = 1,
	down,
	up,
	pressed
};

struct input_manager {
public:
	void initialize();
	void undo();

	m_state get_key_state(uint32_t vk);

	bool is_key_down(uint32_t vk);
	bool was_key_pressed(uint32_t vk);

	void add_hotkey(uint32_t vk, std::function<void(void)> f);
	void rem_hotkey(uint32_t vk);

	HWND get_window();
	WNDPROC get_wnd_proc_original();

	bool process_message(UINT, WPARAM, LPARAM);
	bool process_mouse_message(UINT, WPARAM, LPARAM);
	bool process_keybd_message(UINT, WPARAM, LPARAM);
private:
	HWND                                     m_hwnd;
	WNDPROC                                  m_old_wnd_proc;
	m_state                                  m_key_map[256];
	std::function<void(void)>                m_hotkeys[256];
};

extern input_manager g_input;
