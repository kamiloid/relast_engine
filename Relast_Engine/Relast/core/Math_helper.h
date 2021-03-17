#pragma once
#ifndef __R_MATH_HELPER__
#define __R_MATH_HELPER__


namespace Relast
{
	namespace math
	{
		FLOAT v3_mag(glm::vec3 v = glm::vec3());
		FLOAT v3_angle(glm::vec3 v1 = glm::vec3(), glm::vec3 v2 = glm::vec3());
		glm::vec3 v3_forward(glm::vec3 v = glm::vec3());
		glm::vec3 v3_backward(glm::vec3 v = glm::vec3());
		glm::vec3 v3_left(glm::vec3 v = glm::vec3());
		glm::vec3 v3_right(glm::vec3 v = glm::vec3());
		glm::vec3 v3_up(glm::vec3 v = glm::vec3());
		glm::vec3 v3_down(glm::vec3 v = glm::vec3());

		vec3_t glmv3_to_v3t(glm::vec3 v);
		glm::vec3 v3t_to_glmv3(vec3_t v);

		glm::mat4 mat4_to_glmMat4(mat4_t m);

		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}
}



#endif // !__R_MATH_HELPER__
