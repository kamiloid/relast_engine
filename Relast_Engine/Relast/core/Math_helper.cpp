#include"../Relast_Engine.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

FLOAT Relast::math::v3_mag(glm::vec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

FLOAT Relast::math::v3_angle(glm::vec3 v1, glm::vec3 v2)
{
	return acos( (glm::dot(v1, v2)) / (v3_mag(v1) * v3_mag(v2)) );
}



glm::vec3 Relast::math::v3_forward(glm::vec3 v)
{
	return glm::vec3(v.x, v.y, v.z + 1.0f);
}
glm::vec3 Relast::math::v3_backward(glm::vec3 v)
{
	return glm::vec3(v.x, v.y, v.z - 1.0f);
}
glm::vec3 Relast::math::v3_left(glm::vec3 v)
{
	return glm::vec3(v.x - 1.0f, v.y, v.z);
}
glm::vec3 Relast::math::v3_right(glm::vec3 v)
{
	return glm::vec3(v.x + 1.0f, v.y, v.z);
}
glm::vec3 Relast::math::v3_up(glm::vec3 v)
{
	return glm::vec3(v.x, v.y + 1.0f, v.z);
}
glm::vec3 Relast::math::v3_down(glm::vec3 v)
{
	return glm::vec3(v.x, v.y - 1.0f, v.z);
}

vec3_t Relast::math::glmv3_to_v3t(glm::vec3 v)
{
	return vec3(v.x, v.y, v.z);
}
glm::vec3 Relast::math::v3t_to_glmv3(vec3_t v)
{
	return glm::vec3(v.x, v.y, v.z);
}


glm::mat4 Relast::math::mat4_to_glmMat4(mat4_t m)
{
	glm::mat4 glmm = glm::mat4();
	glmm[0] = { m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3] };
	glmm[1] = { m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3] };
	glmm[2] = { m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3] };
	glmm[3] = { m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3] };
	return glmm;
}








bool Relast::math::DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
{
	// From glm::decompose in matrix_decompose.inl

	using namespace glm;
	using T = float;

	glm::mat4 LocalMatrix(transform);

	// Normalize the matrix.
	if (glm::epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
		return false;

	// First, isolate perspective.  This is the messiest.
	if (
		glm::epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
		glm::epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
		glm::epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
	{
		// Clear the perspective partition
		LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
		LocalMatrix[3][3] = static_cast<T>(1);
	}

	// Next take care of translation (easy).
	translation = glm::vec3(LocalMatrix[3]);
	LocalMatrix[3] = glm::vec4(0, 0, 0, LocalMatrix[3].w);

	glm::vec3 Row[3], Pdum3;

	// Now get scale and shear.
	for (length_t i = 0; i < 3; ++i)
		for (length_t j = 0; j < 3; ++j)
			Row[i][j] = LocalMatrix[i][j];

	// Compute X scale factor and normalize first row.
	scale.x = length(Row[0]);
	Row[0] = detail::scale(Row[0], static_cast<T>(1));
	scale.y = length(Row[1]);
	Row[1] = detail::scale(Row[1], static_cast<T>(1));
	scale.z = length(Row[2]);
	Row[2] = detail::scale(Row[2], static_cast<T>(1));

	// At this point, the matrix (in rows[]) is orthonormal.
	// Check for a coordinate system flip.  If the determinant
	// is -1, then negate the matrix and the scaling factors.
#if 0
	Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
	if (dot(Row[0], Pdum3) < 0)
	{
		for (length_t i = 0; i < 3; i++)
		{
			scale[i] *= static_cast<T>(-1);
			Row[i] *= static_cast<T>(-1);
		}
	}
#endif

	rotation.y = asin(-Row[0][2]);
	if (cos(rotation.y) != 0) {
		rotation.x = atan2(Row[1][2], Row[2][2]);
		rotation.z = atan2(Row[0][1], Row[0][0]);
	}
	else {
		rotation.x = atan2(-Row[2][0], Row[1][1]);
		rotation.z = 0;
	}


	return true;
}