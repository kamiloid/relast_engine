#include"Input_gestures.h"
#include"Relast/deps/ImGizmo/ImGuizmo.h"


namespace ed_input
{
	namespace mouse
	{
		Mouse_config* _mouse_config;

		MOUSE_ACTIVATE _active = MOUSE_ACTIVATE::MA_ON;

		BUTTON_STATE _rbutton = BUTTON_STATE::BS_UP;
		BUTTON_STATE _mbutton = BUTTON_STATE::BS_UP;
		BUTTON_STATE _lbutton = BUTTON_STATE::BS_UP;
		MOUSE_STATE _mstate = MOUSE_STATE::MS_STATIC;

		DOUBLE _mouse_x, _mouse_y = 0;
		glm::vec2 _imouse;
		glm::vec2 _mouse;
		glm::vec2 _mouse_diff;

		glm::vec2 _last_cam_rotation;
		glm::vec2 _last_cam_position;

		FLOAT _mouse_pos_speed = 200.0f;

		float a = 0.0f;

		glm::vec3 _cam_rot = glm::vec3();
	}
}

void ed_input::mouse::start_mouse_input(Mouse_config* config)
{
	_mouse_config = config;

	glfwSetMouseButtonCallback(_mouse_config->_window, mouse_buttons_events);
	_mouse_diff = glm::vec2();
	_imouse = glm::vec2();
}

void ed_input::mouse::mouse_buttons_events(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS)
			_rbutton = BUTTON_STATE::BS_PRESS;
		else
			_rbutton = BUTTON_STATE::BS_UP;
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		if (action == GLFW_PRESS)
			_mbutton = BUTTON_STATE::BS_PRESS;
		else
			_mbutton = BUTTON_STATE::BS_UP;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			_lbutton = BUTTON_STATE::BS_PRESS;
		else
			_lbutton = BUTTON_STATE::BS_UP;
	}
}






void ed_input::mouse::loop_mouse()
{
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow) ||
		ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || ImGui::IsAnyItemFocused() ||
		ImGuizmo::IsUsing())
		stop_mouse();
	else
		play_mouse();

	if(_active == MOUSE_ACTIVATE::MA_OFF) return;

	if (_mouse_config == nullptr) return;
	glfwGetCursorPos(_mouse_config->_window, &_mouse_x, &_mouse_y);
}

void ed_input::mouse::play_mouse()
{
	_active = MOUSE_ACTIVATE::MA_ON;
}

void ed_input::mouse::stop_mouse()
{
	_active = MOUSE_ACTIVATE::MA_OFF;
}

ed_input::mouse::BUTTON_STATE ed_input::mouse::get_left_button_state()
{
	return ed_input::mouse::_lbutton;
}
ed_input::mouse::BUTTON_STATE ed_input::mouse::get_middle_button_state()
{
	return ed_input::mouse::_mbutton;
}
ed_input::mouse::BUTTON_STATE ed_input::mouse::get_right_button_state()
{
	return ed_input::mouse::_rbutton;
}

glm::vec2 ed_input::mouse::get_mouse_coords()
{
	return glm::vec2(_mouse_x, _mouse_y);
}



void ed_input::mouse::mouse_gestures()
{
	if (_active == MOUSE_ACTIVATE::MA_OFF) return;

	Relast::scene_manager::Camera* view_camera = _mouse_config->_engine->get_main_camera();
	_mouse = get_mouse_coords();
	view_camera->_mouse = _mouse;

	if (ed_input::mouse::get_middle_button_state() == ed_input::mouse::BS_PRESS)
	{
		_mouse_diff = _mouse - _imouse;
		FLOAT dist = sqrt(_mouse_diff.x * _mouse_diff.x + _mouse_diff.y * _mouse_diff.y);

		glm::vec2 rot = _last_cam_rotation + _mouse_diff;

		if(view_camera->get_camera_type() == Relast::enums::CAMERA_TYPE::CT_EDITOR)
			view_camera->_transform._rotation = glm::vec3(rot.y, rot.x, 0.0f);
		else {
			//_cam_rot = glm::vec3(_mouse_diff, 0.0f);
			//view_camera->_rot2 += glm::vec3(_mouse_diff.x - view_camera->_rot2.x, _mouse_diff.y - view_camera->_rot2.y, 0.0f) / 10.0f;
			//view_camera->set_rotation(_cam_rot.x, _cam_rot.y, 0);

			//view_camera->rotate_target(glm::vec3(_mouse_diff, 0.0f));
		}
	}
	else if (ed_input::mouse::get_left_button_state() == ed_input::mouse::BS_PRESS)
	{
		_mouse_diff = _mouse - _imouse;
		FLOAT dist = sqrt(_mouse_diff.x * _mouse_diff.x + _mouse_diff.y * _mouse_diff.y);

		_mouse_diff /= _mouse_pos_speed;
		glm::vec2 pos = _last_cam_position + _mouse_diff;
		if (view_camera->get_camera_type() == Relast::enums::CAMERA_TYPE::CT_EDITOR)
		{
			view_camera->_transform._position.x = -pos.x;
			view_camera->_transform._position.y = pos.y;
		}
		//_mouse_diff.x /= _mouse_config->_engine->get_viewport_size()._w;
		//_mouse_diff.y /= _mouse_config->_engine->get_viewport_size()._h;
		////std::cout << _mouse_diff.x << std::endl;
		//FLOAT dist = sqrt(_mouse_diff.x * _mouse_diff.x + _mouse_diff.y * _mouse_diff.y);
		//
		//view_camera->move_target(glm::vec3(_mouse_diff, 0.0f));
	}
	else {
		_imouse = _mouse;
		if (_mouse_diff.x != 0 && _mouse_diff.y != 0)
		{
			_last_cam_rotation.x = view_camera->_transform._rotation.y;
			_last_cam_rotation.y = view_camera->_transform._rotation.x;

			_last_cam_position.x = -view_camera->_transform._position.x;
			_last_cam_position.y = view_camera->_transform._position.y;
			a = _last_cam_position.x;
		}
		_mouse_diff = glm::vec2();
	}


	//if (ImGui::Begin("Mouse tests"))
	//{
	//	String mouse_diff = std::to_string(_mouse_diff.x) + " | " + std::to_string(_mouse_diff.y);
	//	ImGui::Text(mouse_diff.c_str());
	//	String last_mouse_pos = std::to_string(_last_cam_position.x) + " | " + std::to_string(_last_cam_position.y);
	//	ImGui::Text(last_mouse_pos.c_str());
	//	String cam_rot = std::to_string(view_camera->_transform._position.x) + " | " + std::to_string(view_camera->_transform._position.y);
	//	ImGui::Text(cam_rot.c_str());
	//	String astr = std::to_string(a);
	//	ImGui::Text(astr.c_str());
	//	ImGui::End();
	//}
}


glm::vec3 ed_input::mouse::mouse_selection()
{
	INT w = _mouse_config->_engine->get_viewport_size()._w;
	INT h = _mouse_config->_engine->get_viewport_size()._h;
	INT ww, wh, wx, wy;
	FLOAT depth = 0.0f;
	glfwGetWindowSize(_mouse_config->_window, &ww, &wh);
	glfwGetWindowPos(_mouse_config->_window, &wx, &wy);
	glm::vec4 viewport = glm::vec4(0, 0, w, h);
	glm::vec3 wincoord = glm::vec3(wx, ww - wy - 1, depth);
	glm::mat4 view = _mouse_config->_engine->get_main_camera()->get_view();
	glm::mat4 projection = _mouse_config->_engine->get_main_camera()->get_projection();
	glm::vec3 objcoord = glm::unProject(wincoord, view, projection, viewport);

	if (ImGui::Begin("Mouse tests"))
	{
		//String is_hover = std::to_string(ImGui::IsAnyItemHovered());
		String is_hover = std::to_string(ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow));
		ImGui::Text(is_hover.c_str());
		String coords = std::to_string(-objcoord.x) + " | " + std::to_string(-objcoord.y) + " | " + std::to_string(objcoord.z);
		ImGui::Text(coords.c_str());
		ImGui::End();
	}


	return objcoord;
}