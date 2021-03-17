#pragma once
#ifndef __R_TEXTURE__
#define __R_TEXTURE__

#include<iostream>
#include<string>

#include"Tools.h"

namespace Relast
{
	class Texture
	{
	private:
		Texture_config* _config;
		unsigned char* _texture;
		UINT _texture_object;
		String _file;
		Recti* _texture_rect;
		INT _channels;
	public:
		Texture() {};
		Texture(String name);
		Texture(Texture_config* config);
		~Texture() {};

		UINT get_texId() { return this->_texture_object; }
		Texture* load(String file_path = "");
		Texture* setup();

		void reconfig(Texture_config* config) { this->_config = config; };
	};

	Texture* create_texture(String name);
}

#endif // !__R_TEXTURE__