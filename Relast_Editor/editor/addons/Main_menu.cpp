#include"Main_menu.h"

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//COMMANDS DECLARATION
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
bool addons::Main_Menu::_file_new_proj = false;
bool addons::Main_Menu::_file_open_proj = false;
bool addons::Main_Menu::_file_save_proj = false;
bool addons::Main_Menu::_file_close_proj = false;

bool addons::Main_Menu::_file_new_scene = false;
bool addons::Main_Menu::_file_open_scene = false;
bool addons::Main_Menu::_file_save_scene = false;
bool addons::Main_Menu::_file_save_scene_as = false;
bool addons::Main_Menu::_file_close_scene = false;

bool addons::Main_Menu::_scene_props = false;

bool addons::Main_Menu::_panel_assets = false;
bool addons::Main_Menu::_panel_toolbox = true;
bool addons::Main_Menu::_panel_console = false;
bool addons::Main_Menu::_panel_scenegraph = false;
bool addons::Main_Menu::_panel_props = false;

bool addons::Main_Menu::_about_relast = false;
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
bool addons::Scene_Graph_Menu::_sm_new_empty_node = false;
bool addons::Scene_Graph_Menu::_sm_new_layer = false;
bool addons::Scene_Graph_Menu::_sm_new_camera = false;
bool addons::Scene_Graph_Menu::_sm_new_spot_light = false;
bool addons::Scene_Graph_Menu::_sm_new_point_light = false;
bool addons::Scene_Graph_Menu::_sm_new_ambient_light = false;
bool addons::Scene_Graph_Menu::_sm_new_specular_light = false;
bool addons::Scene_Graph_Menu::_sm_new_diffuse_light = false;
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

void addons::main_menu::init()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if(ImGui::MenuItem("New Project..."))
				Main_Menu::_file_new_proj = true;
			if(ImGui::MenuItem("Open Project..."))
				Main_Menu::_file_open_proj = true;
			if(ImGui::MenuItem("Save Project"))
				Main_Menu::_file_save_proj = true;
			if(ImGui::MenuItem("Close Project"))
				Main_Menu::_file_close_proj = true;
			ImGui::Separator();
			if(ImGui::MenuItem("New Scene..."))
				Main_Menu::_file_new_scene = true;
			if(ImGui::MenuItem("Open Scene..."))
				Main_Menu::_file_open_scene = true;
			if(ImGui::MenuItem("Save Scene"))
				Main_Menu::_file_save_scene = true;
			if(ImGui::MenuItem("Save Scene as..."))
				Main_Menu::_file_save_scene_as = true;
			ImGui::Separator();
			if(ImGui::MenuItem("Close Editor"))
				Main_Menu::_file_close_scene = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scene"))
		{
			//std::cout << Main_Menu::_panel_toolbox << std::endl;
			if (ImGui::MenuItem("Scene properties..."))
				Main_Menu::_scene_props = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			//std::cout << Main_Menu::_panel_toolbox << std::endl;
			if (ImGui::MenuItem("Scene Graph"))
				Main_Menu::_panel_scenegraph = true;
			if (ImGui::MenuItem("Properties"))
				Main_Menu::_panel_props = true;
			if (ImGui::MenuItem("Assets"))
				Main_Menu::_panel_assets = true;
			ImGui::Separator();
			if (ImGui::MenuItem("Toolbox"))
				Main_Menu::_panel_toolbox = true;
			ImGui::Separator();
			if (ImGui::MenuItem("Console"))
				Main_Menu::_panel_console = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("About"))
		{
			ImGui::MenuItem("About Relast...");
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}



void addons::Main_Menu::reset_values()
{
	Main_Menu::_panel_assets = 
	Main_Menu::_panel_toolbox =
	Main_Menu::_panel_console =
	Main_Menu::_panel_scenegraph =
	Main_Menu::_panel_props = 
	Main_Menu::_scene_props = false;
}