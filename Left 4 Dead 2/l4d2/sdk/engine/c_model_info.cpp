#include "c_model_info.h"

const model_t* model_info::get_model(int index)
{
	using original_fn = const model_t*(__thiscall*)(model_info*, int);
	return (*(original_fn * *)this)[1](this, index);
}

int model_info::get_model_index(const char* name)
{
	using original_fn = int(__thiscall*)(model_info*, const char*);
	return (*(original_fn * *)this)[2](this, name);
}

const char* model_info::get_model_name(const model_t* model)
{
	using original_fn = const char*(__thiscall*)(model_info*, const model_t*);
	return (*(original_fn * *)this)[3](this, model);
}