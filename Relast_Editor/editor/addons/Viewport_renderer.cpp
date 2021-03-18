#include"Viewport_renderer.h"

addons::Viewport_renderer::Viewport_renderer(addons::Viewport_renderer_config* config)
{
	this->_config = config;
}

void addons::Viewport_renderer::init()
{
	GLuint frame_render;
	glGenTextures(1, &frame_render);
	glBindTexture(GL_TEXTURE_2D, frame_render);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_config->_rect._w, this->_config->_rect._h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_render, 0);

	if (ImGui::Begin(
		this->_config->_title.c_str(),
		&this->_config->_open,
		this->_config->_flags ||
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize))
	{
		ImGui::GetWindowDrawList()->AddImage(
			(void*)frame_render, 
			ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowSize().x - 15,
				ImGui::GetCursorScreenPos().y + ImGui::GetWindowSize().y - 35),
			ImVec2(0, 1),
			ImVec2(1, 0));
		ImGui::End();
	}
}