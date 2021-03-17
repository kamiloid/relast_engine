#include"Test1.h"

void addons::test1::init()
{
	bool open_win = true;
	ImGui::Begin("Test_1", &open_win, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Press me"))
	{
		std::cout << "aaaaaaaaaaa" << std::endl;
	}
	ImGui::End();
}