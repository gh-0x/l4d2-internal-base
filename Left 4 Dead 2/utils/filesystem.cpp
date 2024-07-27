#include "utils.h"

#include <filesystem>

utils::filesystem g_filesystem;

std::string utils::filesystem::get_module_directory()
{
	TCHAR dir[MAX_PATH];
	GetModuleFileNameA(0, dir, MAX_PATH);

	std::filesystem::path p = dir;

	return p.parent_path().string();
}

obj utils::filesystem::object_exists(const char* path)
{
	struct stat s;
	struct obj  o;

	if (stat(path, &s) == 0) {
		if (s.st_mode & S_IFDIR) {
			o._id = is_directory;
		}
		else if (s.st_mode & S_IFREG) {
			o._id = is_binary;
		}
		else {
			o._id = is_failed;
		}
	}
	else {
		o._id = is_failed;
	}

	return o;
}