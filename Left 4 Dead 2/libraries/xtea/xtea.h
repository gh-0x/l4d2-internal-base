#include <iostream>
#include <windows.h>
#include <string>

struct xtea {
public:
	void encode(const std::string& path);
	void decode(const std::string& path);
};

extern xtea g_xtea;