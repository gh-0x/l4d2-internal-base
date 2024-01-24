#pragma once

#include "../vec/vec3.h"
#include "../entity/c_base_entity.h"

#define TRACE_RAY_INTERFACE_VERSION "EngineTraceClient003"

struct ray_t {
	ray_t(const vec3& src, const vec3& dest) : start(src), delta(dest - src) { isSwept = delta.x || delta.y || delta.z; }
	vec3 start{ };
	float pad{ };
	vec3 delta{ };
	byte pad2[40]{ };
	bool isRay{ true };
	bool isSwept{ };
};

struct trace_filter {
	trace_filter(const c_base_entity* entity) : skip{ entity } { }
	virtual bool shouldHitEntity(c_base_entity* entity, int) { return entity != skip; }
	virtual int getTraceType() const { return 0; }
	const void* skip;
};

struct trace_class {
	vec3		startpos;
	vec3		endpos;

	struct
	{
		vec3	normal;
		float	distance;
		char	type;
		char	signbits;
		short	unused;
	}
	plane;

	float		fraction;
	int			contents;
	short		dispflags;
	bool		allsolid;
	bool		startsolid;
	float		fractionleftsolid;
	const char	*name;
	short		surfaceprops;
	short		flags;
	int			hitgroup;
	short		physicsbone;
	c_base_entity	*entity;
	int			hitbox;
};

class trace_ray {
public:
	void get_trace_ray(const ray_t &ray, trace_filter* filter, trace_class* trace);
};