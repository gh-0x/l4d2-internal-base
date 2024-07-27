#pragma once

#include "../std.h"

enum _obj_exists {
	is_failed = 0,
	is_binary = 1,
	is_directory = 2,
};

struct obj {
	_obj_exists _id;
	bool as(_obj_exists id) {
		return _id == id;
	}
};

struct utils {
public:
	int float_to_rgb(const float var);
	int get_time_since_epoch();
	void set_sleeping(const int mills);

	std::string get_current_time();

	struct filesystem {
	public:
		std::string get_module_directory();
		obj object_exists(const char* path);
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