#pragma once
#ifndef __R_TOOLS__
#define __R_TOOLS__

#include<iostream>
#include<array>
#include<vector>
#include<string>
//#include"GL/glew.h"
//#include"GLFW/glfw3.h"
#include"GL/glew.h"
#include"GLFW/glfw3.h"

#include"DataType.h"
#include"GLMat.h"
#include"Math_helper.h"

namespace Relast
{
	namespace enums
	{
		enum POLY_TYPE
		{
			POINTS, LINES, LINES_STRIP, LOOP, TRIANGLE, TRIANGLE_STRIP
		};
		enum SHADER_UNIFORM_TYPE
		{
			I1, F1, FVEC2, FVEC3, FVEC4, M4
		};
		enum SHADER_TYPE { ST_VERTEX, ST_FRAGMENT };
		enum PROJECTION_TYPE { PT_PERSPECTIVE, PT_ORTHO };
		enum CAMERA_TYPE { CT_SIMPLE, CT_EDITOR, CT_FPS };
		enum TRANSFORM_TYPE { TT_LOCAL, TT_GLOBAL };
		enum TRANSFORM_OPERATION { TO_TRANSLATE, TO_ROTATE, TO_SCALE };
		enum IMAGE_FORMAT { IF_JPG, IF_PNG };
		enum LIGHT_TYPE { LT_DIRECTIONAL, LT_POINT, LT_SPOT };
	}
	namespace number
	{
		void seed();
		INT random_i(INT min, INT max);
	}
	namespace string
	{
		bool match_str(String txt, String match);
		std::vector<String> str_split(String str, String delimiter);
		std::vector<String> super_split(String str, String delimiter);
		std::vector<String> split_range(String str, String init_delimiter, String finish_delimiter);
		String replace(String text, String match_text, String new_text);
		UINT char_lenght(char* c);
		char* string_2_array(String text);
		String array_2_string(char* array_);
		String get_uid(UINT length = 20);
	}
	struct Color
	{
		FLOAT _r, _g, _b = 0.5f;
		FLOAT _a = 1.0f;
		Color(FLOAT r = 1.0f, FLOAT g = 1.0f, FLOAT b = 1.0f, FLOAT a = 1.0f)
		{
			this->set_color(r, g, b, a);
		}
		void set_color(FLOAT r = 1.0f, FLOAT g = 1.0f, FLOAT b = 1.0f, FLOAT a = 1.0f) 
		{
			this->_r = r;
			this->_g = g;
			this->_b = b;
			this->_a = a;
		};
	};
	struct Texture_coords
	{
		FLOAT _s, _t, _r = 0.0f;
		Texture_coords(FLOAT s, FLOAT t, FLOAT r)
		{
			this->_s = s;
			this->_t = t;
			this->_r = r;
		}
	};
	struct Recti
	{
		UINT _w, _h, _x, _y, _top, _left, _right, _bottom;
		Recti() {};
		Recti(UINT x, UINT y, UINT w, UINT h)
		{
			this->_x = x;
			this->_y = y;
			this->_w = w;
			this->_h = h;
			this->_left = this->_x;
			this->_right = this->_x + this->_w;
			this->_top = this->_y;
			this->_bottom = this->_y + this->_h;
		};
	};
	struct Rectf
	{
		FLOAT _w, _h, _x, _y, _top, _left, _right, _bottom;
		Rectf() {};
		Rectf(FLOAT x, FLOAT y, FLOAT w, FLOAT h)
		{
			this->_x = x;
			this->_y = y;
			this->_w = w;
			this->_h = h;
			this->_left = this->_x;
			this->_right = this->_x + this->_w;
			this->_top = this->_y;
			this->_bottom = this->_y + this->_h;
		}
	};
	struct Vertex_Layout
	{
		String _name;
		UINT _count;
		UINT _layout;
		Vertex_Layout(String name, UINT count, UINT layout)
		{
			this->_name = name;
			this->_count = count;
			this->_layout = layout;
		}
	};
	struct Buffer_data
	{
		UINT _num_coords;
		UINT _num_colors;
		UINT _num_texcoords;
		UINT _num_normals;
		UINT _VBO;
		UINT _ABO;
		UINT _BO;
		UINT _pos_layout;
		UINT _color_layout;
		UINT _tex_layout;
		UINT _norm_layout;
		std::vector<FLOAT> _vertices;
		std::vector<UINT> _indices;
		std::vector<Vertex_Layout> _layouts;
		Buffer_data(UINT num_coords = 3, UINT num_color_coords = 4, UINT num_texture_coords = 3, UINT num_normal_coords = 3, UINT position_layout = 0, UINT color_layout = 1, UINT texture_layout = 2, UINT normal_layout = 3)
		{
			this->set_parameters(num_coords, num_color_coords, num_texture_coords, num_normal_coords, position_layout, color_layout, texture_layout, normal_layout);
		};
		void set_parameters(UINT num_coords = 3, UINT num_color_coords = 4, UINT num_texture_coords = 3, UINT num_normal_coords = 3, UINT position_layout = 0, UINT color_layout = 1, UINT texture_layout = 2, UINT normal_layout = 3)
		{
			this->_num_coords = num_coords;
			this->_num_colors = num_color_coords;
			this->_num_texcoords = num_texture_coords;
			this->_num_normals = num_normal_coords;
			this->_pos_layout = position_layout;
			this->_color_layout = color_layout;
			this->_tex_layout = texture_layout;
			this->_norm_layout = normal_layout;
		}
		void add_layout(String name, UINT count, UINT layout) { this->_layouts.push_back(Vertex_Layout(name, count, layout)); };
		void save_data(std::vector<FLOAT> vertices, std::vector<UINT> indices);
	};
	struct Shader_config
	{
		String v;
		String f;
		std::vector<String> _uniforms;
		std::vector<String> _uniforms_type;
	};
	namespace shader_structs_config
	{
		struct Shader_struct_property
		{
			String _name;
			String _type;

			Shader_struct_property(String name, String type)
			{
				this->_name = name;
				this->_type = type;
			}
		};
		struct Shader_struct
		{
			String _name;
			std::vector<Shader_struct_property> _props;

			Shader_struct(String name)
			{
				this->_name = name;
			};
			void add_property(String name, String type)
			{
				this->_props.push_back(Shader_struct_property(name, type));
			}
		};
	};
	namespace uniforms_config
	{
		struct Uniform
		{
			String _name;
			String _shader_name;
			virtual ~Uniform() {};
		};
		struct Uniform_1i : public Uniform
		{
			INT _a1;
			Uniform_1i(INT arg1)
			{
				this->_a1 = arg1;
			}
		};
		struct Uniform_1f : public Uniform
		{
			FLOAT _a1;
			Uniform_1f(FLOAT arg1)
			{
				this->_a1 = arg1;
			}
		};
		struct Uniform_2f : public Uniform
		{
			FLOAT _a1, _a2;
			Uniform_2f(FLOAT arg1, FLOAT arg2)
			{
				this->_a1 = arg1;
				this->_a2 = arg2;
			}
		};
		struct Uniform_3f : public Uniform
		{
			FLOAT _a1, _a2, _a3;
			Uniform_3f(FLOAT arg1, FLOAT arg2, FLOAT arg3)
			{
				this->_a1 = arg1;
				this->_a2 = arg2;
				this->_a3 = arg3;
			}
		};
		struct Uniform_4f: public Uniform
		{
			FLOAT _a1, _a2, _a3, _a4;
			Uniform_4f(FLOAT arg1, FLOAT arg2, FLOAT arg3, FLOAT arg4)
			{
				this->_a1 = arg1;
				this->_a2 = arg2;
				this->_a3 = arg3;
				this->_a4 = arg4;
			}
		};
		struct Uniform_mat3 : public Uniform
		{
			glm::mat3 _a1;
			Uniform_mat3(glm::mat3 arg1)
			{
				this->_a1 = arg1;
			}
		};
		struct Uniform_mat4 : public Uniform
		{
			glm::mat4 _a1;
			Uniform_mat4(glm::mat4 arg1)
			{
				this->_a1 = arg1;
			}
		};
	};
	struct Shader_uniform
	{
		String _name;
		String _shader_name;
		GLint _location;
		enums::SHADER_UNIFORM_TYPE _type;
		uniforms_config::Uniform* _args;

		void set_args(uniforms_config::Uniform* uniform_args) { this->_args = uniform_args; };
	};
	struct Material_config
	{
		String _name;
	};
	struct Texture_config
	{
		String _name;
		String _file;
		enums::IMAGE_FORMAT _format = enums::IMAGE_FORMAT::IF_JPG;
		Texture_config() {};
		Texture_config(String name)
		{
			this->_name = name;
		};
		void analize_format()
		{
			bool is_png = Relast::string::match_str(this->_file, ".png");
			is_png = !is_png ? Relast::string::match_str(this->_file, ".PNG") : is_png;
			is_png = !is_png ? Relast::string::match_str(this->_file, ".PENG") : is_png;
			is_png = !is_png ? Relast::string::match_str(this->_file, ".peng") : is_png;

			this->_format = is_png ? enums::IMAGE_FORMAT::IF_PNG : enums::IMAGE_FORMAT::IF_JPG;
		};
	};
	namespace scene_manager
	{
		struct Node_config
		{
			String _name = "New Node";
			String _ID = "";
			UINT _iID = -1;
			Rectf _viewport_size;
		};
		struct Scene_config
		{
			String _name = "New Scene";
			Color _bgcolor;
		};
		struct Basic_Mesh_config
		{
			UINT _bo;
			UINT _vbo;
			UINT _ibo;
			enums::POLY_TYPE _poly_type = enums::POLY_TYPE::TRIANGLE;
			std::vector<glm::fvec3> _vpos;
			std::vector<Color*> _vcolor;
			std::vector<Texture_coords*> _vtexture;
			std::vector<glm::fvec3> _vnormals;
		};
		struct Camera_config
		{
			enums::PROJECTION_TYPE _type = enums::PROJECTION_TYPE::PT_PERSPECTIVE;
			enums::CAMERA_TYPE _camera_type = enums::CAMERA_TYPE::CT_SIMPLE;
			Rectf _viewport_size;
			FLOAT _fov, _ratio, _near, _far;
		};
		struct Light_config
		{
			enums::LIGHT_TYPE _type = enums::LIGHT_TYPE::LT_DIRECTIONAL;
			Color _ambient_color = Color();
			Color _diffuse_color = Color();
			Color _specular_color = Color();

			FLOAT _ambient_intensity = 1.0f;
			FLOAT _diffuse_intensity = 1.0f;
			FLOAT _specular_intensity = 1.0f;
			FLOAT _specular_pow = 32.0f;

			Light_config() {};
		};
	}
}


#endif // !__R_TOOLS__