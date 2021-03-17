#include"../Relast_Engine.h"
#include"../deps/stb_image/stb_image.h"

Relast::Texture* Relast::create_texture(String name)
{
	Texture_config* config = new Texture_config(name);
	Texture* texture = new Texture(config);
	return texture;
}



Relast::Texture::Texture(String name)
{
	this->_config = new Texture_config(name);
}

Relast::Texture::Texture(Texture_config* config)
{
	this->_config = config;
}

Relast::Texture* Relast::Texture::load(String file_path)
{
	stbi_set_flip_vertically_on_load(true);//next into the tools.h - temporally

	this->_file = file_path == "" ? this->_config->_file : file_path;
	this->_config->_file = this->_file;
	this->_config->analize_format();
	INT w, h;
	this->_texture = stbi_load(this->_file.c_str(), &w, &h, &this->_channels, 0);
	if (!this->_texture)
	{
		std::cout << "Error loading texture: " << this->_config->_name << std::endl;
		stbi_image_free(this->_texture);
		return this;
	}
	this->_texture_rect = new Recti(0, 0, w, h);
	return this;
}

Relast::Texture* Relast::Texture::setup()
{
	glGenTextures(1, &this->_texture_object);
	glBindTexture(GL_TEXTURE_2D, this->_texture_object);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (this->_texture)
	{
		GLenum format;
		if (this->_channels == 1)
			format = GL_RED;
		else if (this->_channels == 3)
			format = GL_RGB;
		else if (this->_channels == 4)
			format = GL_RGBA;
		GLenum channels_validation = this->_config->_format == enums::IMAGE_FORMAT::IF_PNG ? GL_RGBA : GL_RGB;
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->_texture_rect->_w, this->_texture_rect->_h, 0, channels_validation, GL_UNSIGNED_BYTE, this->_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, this->_texture_rect->_w, this->_texture_rect->_h, 0, format, GL_UNSIGNED_BYTE, this->_texture);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else
		std::cout << "Error loading texture: " << this->_config->_name << std::endl;

	stbi_image_free(this->_texture);
	return this;
}