#pragma once
#ifndef __R_CAMERA__
#define __R_CAMERA__

//#include"Entities.h"
#include"Primitives.h"

namespace Relast
{
	namespace scene_manager
	{
		class Camera:public Entity3D
		{
		private:
			void setup_projection();
		protected:
			glm::vec3 _itarget, _target = glm::vec3(0.0f);
			glm::mat4 _view, _proj;
			FLOAT _fov, _aspect_ratio, _near, _far;
			FLOAT _izoom, _zoom = 0.0f;

			glm::vec3 _acum_pos = glm::vec3();

		public:
			Camera_config* _cam_config;

			glm::vec2 _mouse;



			Camera(Camera_config* config) :Entity3D() { this->_cam_config = config; };
			virtual ~Camera() {};

			Basic_Mesh* _temp_mesh = nullptr;


			glm::vec3 get_initial_target() { return this->_itarget; };
			glm::vec3 get_target() { return this->_target; };
			glm::mat4 get_view() { return this->_view; };
			glm::mat4 get_projection() { return this->_proj; };
			FLOAT get_initial_zoom() { return this->_izoom; };
			FLOAT get_zoom() { return this->_zoom; };
			enums::CAMERA_TYPE get_camera_type() { return this->_cam_config->_camera_type; };

			void set_initial_target(FLOAT x, FLOAT y, FLOAT z)
			{
				this->_itarget = glm::vec3(x, y, z);
				this->_target = glm::vec3(x, y, z);
			};
			void set_target(FLOAT x, FLOAT y, FLOAT z)
			{
				this->_target = glm::vec3(x, y, z);
			};
			void set_initial_zoom(FLOAT zoom = 0.0f)
			{
				this->_izoom = zoom;
				this->_zoom = zoom;
			};
			void set_zoom(FLOAT zoom = 0.0f)
			{
				this->_zoom = zoom;
			};

			virtual void loop();

			void rotate_target(glm::vec3 angles);
			void move_target(glm::vec3 movement);
		};
	}
}


#endif // !__R_CAMERA__