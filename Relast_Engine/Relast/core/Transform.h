#pragma once

#ifndef __R_TRANSFORM__
#define __R_TRANSFORM__

#define _GLOBAL_ "Global"
#define _LOCAL_ "Local"


#include"Tools.h"

namespace Relast
{
	class Transform3D
	{
	private:
		glm::mat4 _transform = glm::mat4(1.0f);
	public:
		Transform3D() {
		};
		~Transform3D() {};

		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _rotation = glm::vec3(0.0f);
		glm::vec3 _scale = glm::vec3(1.0f);

		glm::mat4 get_matrix() { return this->_transform; };
		uniforms_config::Uniform_3f* position_uniform() { return new uniforms_config::Uniform_3f(this->_position.x, this->_position.y, this->_position.z); };
		uniforms_config::Uniform_3f* rotation_uniform() { return new uniforms_config::Uniform_3f(this->_rotation.x, this->_rotation.y, this->_rotation.z); };
		uniforms_config::Uniform_3f* scale_uniform() { return new uniforms_config::Uniform_3f(this->_scale.x, this->_scale.y, this->_scale.z); };
		uniforms_config::Uniform_mat4* transform_uniform() { return new uniforms_config::Uniform_mat4(this->_transform); };

		void apply(Transform3D& parent_transform, enums::TRANSFORM_TYPE transform_type = enums::TRANSFORM_TYPE::TT_GLOBAL);
	};
}



#endif // !__R_TRANSFORM__
