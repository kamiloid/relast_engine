#include"Scene_props.h"
#include"Relast/core/Tools.h"


void addons::scene::init_props(Relast::scene_manager::Scene_config* scene_props, 
	Relast::scene_manager::Camera_config* camera_config)
{
	if (Main_Menu::_scene_props)
	{
		ImGui::Begin("Scene properties", &Main_Menu::_scene_props);
		char* scene_name = Relast::string::string_2_array(scene_props->_name);
		if(ImGui::InputText("Scene name", scene_name, sizeof(scene_props->_name)))
			scene_props->_name = Relast::string::array_2_string(scene_name);
		if (ImGui::TreeNode("Background color"))
		{
			static ImVec4 color = ImVec4(scene_props->_bgcolor._r, scene_props->_bgcolor._g, scene_props->_bgcolor._b, scene_props->_bgcolor._a);
			ImGui::ColorEdit3("RGB Color", (float*)&color);
			scene_props->_bgcolor.set_color(color.x, color.y, color.z, color.w);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Main camera"))
		{
			
			const char* cam_proj[] = { "Perspective", "Orthogonal" };
			INT trans_items_l = sizeof(cam_proj) / sizeof(*cam_proj);
			INT selected_cam_proj = camera_config->_type;
			const char* cam_type = cam_proj[selected_cam_proj];
			if (ImGui::BeginCombo("Projection", cam_type, ImGuiComboFlags_NoArrowButton))
			{
				for (INT i = 0; i < trans_items_l; i++)
				{
					bool is_selected = (selected_cam_proj == i);
					if (ImGui::Selectable(cam_proj[i], is_selected))
					{
						selected_cam_proj = i;
						camera_config->_type = (Relast::enums::PROJECTION_TYPE)i;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (selected_cam_proj == 0)
			{
				ImGui::BeginChild("Projection size", ImVec2(), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
					ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize |
					ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
					ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
				FLOAT near = camera_config->_near, far = camera_config->_far, fov = camera_config->_fov, ratio = camera_config->_ratio;
				ImGui::DragFloatRange2("Near/Far", &near, &far, 0.25f, 0.0f, 99999.0f, "Min: %.1f %%", "Max: %.1f %%", ImGuiSliderFlags_AlwaysClamp);
				camera_config->_near = near;
				camera_config->_far = far;
				ImGui::Separator();
				ImGui::DragFloat("Aspect ratio", &ratio, 0.005f);
				ImGui::Separator();
				ImGui::DragFloat("Field of view", &fov, 0.005f);
				camera_config->_fov = fov;
				camera_config->_ratio = ratio;
				ImGui::EndChild();
			}
			else {
				ImGui::BeginChild("Projection size", ImVec2(), true, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize |
				ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_::ImGuiWindowFlags_NoMove);
				FLOAT left, right, top, bottom;
				left = camera_config->_viewport_size._x;
				right = camera_config->_viewport_size._w;
				top = camera_config->_viewport_size._y;
				bottom = camera_config->_viewport_size._h;
				ImGui::DragFloatRange2("Left/Right", &left, &right, 0.005f);
				ImGui::DragFloatRange2("Top/Bottom", &top, &bottom, 0.005f);
				camera_config->_viewport_size._x = left;
				camera_config->_viewport_size._y = top;
				camera_config->_viewport_size._w = right;
				camera_config->_viewport_size._h = bottom;
				ImGui::EndChild();
			}

			ImGui::TreePop();
		}

		ImGui::End();
	}
}