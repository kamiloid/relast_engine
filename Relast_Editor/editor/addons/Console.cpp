#include"Console.h"

void addons::console::init()
{
	if (Main_Menu::_panel_console)
	{
		ImGui::Begin("console", &Main_Menu::_panel_console);
		ImGui::Text("Here must be the console content input and output");
		ImGui::End();
	}
}