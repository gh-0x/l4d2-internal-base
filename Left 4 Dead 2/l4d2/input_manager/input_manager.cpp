#include "input_manager.h"

input_manager g_input;

unsigned long WINAPI hook(HWND h, UINT m, WPARAM w, LPARAM l)
{
	g_input.process_message(m, w, l);

	LRESULT ImGui_ImplWin32_WndProcHandler(HWND h, UINT m, WPARAM w, LPARAM l);
	ImGui_ImplWin32_WndProcHandler(g_input.get_window(), m, w, l);

	return CallWindowProcA(g_input.get_wnd_proc_original(), h, m, w, l);
}

void input_manager::initialize()
{
	m_hwnd = FindWindowA(X_("Valve001"), 0);
	m_old_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongA(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hook)));
}

void input_manager::undo()
{
	if (m_old_wnd_proc)
		SetWindowLongA(m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_old_wnd_proc));

	m_old_wnd_proc = 0;
}

m_state input_manager::get_key_state(std::uint32_t vk)
{
	return m_key_map[vk];
}

bool input_manager::is_key_down(std::uint32_t vk)
{
	return m_key_map[vk] == m_state::down;
}

bool input_manager::was_key_pressed(std::uint32_t vk)
{
	if (m_key_map[vk] == m_state::pressed)
	{
		m_key_map[vk] = m_state::up;
		return true;
	}
	return false;
}

void input_manager::add_hotkey(std::uint32_t vk, std::function<void(void)> f)
{
	m_hotkeys[vk] = f;
}

void input_manager::rem_hotkey(std::uint32_t vk)
{
	m_hotkeys[vk] = nullptr;
}

HWND input_manager::get_window()
{
	return m_hwnd;
}

WNDPROC input_manager::get_wnd_proc_original()
{
	return m_old_wnd_proc;
}

bool input_manager::process_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
		return process_mouse_message(uMsg, wParam, lParam);
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return process_keybd_message(uMsg, wParam, lParam);
	default:
		return false;
	}
}

bool input_manager::process_mouse_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = VK_LBUTTON;
	auto state = m_state::none;

	switch (uMsg)
	{
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		state = uMsg == WM_MBUTTONUP ? m_state::up : m_state::down;
		key = VK_MBUTTON;
		break;
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		state = uMsg == WM_RBUTTONUP ? m_state::up : m_state::down;
		key = VK_RBUTTON;
		break;
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		state = uMsg == WM_LBUTTONUP ? m_state::up : m_state::down;
		key = VK_LBUTTON;
		break;
	case WM_XBUTTONDBLCLK:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		state = uMsg == WM_XBUTTONUP ? m_state::up : m_state::down;
		key = (HIWORD(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	default:
		return false;
	}

	if (state == m_state::up && m_key_map[key] == m_state::down)
		m_key_map[key] = m_state::pressed;
	else
		m_key_map[key] = state;

	return true;
}

bool input_manager::process_keybd_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = wParam;
	auto state = m_state::none;

	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		state = m_state::down;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		state = m_state::up;
		break;
	default:
		return false;
	}

	if (state == m_state::up && m_key_map[int(key)] == m_state::down)
	{
		m_key_map[int(key)] = m_state::pressed;

		auto& hotkey_callback = m_hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();
	}
	else
	{
		m_key_map[int(key)] = state;
	}

	return true;
}
