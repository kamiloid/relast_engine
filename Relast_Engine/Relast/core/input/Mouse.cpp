//#include "Mouse.h"
#include"../../Relast_Engine.h"

void Relast::input::mouse_event(Relast::input::mouse_callback config)
{
	glfwSetMouseButtonCallback(config._window, config._buttons_callback);
}