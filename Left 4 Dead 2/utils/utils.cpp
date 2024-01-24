#include "utils.h"

#include <psapi.h>
#include <chrono>
#include <thread>

utils g_utils;

using namespace std::this_thread;
using namespace std::chrono;

bool utils::is_module_exists(const char* mod)
{
	return GetModuleHandleA(mod) != 0;
}

DWORD_PTR utils::get_module_base_address(const char* name)
{
	HMODULE m = GetModuleHandleA(name);

	if (m == 0)
		return 0;

	MODULEINFO module_info;
	GetModuleInformation(GetCurrentProcess(), m, &module_info, sizeof(module_info));

	return (DWORD_PTR)module_info.lpBaseOfDll;
}

int utils::float_to_rgb(float var)
{
	return var * 255;
}

int utils::get_time_since_epoch()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void utils::set_sleeping(int mills)
{
	return sleep_for(milliseconds(mills));
}

std::string utils::get_current_time()
{
	time_t     now = time(0);

	struct tm  tstruct;
	char       buf[80];

	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%H:%M", &tstruct);
	return buf;
}