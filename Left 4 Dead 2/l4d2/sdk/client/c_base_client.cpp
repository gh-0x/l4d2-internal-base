#include "c_base_client.h"

c_client_class* base_client::get_client_class()
{
	using original_fn = c_client_class*(__thiscall*)(base_client*);
	return (*(original_fn * *)this)[7](this);
}