#include"Toolbox.h"


void addons::toolbox::init()
{
	bool open = true;
	if (addons::Main_Menu::_panel_toolbox)
	{
		ImGui::Begin("ToolBox", &addons::Main_Menu::_panel_toolbox, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		ImGui::Button("aaa");
		ImGui::Button("bbb");
		ImGui::Button("ccc");
		ImGui::Button("ddd");
		ImGui::End();
	}
}