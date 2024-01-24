#pragma once

#pragma warning( disable : 26451 )

#include <limits>
#include <algorithm>

inline float bits_to_float(std::uint32_t i) {
	union convertor_t {
		float f; unsigned long ul;
	} tmp;

	tmp.ul = i;
	return tmp.f;
}

constexpr double M_PI = 3.14159265358979323846;
constexpr float M_RADPI = 57.295779513082f;
constexpr float M_PI_F = static_cast<float>(M_PI);

constexpr float RAD2DEG(const float x) {
	return (float)(x) * (float)(180.f / M_PI_F);
}

constexpr float DEG2RAD(const float x) {
	return (float)(x) * (float)(M_PI_F / 180.f);
}

constexpr std::uint32_t FLOAT32_NAN_BITS = 0x7FC00000;
const float FLOAT32_NAN = bits_to_float(FLOAT32_NAN_BITS);

#define VECTOR_NAN FLOAT32_NAN
#define ASSERT( _exp ) ( (void ) 0 )

class vec3 {
public:
	vec3();
	vec3(float, float, float);
	~vec3();

	float x, y, z;

	vec3& operator+=(const vec3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vec3& operator-=(const vec3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vec3& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}

	vec3 operator+(const vec3& v) {
		return vec3{ x + v.x, y + v.y, z + v.z };
	}

	vec3 operator-(const vec3& v) {
		return vec3{ x - v.x, y - v.y, z - v.z };
	}

	vec3 operator*(float fl) const {
		return vec3(x * fl, y * fl, z * fl);
	}

	vec3 operator*(const vec3& v) const {
		return vec3(x * v.x, y * v.y, z * v.z);
	}

	vec3& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;

		return *this;
	}

	auto operator-(const vec3& other) const -> vec3 {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator/(float other) const {
		vec3 vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		return vec;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}

	float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline float length_2d() const {
		return sqrt((x * x) + (y * y));
	}

	void crossproduct(vec3 v1, vec3 v2, vec3 cross_p) const {
		cross_p.x = (v1.y * v2.z) - (v1.z * v2.y);
		cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x));
		cross_p.z = (v1.x * v2.y) - (v1.y * v2.x);
	}

	vec3 cross(const vec3 & other) const {
		vec3 res;
		crossproduct(*this, other, res);
		return res;
	}

	void init(float ix, float iy, float iz);
	void clamp();
	vec3 clamped();
	vec3 normalized();
	float distance_to(const vec3 & other);
	bool is_zero(void);
	void normalize();
	float length();
	float length_sqr();
	float length_2d_sqr(void) const;
	float dot(const vec3 other);
	float dot(const float* other);
};

inline vec3 operator*(float lhs, const vec3 & rhs) {
	return vec3(rhs.x * lhs, rhs.x * lhs, rhs.x * lhs);
}