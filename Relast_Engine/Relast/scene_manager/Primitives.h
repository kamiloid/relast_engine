#pragma once
#ifndef __R_PRIMITIVES__
#define __R_PRIMITIVES__

#include<iostream>
#include<string>
#include<vector>
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//#include"../core/Tools.h"
//#include"../core/GLMat.h"
//#include"../core/Shader.h"


namespace Relast
{
	namespace scene_manager
	{
		class Basic_Mesh:public Entity3D
		{
		protected:
			Basic_Mesh_config* _mesh_config;

			std::vector<FLOAT> _vertices;
			std::vector<UINT> _indices;

			UINT _vbo;//vertex buffer object
			UINT _ibo;//index buffer object
		public:
			Basic_Mesh():Entity3D() {}
			~Basic_Mesh() {}


			void init();
			virtual void loop();
			virtual void render();

			std::vector<FLOAT> get_vertices() { return _vertices; };
			std::vector<UINT> get_indices() { return _indices; };
			UINT get_vbo() { return _vbo; };
			UINT get_ibo() { return _ibo; };
			void mesh_config(Basic_Mesh_config* config)
			{
				this->_mesh_config = config;
			};
			void poly_type(enums::POLY_TYPE type);
			void vertex_pos(glm::fvec3 v1, glm::fvec3 v2, glm::fvec3 v3, glm::fvec3 v4);
			void vertex_color(Color* color);
			void vertex_color(Color* v1, Color* v2, Color* v3, Color* v4);
			void vertex_texture(Texture_coords* v1, Texture_coords* v2, Texture_coords* v3, Texture_coords* v4);
			void vertex_normal(glm::fvec3 v1, glm::fvec3 v2, glm::fvec3 v3, glm::fvec3 v4);
		};


		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
	}
}


#endif // !__R_PRIMITIVES__