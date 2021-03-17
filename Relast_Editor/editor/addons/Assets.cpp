#include"Assets.h"


void addons::assets::init()
{
	if (Main_Menu::_panel_assets)
	{
		ImGui::Begin("Assets", &Main_Menu::_panel_assets, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		ImGui::Text("This is the panel to manage the assets in the project");
		ImGui::End();
	}
}