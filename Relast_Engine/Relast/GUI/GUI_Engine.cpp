#include"../Relast_Engine.h"

void Relast::imgui::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
}

void Relast::imgui::style_color(Style_color style)
{
	if (style == Style_color::CLASSIC)
		ImGui::StyleColorsClassic();
	else if (style == Style_color::DARK)
		ImGui::StyleColorsDark();
	else if (style == Style_color::LIGHT)
		ImGui::StyleColorsLight();
}

const char* Relast::imgui::glsl_version()
{
	return "#version 130";
}

void Relast::imgui::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void Relast::imgui::loop()
{
	ImGui::NewFrame();
}

void Relast::imgui::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}




void Relast::imgui_glfw::init(GLFWwindow* window, const char* glsl_version)
{
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void Relast::imgui_glfw::shutdown()
{
	ImGui_ImplGlfw_Shutdown();
}

void Relast::imgui_glfw::loop()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
}