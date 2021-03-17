#pragma once
#ifndef __RE_INPUT_GESTURES__
#define __RE_INPUT_GESTURES__


#include"Relast/Relast_Engine.h"

namespace ed_input
{
	namespace mouse
	{
		enum BUTTON_STATE { BS_UP, BS_PRESS };
		enum MOUSE_STATE { MS_STATIC, MS_MOVING };
		enum MOUSE_ACTIVATE { MA_OFF, MA_ON };

		struct Mouse_config
		{
			GLFWwindow* _window;
			Relast::Engine* _engine;

			Mouse_config(GLFWwindow* window, Relast::Engine* engine)
			{
				this->_window = window;
				this->_engine = engine;
			}
		};

		void start_mouse_input(Mouse_config* config);
		void mouse_buttons_events(GLFWwindow* window, int button, int action, int mods);

		void loop_mouse();
		void play_mouse();
		void stop_mouse();
		BUTTON_STATE get_left_button_state();
		BUTTON_STATE get_middle_button_state();
		BUTTON_STATE get_right_button_state();
		glm::vec2 get_mouse_coords();


		void mouse_gestures();
		glm::vec3 mouse_selection();
	}
}


#endif // !__RE_INPUT_GESTURES__
