#include "vec3.h"

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

vec3::vec3(void) {
	x = y = z = 0.0f;
}

vec3::vec3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

vec3::~vec3(void) {};

void vec3::init(float _x, float _y, float _z) {
	x = _x; y = _y; z = _z;
}

void vec3::clamp(void) {
	x = std::clamp(x, -89.0f, 89.0f);
	y = std::clamp(std::remainder(y, 360.0f), -180.0f, 180.0f);
	z = std::clamp(z, -50.0f, 50.0f);
}

vec3 vec3::clamped() {
	vec3 clamped = *this;
	clamped.clamp();
	return clamped;
}

float vec3::distance_to(const vec3& other) {
	vec3 delta;
	delta.x = x - other.x;
	delta.y = y - other.y;
	delta.z = z - other.z;

	return delta.length();
}

bool vec3::is_zero(void) {
	if (x == 0 && y == 0 && z == 0)
		return true;

	return false;
}

void vec3::normalize()
{
	x = std::isfinite(x) ? std::remainderf(x, 360.0f) : 0.0f;
	y = std::isfinite(y) ? std::remainderf(y, 360.0f) : 0.0f;
	z = 0.0f;
}

vec3 vec3::normalized(void) {

	vec3 vec(*this);
	vec.normalize();
	return vec;
}

float vec3::length(void) {
	float root = 0.0f, sqsr = this->length_sqr();
	root = std::sqrt(sqsr);
	return root;
}

float vec3::length_sqr(void) {
	auto sqr = [](float n) {
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y) + sqr(z));
}

float vec3::length_2d_sqr(void) const {
	return (x * x + y * y);
}

float vec3::dot(const vec3 other) {
	return (x * other.x + y * other.y + z * other.z);
}

float vec3::dot(const float* other) {
	const vec3& a = *this;
	return(a.x * other[0] + a.y * other[1] + a.z * other[2]);
}
