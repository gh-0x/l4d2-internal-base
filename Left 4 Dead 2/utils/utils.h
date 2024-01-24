#pragma once

#include "../std.h"

enum M_DIR {
	DIR_FOUNDED = 3,
	FILE_FOUNDED = 2,
	FAIL = 0
};

struct utils {
public:
	bool is_module_exists(const char* mod);
	DWORD_PTR get_module_base_address(const char* name);
	
	int float_to_rgb(float var);
	int get_time_since_epoch();
	void set_sleeping(int mills);

	std::string get_current_time();

	struct filesystem {
	public:
		std::string get_module_directory();
		M_DIR dir_exists(const char* path);
	};

	struct console {
	public:
		void initialize(const char* title);
		void undo();

		template <typename ... Args>
		void log(char const* const format, Args const& ... args) {
#ifdef _DEBUG
			printf(format, args ...);
#endif
		}
	};
};

extern utils g_utils;
extern utils::console g_console;
extern utils::filesystem g_filesystem;