#pragma once
#ifndef __R_SHADER__
#define __R_SHADER__

#define _MAP_DIFFUSE_ "diffuse_map"
#define _MAP_SPECULAR_ "specular_map"

#include<iostream>
#include<map>
#include<vector>
//#include"GL/glew.h"
//#include"GLFW/glfw3.h"
#include"GL/glew.h"
#include"GLFW/glfw3.h"

#include"Tools.h"
#include"Texture.h"

namespace Relast
{
	class Shader
	{
	private:
		String _name = "";
		UINT _prog;
		GLuint _vs;
		GLuint _fs;
		String _vcode;
		String _fcode;
		std::map<String, Texture*> _textures;

		std::map<String, Shader_uniform*> _uniforms;
		std::vector<String> _uniforms_list;
		std::vector<String> _uniforms_types_list;

		void create_program();
		UINT check_program();
		UINT compile_shader(GLuint& shader, String source, enums::SHADER_TYPE type);

		static std::vector<shader_structs_config::Shader_struct> read_structs(String shaderstr);
	public:
		static Relast::Shader_config split_strShader(String shaderstr);

		Shader(String name, String vertex_shader, String fragment_shader);
		~Shader();
		UINT get_program() { return this->_prog; }
		std::map<String, Texture*> get_textures() { return this->_textures; };
		std::map<String, Shader_uniform*> get_uniforms() { return this->_uniforms; };

		UINT compile();
		void use();

		void set_uniforms_list(std::vector<String> uniforms, std::vector<String> types);
		Shader_uniform* create_uniform(String name, enums::SHADER_UNIFORM_TYPE type);
		Shader_uniform* get_uniform(String name);
		void setup_uniforms();
		void run_uniform_i1(String uniform_name, INT i);
		void run_uniform_f1(String uniform_name, FLOAT f);
		void run_uniform_f2(String uniform_name, FLOAT f1, FLOAT f2);
		void run_uniform_f3(String uniform_name, FLOAT f1, FLOAT f2, FLOAT f3);
		void run_uniform_f4(String uniform_name, FLOAT f1, FLOAT f2, FLOAT f3, FLOAT f4);
		void run_uniform_m4(String uniform_name, glm::mat4 matrix);

		bool has_texture(String texture_key);
		Texture* get_texture(String texture_key);
		Texture* add_texture(Texture_config* _config);
		Texture* add_texture(String name, String file = "");
		void setup_texture(String texture_key);
		void texture(String texture_key);
	};


	class Material
	{
	private:
		Material_config _config;
		String _name;
		String _id;
		Shader* shader;
	public:
		Material() 
		{
			/*this->create_map_category(_MAP_DIFFUSE_);
			this->create_map_category(_MAP_SPECULAR_);*/
		};
		~Material() {};

		Color _ambient_color = Color();
		Color _diffuse_color = Color();
		Color _specular_color = Color();
		//std::map<String, std::vector<Texture*>> _maps;
		std::map<String, Texture*> _maps;
		FLOAT _shininess = 0.5f;

		Material_config get_config() { return this->_config; };
		uniforms_config::Uniform_3f* ambient_color_uniform() { return new uniforms_config::Uniform_3f(this->_ambient_color._r, this->_ambient_color._g, this->_ambient_color._b); };
		uniforms_config::Uniform_3f* diffuse_color_uniform() { return new uniforms_config::Uniform_3f(this->_diffuse_color._r, this->_diffuse_color._g, this->_diffuse_color._b); };
		uniforms_config::Uniform_3f* specular_color_uniform() { return new uniforms_config::Uniform_3f(this->_specular_color._r, this->_specular_color._g, this->_specular_color._b); };
		uniforms_config::Uniform_1f* shininess_uniform() { return new uniforms_config::Uniform_1f(this->_shininess); };
		uniforms_config::Uniform_1i* diffuse_map_uniform(INT index) { return new uniforms_config::Uniform_1i(index); };
		uniforms_config::Uniform_1i* specular_map_uniform(INT index) { return new uniforms_config::Uniform_1i(index); };

		Shader* get_shader() { return this->shader; };
		Texture* get_map(String name);
		INT get_map_index(String name);
		bool exist_map(String name);

		void config(Material_config config);
		void set_shader(Shader* shader);
		//void create_map_category(String name);
		Relast::Texture* add_texture_2_MapCategory(String map_name, String file = "");
		void add_texture_2_MapCategory(String map_name, Texture* texture);

		void render_maps();
	};


	Shader* create_shader(String name, String vertex_shader, String fragment_shader);
	Shader* create_shader(String name, Shader_config shader_config);
	Material* create_material(Material_config config);
}

#endif // !__R_SHADER__