#include "c_trace_ray.h"

void trace_ray::get_trace_ray(const ray_t &ray, trace_filter* filter, trace_class* trace) {
	using original_fn = void(__thiscall*)(trace_ray*, const ray_t&, int, trace_filter*, trace_class*);
	return (*(original_fn * *)this)[5](this, ray, 0x46004003, filter, trace);
}