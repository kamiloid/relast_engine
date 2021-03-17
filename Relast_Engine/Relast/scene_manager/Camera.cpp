#include"../Relast_Engine.h"

void Relast::scene_manager::Camera::setup_projection()
{
	if (this->_cam_config->_viewport_size._x == this->_cam_config->_viewport_size._w)
	{
		this->_cam_config->_viewport_size._x -= 0.00001f;
		this->_cam_config->_viewport_size._w += 0.00001f;
	}
	if (this->_cam_config->_viewport_size._y == this->_cam_config->_viewport_size._h)
	{
		this->_cam_config->_viewport_size._y -= 0.00001f;
		this->_cam_config->_viewport_size._h += 0.00001f;
	}

	if (this->_cam_config->_type == enums::PROJECTION_TYPE::PT_PERSPECTIVE)
		this->_proj = glm::perspective(this->_cam_config->_fov - this->_zoom / 10, this->_cam_config->_ratio, this->_cam_config->_near, this->_cam_config->_far);
	else
		this->_proj = glm::ortho(this->_cam_config->_viewport_size._x, this->_cam_config->_viewport_size._w, this->_cam_config->_viewport_size._y, this->_cam_config->_viewport_size._h);
}

void Relast::scene_manager::Camera::loop()
{
	Entity3D::loop();

	this->_view = glm::mat4(1.0f);
	if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_EDITOR)
	{
		/*this->_view = glm::translate(this->_view, -this->_transform._position) *
			glm::rotate(this->_view, glm::radians(this->_transform._rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(this->_view, glm::radians(this->_transform._rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(this->_view, glm::radians(this->_transform._rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));*/
		this->_view = glm::translate(this->_view, -this->_transform._position) *
			glm::toMat4(glm::quat(this->_transform._rotation * _RAD_));
	}
	else if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_FPS || this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_SIMPLE)
	{
		glm::vec3 viewer = this->_transform._position;
		glm::vec3 target = this->_target;

		if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_SIMPLE)
		{
			/*glm::vec3 diff = -this->_target + this->_pos;
			FLOAT dist = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);*/

			/*glm::vec3 angles = glm::vec3(
				sin(-this->_rot2.x * _RAD_) * glm::cos(_RAD_ * this->_rot2.y),
				sin(_RAD_ * this->_rot2.y),
				cos(_RAD_ * this->_rot2.x) * cos(_RAD_ * this->_rot2.y)
			);*/

			/*viewer.x = dist * angles.x;
			viewer.y = dist * angles.y;
			viewer.z = dist * angles.z;*/


			/*glm::mat4 origen = glm::translate(glm::mat4(1.0f), target);
			origen = glm::rotate(origen, glm::radians(-this->_rot2.x), glm::vec3(0.0f, 1.0f, 0.0f));

			glm::vec3 basex = { origen[0][0], 0.0f, origen[0][2] };
			glm::vec3 basez = { origen[2][0], 0.0f, origen[2][2] };*/




			/*glm::vec3 dxzm = glm::vec3(this->_mouse.x, 0.0f, this->_mouse.y) - target;
			FLOAT dxzmmag = math::v3_mag(dxzm);*/





			//this->_temp_mesh->set_rotation(0, this->_rot2.x, 0);

		}
		//target = target;
		//viewer = viewer + target;
		//this->_view = glm::lookAt(viewer, target, glm::vec3(0.0f, 1.0f, 0.0f));
		this->_view = glm::lookAt(viewer, glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	this->setup_projection();
}



void Relast::scene_manager::Camera::rotate_target(glm::vec3 angles)
{
	if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_SIMPLE)
	{
		glm::vec2 mouse = this->_mouse;
		glm::vec3 viewer = this->_transform._position;
		glm::vec3 target = this->_target;
		glm::vec3 rot = angles;


		FLOAT angMag = math::v3_mag(angles);

		glm::vec3 mdxz = { mouse.x - target.x, 0.0f, mouse.y - target.z };
		FLOAT mdxzMag = math::v3_mag(mdxz);



		glm::mat4 origen = glm::translate(glm::mat4(1.0f), target);
		origen = glm::rotate(origen, glm::radians(rot.x), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 basex = { origen[0][0], 0.0f, origen[0][2] };
		glm::vec3 basez = { origen[2][0], 0.0f, origen[2][2] };

		this->_transform._rotation = rot;

		this->_temp_mesh->_transform._rotation = glm::vec3(0, rot.x, 0);

		this->_target = target;
	}
}

void Relast::scene_manager::Camera::move_target(glm::vec3 movement)
{
	if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_SIMPLE)
	{
		glm::vec2 mouse = this->_mouse;
		glm::vec3 viewer = this->_transform._position;
		glm::vec3 target = this->_target;

		glm::vec3 mdxz = { mouse.x - target.x, 0.0f, mouse.y - target.z };
		FLOAT mdxzMag = math::v3_mag(mdxz);

		


		this->_temp_mesh->_transform._position = glm::vec3(target.x, target.y, target.z);

		this->_target = target;
	}
	else if (this->_cam_config->_camera_type == enums::CAMERA_TYPE::CT_EDITOR)
	{
		//glm::vec3 viewer = this->_pos;
		//movement += this->_acum_pos;

		FLOAT movMag = math::v3_mag(movement);
		/*this->_pos.x = -movement.x;
		this->_pos.y = movement.y;*/

		this->_acum_pos = this->_transform._position;
		//this->_pos = viewer;
	}
}