#pragma once

#include "../../../std.h"
#define MODEL_INFO_INTERFACE_VERSION "VModelInfoClient004"

struct model_t {
	DWORD		unknown;
	char        name[255];
};

class model_info {
public:
	const model_t* get_model(int index);
	int get_model_index(const char* name);
	const char* get_model_name(const model_t* model);
};