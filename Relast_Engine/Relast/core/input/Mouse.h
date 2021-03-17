#pragma once

#ifndef __R_MOUSE__
#define __R_MOUSE__

//#include"../Tools.h"

namespace Relast
{
	namespace input
	{
		struct mouse_callback
		{
			GLFWwindow* _window;
			GLFWmousebuttonfun _buttons_callback;
		};
		void mouse_event(mouse_callback config);
	}
}


#endif // !__R_MOUSE__
