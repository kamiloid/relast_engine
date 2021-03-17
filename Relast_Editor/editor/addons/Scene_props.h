#pragma once
#ifndef __RE_SCENEPROPS__
#define __RE_SCENEPROPS__

#include<iostream>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"Main_menu.h"
//#include"../../Relast/core/DataType.h"
//#include"../../Relast/core/Tools.h"
#include"Relast/scene_manager/Scene.h"

namespace addons
{
	namespace scene
	{
		void init_props(Relast::scene_manager::Scene_config* scene_props, 
			Relast::scene_manager::Camera_config* camera_config);
	}
}

#endif // !__RE_SCENEPROPS__