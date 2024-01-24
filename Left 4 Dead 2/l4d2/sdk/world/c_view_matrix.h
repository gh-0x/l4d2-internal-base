#pragma once

#include "../vec/vec.h"
#include "../world/c_matrix.h"

class view_matrix {
public:
	view_matrix();
	view_matrix(
		vec m00, vec m01, vec m02, vec m03,
		vec m10, vec m11, vec m12, vec m13,
		vec m20, vec m21, vec m22, vec m23,
		vec m30, vec m31, vec m32, vec m33
	);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	view_matrix(const vec3& forward, const vec3& left, const vec3& up);

	// Construct from a 3x4 matrix
	view_matrix(const c_matrix& m3x4);

	// Set the values in the matrix.
	void		init(
		vec m00, vec m01, vec m02, vec m03,
		vec m10, vec m11, vec m12, vec m13,
		vec m20, vec m21, vec m22, vec m23,
		vec m30, vec m31, vec m32, vec m33
	);

	// Initialize from a 3x4
	void		init(const c_matrix& matrix3x4);

	// array access
	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float* base() {
		return &m[0][0];
	}

	inline const float* base() const {
		return &m[0][0];
	}

	void		set_left(const vec3& left);
	void		set_up(const vec3& up);
	void		set_forward(const vec3& forward);

	void		get_basis_vector_3d(vec3& forward, vec3& left, vec3& up) const;
	void		set_basis_vector_3d(const vec3& forward, const vec3& left, const vec3& up);

	// Get/set the translation.
	vec3& 	get_translation(vec3& trans) const;
	void		set_translation(const vec3& trans);

	void		pre_translate(const vec3& tans);
	void		post_translate(const vec3& trans);

	c_matrix& 	as_matrix();
	const c_matrix& as_matrix() const;
	void		copy_from_matrix(const c_matrix& m3x4);
	void		set_matrix(c_matrix& m3x4) const;

	bool		operator==(const view_matrix& src) const;
	bool		operator!=(const view_matrix& src) const { return !(*this == src); }

	// Access the basis vec3s.
	vec3		get_left() const;
	vec3		get_up() const;
	vec3		get_forward() const;
	vec3		get_translation() const;

	// Matrix->vec3 operations.
public:
	// Multiply by a 3D vec3 (same as operator*).
	void		vector_3d_multiply(const vec3 & in, vec3 & out) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	vec3		apply_rotation(const vec3 & vec) const;

	// Multiply by a vec3 (divides by w, assumes input w is 1).
	vec3		operator*(const vec3 & vec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	vec3		vector_3d_multiply(const vec3 & vec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	vec3		vector_3d_transpose_rotation(const vec3 & vec) const;

	// Multiply by the upper 3 rows.
	vec3		vector_3d_multiply_upper(const vec3 & vec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	vec3		vector_3d_transpose(const vec3 & vec) const;
	
public:

	view_matrix& operator=(const view_matrix & other);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const view_matrix & vm, view_matrix & out) const;

	// Add two matrices.
	const view_matrix& operator+=(const view_matrix & other);

	// Just calls MatrixMul and returns the result.
	view_matrix		operator*(const view_matrix & other) const;

	// Add/Subtract two matrices.
	view_matrix		operator+(const view_matrix & other) const;
	view_matrix		operator-(const view_matrix & other) const;

	// Negation.
	view_matrix		operator-() const;

	// Matrix operations.
public:
	// Set to identity.
	void		identity();

	bool		is_identity() const;

	// Setup a matrix for origin and angles.
	void		setup_maitrx_orginal_angles(const vec3 & origin, const vec3 & angles);

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		inverse_tr(view_matrix & ret) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit vec3s and they are all orthogonal.
	bool		is_rotation_matrix() const;

	// This calls the other InverseTR and returns the result.
	view_matrix		inverse_tr() const;

	// Get the scale of the matrix's basis vec3s.
	vec3			get_scale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	view_matrix		scale(const vec3 & scale);

	// Normalize the basis vec3s.
	view_matrix		normalize_basis_vector_3d() const;

	// Transpose.
	view_matrix		transpose() const;

	// Transpose upper-left 3x3.
	view_matrix		transpose_3x3() const;

public:
	// The matrix.
	vec		m[4][4];
};
