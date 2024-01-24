#include "c_input_system.h"

void inputsystem::enable_input(bool v)
{
	using original_fn = void(__thiscall*)(void*, bool);
	return (*(original_fn * *)this)[2](this, v);
}

bool inputsystem::is_button_down(button_code_t code) {
	using original_fn = bool(__thiscall*)(void*, button_code_t);
	return (*(original_fn * *)this)[6](this, code);
}

const char* inputsystem::button_code_to_string(button_code_t code)
{
	using original_fn = const char* (__thiscall*)(void*, button_code_t);
	return (*(original_fn * *)this)[22](this, code);
}

const char* inputsystem::analog_code_to_string(analog_code_t code)
{
	using original_fn = const char* (__thiscall*)(void*, analog_code_t);
	return (*(original_fn * *)this)[23](this, code);
}

int inputsystem::get_analog_value(analog_code_t code)
{
	using original_fn = int(__thiscall*)(void*, analog_code_t);
	return (*(original_fn * *)this)[9](this, code);
}

int inputsystem::get_analog_delta(analog_code_t code)
{
	using original_fn = int(__thiscall*)(void*, analog_code_t);
	return (*(original_fn * *)this)[10](this, code);
}