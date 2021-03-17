#pragma once
#ifndef __RE_CONSOLE__
#define __RE_CONSOLE__

#include<iostream>
#include<string>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"Main_menu.h"

namespace addons
{
	namespace console
	{
		void init();
	}
}


#endif // !__RE_CONSOLE__