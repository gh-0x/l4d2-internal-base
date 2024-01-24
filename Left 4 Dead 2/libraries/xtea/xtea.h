
#include <iostream>
#include <windows.h>
#include <string>

struct xtea {
public:
	void enc(std::string file_path);
	void dec(std::string file_path);
};

extern xtea g_xtea;