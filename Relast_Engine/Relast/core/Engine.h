#pragma once
#ifndef __R_ENGINE__
#define __R_ENGINE__

namespace Relast
{
	struct Engine_params
	{
		S_UINT _w, _h; 
		String _win_title;

		Engine_params(S_UINT width=800, S_UINT height=600, String title="Relast Window");
	};

	class Engine
	{
	private:
		Rectf _viewport_size;
		GLFWwindow* _window;
		Engine_params _params;
		std::vector<scene_manager::Scene*> _scenes;
		scene_manager::Camera* _main_camera;
		enums::TRANSFORM_TYPE _trans_type = enums::TRANSFORM_TYPE::TT_GLOBAL;
	protected:
	public:
		static void add_2_render(scene_manager::Node* node);

		Engine();
		~Engine();

		Color _color;

		GLFWwindow* get_window();
		int init(Engine_params params);
		void end();
		bool run();
		void clear();
		void swap();
		void loop();
		void render();

		enums::TRANSFORM_TYPE get_transform_type() { return this->_trans_type; };
		Rectf get_viewport_size() { return this->_viewport_size; };

		scene_manager::Scene* get_scene(UINT index = 0) { return this->_scenes[index]; };
		scene_manager::Camera* get_main_camera() { return this->_main_camera; };

		void add_scene(scene_manager::Scene_config* config);
		void set_main_camera(scene_manager::Camera* camera) { this->_main_camera = camera; };
		void set_transform_type(enums::TRANSFORM_TYPE type) { this->_trans_type = type; }
	};
};


#endif // !__R_ENGINE__