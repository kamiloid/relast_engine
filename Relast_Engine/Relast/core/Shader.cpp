#include"../Relast_Engine.h"


//ALL STATICS INDEPENDENTS METHODS
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
std::vector<Relast::shader_structs_config::Shader_struct> Relast::Shader::read_structs(String shaderstr)
{
	std::vector<String> structs_split = string::split_range(shaderstr, "struct", "}");
	std::vector<shader_structs_config::Shader_struct> structs;
	for (String struct_ : structs_split)
	{
		String name = "";
		INT inext = 0;
		for (INT i = 7; i < struct_.size(); i++)
		{
			inext = i;
			if (struct_[i] == '{') break;
			if (struct_[i] == '\n' ||
				struct_[i] == '\t' ||
				struct_[i] == '\r') continue;
			name += struct_[i];
		}
		name = string::replace(name, " ", "");
		shader_structs_config::Shader_struct struct_config(name);
		String all_props = "";
		std::vector<String> props_list;
		for (INT i = inext + 1; i < struct_.size(); i++)
		{
			if (struct_[i] == '\n' ||
				struct_[i] == '\t' ||
				struct_[i] == '\r') continue;
			all_props += struct_[i];
			if (struct_[i] == ';')
			{
				props_list.push_back(all_props);
				all_props = "";
			}
		}
		for (String prop : props_list)
		{
			std::vector<String> prop_split = string::super_split(prop, " ");
			String pname = string::replace(prop_split[prop_split.size() - 1], ";", "");
			String ptype = prop_split[prop_split.size() - 2];
			struct_config.add_property(pname, ptype);
		}
		structs.push_back(struct_config);
	}

	return structs;
}
Relast::Shader_config Relast::Shader::split_strShader(String shaderstr)
{
	String vertex = "";
	String fragment = "";
	std::vector<String> split = string::str_split(shaderstr, "#shader ");
	std::vector<shader_structs_config::Shader_struct> structs = read_structs(shaderstr);
	std::vector<String> uniforms_split = string::split_range(shaderstr, "uniform", ";");

	std::vector<String> uniforms;
	std::vector<String> uniforms_types;

	for (String uni : uniforms_split)
	{
		std::vector<String> uni_split = string::super_split(uni, " ");
		String type = uni_split[uni_split.size() - 2];
		String name = uni_split[uni_split.size() - 1];
		bool exist_struct_as_uni = false;
		for (shader_structs_config::Shader_struct struct_ : structs)
		{
			if (struct_._name == type)
			{
				exist_struct_as_uni = true;
				for (shader_structs_config::Shader_struct_property prop : struct_._props)
				{
					uniforms.push_back(name + "." + (prop._name));
					uniforms_types.push_back(prop._type);
				}
				break;
			}
		}
		if (!exist_struct_as_uni)
		{
			uniforms.push_back(uni_split[uni_split.size() - 1]);
			uniforms_types.push_back(uni_split[uni_split.size() - 2]);
		}
	}

	split[0] = split[0].substr(1, split[0].length());
	split[1] = split[1].substr(1, split[1].length());

	Shader_config shader_config;
	shader_config.v = split[0];
	shader_config.f = split[1];
	shader_config._uniforms = uniforms;
	shader_config._uniforms_type = uniforms_types;

	return shader_config;
}


Relast::Shader* Relast::create_shader(String name, String vertex_shader, String fragment_shader)
{
	Shader* shader = new Shader(name, vertex_shader, fragment_shader);
	return shader;
}

Relast::Shader* Relast::create_shader(String name, Shader_config shader_config)
{
	Shader* shader = new Shader(name, shader_config.v, shader_config.f);
	shader->compile();
	shader->set_uniforms_list(shader_config._uniforms, shader_config._uniforms_type);
	return shader;
}

Relast::Material* Relast::create_material(Relast::Material_config config)
{
	Material* material = new Material();
	material->config(config);
	return material;
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------




//SHADER CLASS
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
Relast::Shader::Shader(String name, String vertex_shader, String fragment_shader)
{
	this->_name = name;
	this->_vcode = vertex_shader;
	this->_fcode = fragment_shader;
}

Relast::Shader::~Shader()
{
}

void Relast::Shader::create_program()
{
	this->_prog = glCreateProgram();
	glAttachShader(this->_prog, this->_vs);
	glAttachShader(this->_prog, this->_fs);
	glLinkProgram(this->_prog);
	glValidateProgram(this->_prog);
}

UINT Relast::Shader::check_program()
{
	GLint success;
	INT l;
	glGetProgramiv(this->_prog, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(this->_prog, GL_INFO_LOG_LENGTH, &l);
		//GLchar* info = (GLchar*)malloc(l * sizeof(GLchar));
		GLchar info[250];
		//glGetProgramInfoLog(this->_prog, l, &l, info);
		glGetProgramInfoLog(this->_prog, 250, NULL, info);
		std::cout << "ERROR Linking shaders: " << info << std::endl;
		return 0;
	}
	return 1;
}

UINT Relast::Shader::compile_shader(GLuint &shader, String source, Relast::enums::SHADER_TYPE type)
{
	shader = glCreateShader(type == Relast::enums::SHADER_TYPE::ST_VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	const char* code = source.c_str();
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	GLint success;
	INT l;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &l);
		GLchar* info = (GLchar*)malloc(l * sizeof(GLchar));
		glGetShaderInfoLog(shader, l, &l, info);
		std::cout << "ERROR compiling (" << this->_name << ") " << (type == Relast::enums::SHADER_TYPE::ST_VERTEX ? "vertex" : "fragment") << " shaders: " << info << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return 1;
}

UINT Relast::Shader::compile()
{
	UINT vresult = this->compile_shader(this->_vs, this->_vcode, enums::SHADER_TYPE::ST_VERTEX);
	UINT fresult = this->compile_shader(this->_fs, this->_fcode, enums::SHADER_TYPE::ST_FRAGMENT);
	if (vresult == 0 || fresult == 0) return 0;
	this->create_program();
	this->check_program();

	return 1;
}

void Relast::Shader::set_uniforms_list(std::vector<String> uniforms, std::vector<String> types)
{
	this->_uniforms_list = uniforms;
	this->_uniforms_types_list = types;

	UINT l = this->_uniforms_list.size();
	for (size_t i = 0; i < l; i++)
	{
		String uni = this->_uniforms_list[i];
		String type = this->_uniforms_types_list[i];
		enums::SHADER_UNIFORM_TYPE enum_type = enums::SHADER_UNIFORM_TYPE::FVEC4;
		if(type == _F_)
			enum_type = enums::SHADER_UNIFORM_TYPE::F1;
		else if (type == _I_ || type == _SAMPLER2D_)
			enum_type = enums::SHADER_UNIFORM_TYPE::I1;
		else if(type == _FVEC2_)
			enum_type = enums::SHADER_UNIFORM_TYPE::FVEC2;
		else if (type == _FVEC3_)
			enum_type = enums::SHADER_UNIFORM_TYPE::FVEC3;
		else if (type == _MAT4_)
			enum_type = enums::SHADER_UNIFORM_TYPE::M4;
		this->create_uniform(uni, enum_type);
	}
}

void Relast::Shader::use()
{
	glUseProgram(this->_prog);
}

Relast::Shader_uniform* Relast::Shader::create_uniform(String name, enums::SHADER_UNIFORM_TYPE type)
{
	Shader_uniform* uniform = new Shader_uniform();
	uniform->_name = name;
	uniform->_shader_name = this->_name;
	uniform->_type = type;
	uniform->_location = glGetUniformLocation(this->_prog, name.c_str());

	this->_uniforms[uniform->_shader_name + "_" + uniform->_name] = uniform;

	return uniform;
}
Relast::Shader_uniform* Relast::Shader::get_uniform(String name)
{
	std::map<String, Shader_uniform*>::iterator it;
	for (it = this->_uniforms.begin(); it != this->_uniforms.end(); it++)
		if (it->first == this->_name + "_" + name) return it->second;
	return nullptr;
}

void Relast::Shader::run_uniform_i1(String uniform_name, INT i)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniform1i(uniform->_location, i);
}
void Relast::Shader::run_uniform_f1(String uniform_name, FLOAT f)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniform1f(uniform->_location, f);
}
void Relast::Shader::run_uniform_f2(String uniform_name, FLOAT f1, FLOAT f2)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniform2f(uniform->_location, f1, f2);
}
void Relast::Shader::run_uniform_f3(String uniform_name, FLOAT f1, FLOAT f2, FLOAT f3)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniform3f(uniform->_location, f1, f2, f3);
}
void Relast::Shader::run_uniform_f4(String uniform_name, FLOAT f1, FLOAT f2, FLOAT f3, FLOAT f4)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniform4f(uniform->_location, f1, f2, f3, f4);
}
void Relast::Shader::run_uniform_m4(String uniform_name, glm::mat4 matrix)
{
	String uname = string::replace(uniform_name, this->_name + "_", "");
	Shader_uniform* uniform = this->_uniforms[this->_name + "_" + uname];
	glUniformMatrix4fv(uniform->_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

bool Relast::Shader::has_texture(String texture_key)
{
	return this->_textures.count(texture_key);
}
Relast::Texture* Relast::Shader::get_texture(String texture_key)
{
	if (!this->has_texture(texture_key)) return NULL;
	std::map<String, Texture*>::iterator it = this->_textures.find(texture_key);
	Texture* t = NULL;
	if (it != this->_textures.end())
		t = it->second;

	return t;
}
Relast::Texture* Relast::Shader::add_texture(Texture_config* _config)
{
	Texture* t = new Texture(_config);
	this->_textures[_config->_name] = t;
	return this->_textures[_config->_name];
}
Relast::Texture* Relast::Shader::add_texture(String name, String file)
{
	Texture_config* config = new Texture_config(name);
	config->_file = file;
	return this->add_texture(config);
}
void Relast::Shader::setup_texture(String texture_key)
{
	Texture* t = this->get_texture(texture_key);
	if (t == NULL)
	{
		std::cout << "Texture: " << texture_key << " does not exist in Shader: " << this->_name << std::endl;
		return;
	}
	
}
void Relast::Shader::texture(String texture_key)
{
	Texture* t = this->get_texture(texture_key);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,t->get_texId());
}

void Relast::Shader::setup_uniforms()
{

}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------





//MATERIAL CLASS
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void Relast::Material::config(Material_config config)
{
	this->_config = config;
	this->_name = string::replace(this->_config._name, " ", "_");
}
void Relast::Material::set_shader(Shader* shader)
{
	this->shader = shader;
}
Relast::Texture* Relast::Material::get_map(String name)
{
	std::map<String, Texture*>::iterator it;
	for (it = this->_maps.begin(); it != this->_maps.end(); it++)
	{
		if (it->first == name)
			return this->_maps[it->first];
	}
	return nullptr;
}
INT Relast::Material::get_map_index(String name)
{
	std::map<String, Texture*>::iterator it;
	INT index = 0;
	for (it = this->_maps.begin(); it != this->_maps.end(); it++)
	{
		if (it->first == name)
			return index;
		index++;
	}
	return -1;
}
bool Relast::Material::exist_map(String name)
{
	std::map<String, Texture*>::iterator it;
	for (it = this->_maps.begin(); it != this->_maps.end(); it++)
		if (it->first == name)
			return true;
	return false;
}
Relast::Texture* Relast::Material::add_texture_2_MapCategory(String map_name, String file)
{
	Texture_config* config = new Texture_config(map_name);
	config->_file = file;
	if (this->exist_map(map_name))
		this->_maps[map_name]->reconfig(config);
	else
		this->_maps[map_name] = new Texture(config);
	return this->_maps[map_name];
}
void Relast::Material::add_texture_2_MapCategory(String map_name, Texture* texture)
{
	this->_maps[map_name] = texture;
}

void Relast::Material::render_maps()
{
	std::map<String, Texture*>::iterator it;
	GLint t = GL_TEXTURE0;
	for (it = this->_maps.begin(); it != this->_maps.end(); it++)
	{
		Texture* texture = this->_maps[it->first];
		glActiveTexture(t);
		glBindTexture(GL_TEXTURE_2D, texture->get_texId());
		t++;
	}
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------