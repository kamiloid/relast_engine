#pragma once
#ifndef __R_GUI_ENGINE__
#define __R_GUI_ENGINE__


#include"../core/DataType.h"

#include"../deps/ImGui/imgui.h"
#include"../deps/ImGui/imgui_impl_glfw.h"
#include"../deps/ImGui/imgui_impl_opengl3.h"

namespace Relast
{
	namespace imgui
	{
		enum Style_color {
			DARK,
			LIGHT,
			CLASSIC
		};

		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		//IMGUI SETUP METHODS
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		void init();
		void style_color(Style_color style);
		const char* glsl_version();
		void shutdown();
		void loop();
		void render();
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		//IMGUI OPERATIONAL METHODS
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
	}
	namespace imgui_glfw
	{
		void init(GLFWwindow* window, const char* glsl_version);
		void shutdown();
		void loop();
	}
}

#endif // !__R_GUI_ENGINE__