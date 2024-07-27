#include "utils.h"

#include <chrono>
#include <thread>

utils g_utils;

int utils::float_to_rgb(const float var)
{
	return var * 255;
}

int utils::get_time_since_epoch()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void utils::set_sleeping(const int mills)
{
	return std::this_thread::sleep_for(std::chrono::milliseconds(mills));
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