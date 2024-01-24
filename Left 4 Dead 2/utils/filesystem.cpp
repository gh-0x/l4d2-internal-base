#include "utils.h"

#include <filesystem>

utils::filesystem g_filesystem;

std::string utils::filesystem::get_module_directory()
{
	TCHAR dir[260];
	GetModuleFileNameA(0, dir, 260);

	std::filesystem::path p = dir;

	return p.parent_path().string();
}

M_DIR utils::filesystem::dir_exists(const char* path)
{
	struct stat s;

	if (stat(path, &s) == 0) {
		if (s.st_mode & S_IFDIR) {
			return M_DIR::DIR_FOUNDED;
		}
		else if (s.st_mode & S_IFREG) {
			return M_DIR::FILE_FOUNDED;
		}
	}

	return M_DIR::FAIL;
}