#include "c_view_matrix.h"

view_matrix::view_matrix() {}

view_matrix::view_matrix(
	vec m00, vec m01, vec m02, vec m03,
	vec m10, vec m11, vec m12, vec m13,
	vec m20, vec m21, vec m22, vec m23,
	vec m30, vec m31, vec m32, vec m33) {
	init(
		m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33
	);
}

view_matrix::view_matrix(const c_matrix& matrix3x4) {
	init(matrix3x4);
}

view_matrix::view_matrix(const vec3& _x, const vec3& _y, const vec3& _z) {
	init(
		_x.x, _y.x, _z.x, 0.0f,
		_x.y, _y.y, _z.y, 0.0f,
		_x.z, _y.z, _z.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void view_matrix::init(
	vec m00, vec m01, vec m02, vec m03,
	vec m10, vec m11, vec m12, vec m13,
	vec m20, vec m21, vec m22, vec m23,
	vec m30, vec m31, vec m32, vec m33
) {
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

void view_matrix::init(const c_matrix& m3x4) {
	memcpy(m, m3x4.base(), sizeof(c_matrix));

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void vector_3d_multiply_position(const view_matrix& src1, const vec3& src2, vec3& dst) {
	dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
	dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
	dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
}

vec3 view_matrix::get_forward() const {
	return vec3(m[0][0], m[1][0], m[2][0]);
}

vec3 view_matrix::get_left() const {
	return vec3(m[0][1], m[1][1], m[2][1]);
}

vec3 view_matrix::get_up() const {
	return vec3(m[0][2], m[1][2], m[2][2]);
}

void view_matrix::set_forward(const vec3& forward) {
	m[0][0] = forward.x;
	m[1][0] = forward.y;
	m[2][0] = forward.z;
}

void view_matrix::set_left(const vec3& left) {
	m[0][1] = left.x;
	m[1][1] = left.y;
	m[2][1] = left.z;
}

void view_matrix::set_up(const vec3& up) {
	m[0][2] = up.x;
	m[1][2] = up.y;
	m[2][2] = up.z;
}

void view_matrix::get_basis_vector_3d(vec3& forward, vec3& left, vec3& up) const {
	forward.init(m[0][0], m[1][0], m[2][0]);
	left.init(m[0][1], m[1][1], m[2][1]);
	up.init(m[0][2], m[1][2], m[2][2]);
}

void view_matrix::set_basis_vector_3d(const vec3& forward, const vec3& left, const vec3& up) {
	set_forward(forward);
	set_left(left);
	set_up(up);
}

vec3 view_matrix::get_translation() const {
	return vec3(m[0][3], m[1][3], m[2][3]);
}

vec3& view_matrix::get_translation(vec3& trans) const {
	trans.x = m[0][3];
	trans.y = m[1][3];
	trans.z = m[2][3];
	return trans;
}

void view_matrix::set_translation(const vec3& trans) {
	m[0][3] = trans.x;
	m[1][3] = trans.y;
	m[2][3] = trans.z;
}

void view_matrix::pre_translate(const vec3& trans) {
	vec3 tmp;
	vector_3d_multiply_position(*this, trans, tmp);
	m[0][3] = tmp.x;
	m[1][3] = tmp.y;
	m[2][3] = tmp.z;
}

void view_matrix::post_translate(const vec3& trans) {
	m[0][3] += trans.x;
	m[1][3] += trans.y;
	m[2][3] += trans.z;
}

const c_matrix& view_matrix::as_matrix() const {
	return *((const c_matrix*)this);
}

c_matrix& view_matrix::as_matrix() {
	return *((c_matrix*)this);
}

void view_matrix::copy_from_matrix(const c_matrix& m3x4) {
	memcpy(m, m3x4.base(), sizeof(c_matrix));
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;
}

void view_matrix::set_matrix(c_matrix& m3x4) const {
	memcpy(m3x4.base(), m, sizeof(c_matrix));
}

const view_matrix& view_matrix::operator+=(const view_matrix& other) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] += other.m[i][j];
		}
	}
	return *this;
}

view_matrix& view_matrix::operator=(const view_matrix& other) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = other.m[i][j];
		}
	}
	return *this;
}

view_matrix view_matrix::operator+(const view_matrix& other) const {
	view_matrix ret;
	for (int i = 0; i < 16; i++) {
		((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
	}
	return ret;
}

view_matrix view_matrix::operator-(const view_matrix& other) const {
	view_matrix ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = m[i][j] - other.m[i][j];
		}
	}

	return ret;
}

view_matrix view_matrix::operator-() const {
	view_matrix ret;
	for (int i = 0; i < 16; i++) {
		((float*)ret.m)[i] = -((float*)m)[i];
	}
	return ret;
}

vec3 view_matrix::operator*(const vec3& vec) const {
	vec3 ret;
	ret.x = m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3];
	ret.y = m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3];
	ret.z = m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3];
	return ret;
}

vec3 view_matrix::vector_3d_multiply(const vec3& vec) const {
	vec3 result;
	vector_3d_multiply_position(*this, vec, result);
	return result;
}

vec3 view_matrix::vector_3d_transpose(const vec3& vec) const {
	vec3 tmp = vec;
	tmp.x -= m[0][3];
	tmp.y -= m[1][3];
	tmp.z -= m[2][3];

	return vec3(
		m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
		m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
		m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
	);
}

vec3 view_matrix::vector_3d_multiply_upper(const vec3 & vec) const {
	return vec3(
		m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z,
		m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z,
		m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z
	);
}

vec3 view_matrix::vector_3d_transpose_rotation(const vec3 & vec) const {
	return vec3(
		m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
		m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
		m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
	);
}

void view_matrix::vector_3d_multiply(const vec3 & in, vec3 & out) const {
	vec rw;

	rw = 1.0f / (m[3][0] * in.x + m[3][1] * in.y + m[3][2] * in.z + m[3][3]);
	out.x = (m[0][0] * in.x + m[0][1] * in.y + m[0][2] * in.z + m[0][3]) * rw;
	out.y = (m[1][0] * in.x + m[1][1] * in.y + m[1][2] * in.z + m[1][3]) * rw;
	out.z = (m[2][0] * in.x + m[2][1] * in.y + m[2][2] * in.z + m[2][3]) * rw;
}

void view_matrix::identity() {
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

bool view_matrix::is_identity() const {
	return
		m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
		m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
		m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
		m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
}

vec3 view_matrix::apply_rotation(const vec3 & vec) const {
	return vector_3d_multiply(vec);
}
