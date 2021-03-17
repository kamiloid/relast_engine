#pragma once
#ifndef __RE_MAINMENU__
#define __RE_MAINMENU__

#include<iostream>
#include<string>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

namespace addons
{
	namespace main_menu
	{
		void init();
	}

	class Main_Menu
	{
	public:
		static bool _file_new_proj;
		static bool _file_open_proj;
		static bool _file_save_proj;
		static bool _file_close_proj;

		static bool _file_new_scene;
		static bool _file_open_scene;
		static bool _file_save_scene;
		static bool _file_save_scene_as;
		static bool _file_close_scene;

		static bool _scene_props;

		static bool _panel_toolbox;
		static bool _panel_assets;
		static bool _panel_console;
		static bool _panel_scenegraph;
		static bool _panel_props;

		static bool _about_relast;

		static void reset_values();
	};

	class Scene_Graph_Menu
	{
	public:
		static bool _sm_new_empty_node;
		static bool _sm_new_layer;
		static bool _sm_new_camera;
		static bool _sm_new_spot_light;
		static bool _sm_new_point_light;
		static bool _sm_new_ambient_light;
		static bool _sm_new_specular_light;
		static bool _sm_new_diffuse_light;
	};
}


#endif // !__RE_MAINMENU__