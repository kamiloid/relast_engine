#pragma once

//#include<GL/glew.h>
//#include<GL/GLU.h>
//#include<GLFW/glfw3.h>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"../Relast_Engine/Relast/core/Tools.h"

namespace addons
{
	struct Viewport_renderer_config
	{
		String _title = "";
		bool _open = true;
		ImGuiWindowFlags_ _flags;
		Relast::Recti _rect;

		Viewport_renderer_config(String title, bool open = true, ImGuiWindowFlags_ flags = ImGuiWindowFlags_::ImGuiWindowFlags_None)
		{
			this->_title = title;
			this->_open = open;
			this->_flags = flags;
			this->_rect._w = 800;
			this->_rect._h = 800;
		}
	};
	class Viewport_renderer
	{
	private:
		Viewport_renderer_config* _config;
	public:
		Viewport_renderer() {};
		Viewport_renderer(Viewport_renderer_config* config);
		~Viewport_renderer() {};

		void init();
	};
}