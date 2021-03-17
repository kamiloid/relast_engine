#include"../Relast_Engine.h"

void Relast::Transform3D::apply(Transform3D& parent_transform, 
	enums::TRANSFORM_TYPE transform_type)
{
		glm::vec3 pos = this->_position;
		glm::vec3 rot = this->_rotation;
		glm::vec3 scale = this->_scale;

		this->_transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::toMat4(glm::quat(rot * _RAD_));
		this->_transform = glm::scale(this->_transform, scale);
}