#include"../Relast_Engine.h"

//GENERAL METHODS
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------




//BASIC MESH CLASS
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

void Relast::scene_manager::Basic_Mesh::poly_type(enums::POLY_TYPE type)
{
	this->_mesh_config->_poly_type = type;
}
void Relast::scene_manager::Basic_Mesh::vertex_pos(glm::fvec3 v1, glm::fvec3 v2, glm::fvec3 v3, glm::fvec3 v4)
{
	FLOAT min = std::min(this->_config->_viewport_size._w, this->_config->_viewport_size._h);
	FLOAT max = std::max(this->_config->_viewport_size._w, this->_config->_viewport_size._h);
	FLOAT aspect = min / max;
	glm::vec3 vaspec(aspect, 1.0f, 1.0f);
	if (this->_config->_viewport_size._h > this->_config->_viewport_size._w)
		vaspec = glm::vec3(1.0f, aspect, 1.0f);

	this->_mesh_config->_vpos.push_back(v1 * vaspec);
	this->_mesh_config->_vpos.push_back(v2 * vaspec);
	this->_mesh_config->_vpos.push_back(v3 * vaspec);
	this->_mesh_config->_vpos.push_back(v4 * vaspec);
}
void Relast::scene_manager::Basic_Mesh::vertex_color(Color* color)
{
	this->vertex_color(color, color, color, color);
}
void Relast::scene_manager::Basic_Mesh::vertex_color(Color* v1, Color* v2, Color* v3, Color* v4)
{
	this->_mesh_config->_vcolor.push_back(v1);
	this->_mesh_config->_vcolor.push_back(v2);
	this->_mesh_config->_vcolor.push_back(v3);
	this->_mesh_config->_vcolor.push_back(v4);
}
void Relast::scene_manager::Basic_Mesh::vertex_texture(Texture_coords* v1, Texture_coords* v2, Texture_coords* v3, Texture_coords* v4)
{
	this->_mesh_config->_vtexture.push_back(v1);
	this->_mesh_config->_vtexture.push_back(v2);
	this->_mesh_config->_vtexture.push_back(v3);
	this->_mesh_config->_vtexture.push_back(v4);
}
void Relast::scene_manager::Basic_Mesh::vertex_normal(glm::fvec3 v1, glm::fvec3 v2, glm::fvec3 v3, glm::fvec3 v4)
{
	this->_mesh_config->_vnormals.push_back(v1);
	this->_mesh_config->_vnormals.push_back(v2);
	this->_mesh_config->_vnormals.push_back(v3);
	this->_mesh_config->_vnormals.push_back(v4);
}

void Relast::scene_manager::Basic_Mesh::init()
{
	glm::vec3 v1(0.0f), v2(0.0f), norm(0.0f);

	//INDICES ORDER
	this->_indices.push_back(0);
	this->_indices.push_back(1);
	this->_indices.push_back(3);
	this->_indices.push_back(1);
	this->_indices.push_back(2);
	this->_indices.push_back(3);


	//VERTEX 0
	//POSITION COORDS
	this->_vertices.push_back(this->_mesh_config->_vpos[0].x);
	this->_vertices.push_back(this->_mesh_config->_vpos[0].y);
	this->_vertices.push_back(this->_mesh_config->_vpos[0].z);
	//COLOR
	if (this->_mesh_config->_vcolor.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vcolor[0]->_r);
		this->_vertices.push_back(this->_mesh_config->_vcolor[0]->_g);
		this->_vertices.push_back(this->_mesh_config->_vcolor[0]->_b);
		this->_vertices.push_back(this->_mesh_config->_vcolor[0]->_a);
	}
	//TEXTURE COORDS
	if (this->_mesh_config->_vtexture.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vtexture[0]->_s);
		this->_vertices.push_back(this->_mesh_config->_vtexture[0]->_t);
	}
	//NORMAL
	/*v1 = this->_mesh_config->_vpos[1] - this->_mesh_config->_vpos[0];
	v2 = this->_mesh_config->_vpos[3] - this->_mesh_config->_vpos[0];*/
	v1 = this->_mesh_config->_vpos[3] - this->_mesh_config->_vpos[0];
	v2 = this->_mesh_config->_vpos[1] - this->_mesh_config->_vpos[0];
	norm = glm::normalize(glm::cross(v1, v2));
	this->_vertices.push_back(norm.x);
	this->_vertices.push_back(norm.y);
	this->_vertices.push_back(norm.z);


	//VERTEX 1
	//POSITION COORDS
	this->_vertices.push_back(this->_mesh_config->_vpos[1].x);
	this->_vertices.push_back(this->_mesh_config->_vpos[1].y);
	this->_vertices.push_back(this->_mesh_config->_vpos[1].z);
	//COLOR
	if (this->_mesh_config->_vcolor.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vcolor[1]->_r);
		this->_vertices.push_back(this->_mesh_config->_vcolor[1]->_g);
		this->_vertices.push_back(this->_mesh_config->_vcolor[1]->_b);
		this->_vertices.push_back(this->_mesh_config->_vcolor[1]->_a);
	}
	//TEXTURE COORDS
	if (this->_mesh_config->_vtexture.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vtexture[1]->_s);
		this->_vertices.push_back(this->_mesh_config->_vtexture[1]->_t);
	}
	//NORMAL
	v1 = this->_mesh_config->_vpos[0] - this->_mesh_config->_vpos[1];
	v2 = this->_mesh_config->_vpos[2] - this->_mesh_config->_vpos[1];
	norm = glm::normalize(glm::cross(v1, v2));
	this->_vertices.push_back(norm.x);
	this->_vertices.push_back(norm.y);
	this->_vertices.push_back(norm.z);


	//VERTEX 2
	//POSITION COORDS
	this->_vertices.push_back(this->_mesh_config->_vpos[2].x);
	this->_vertices.push_back(this->_mesh_config->_vpos[2].y);
	this->_vertices.push_back(this->_mesh_config->_vpos[2].z);
	//COLOR
	if (this->_mesh_config->_vcolor.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vcolor[2]->_r);
		this->_vertices.push_back(this->_mesh_config->_vcolor[2]->_g);
		this->_vertices.push_back(this->_mesh_config->_vcolor[2]->_b);
		this->_vertices.push_back(this->_mesh_config->_vcolor[2]->_a);
	}
	//TEXTURE COORDS
	if (this->_mesh_config->_vtexture.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vtexture[2]->_s);
		this->_vertices.push_back(this->_mesh_config->_vtexture[2]->_t);
	}
	//NORMAL
	v1 = this->_mesh_config->_vpos[1] - this->_mesh_config->_vpos[2];
	v2 = this->_mesh_config->_vpos[3] - this->_mesh_config->_vpos[2];
	norm = glm::normalize(glm::cross(v1, v2));
	this->_vertices.push_back(norm.x);
	this->_vertices.push_back(norm.y);
	this->_vertices.push_back(norm.z);


	//VERTEX 3
	//POSITION COORDS
	this->_vertices.push_back(this->_mesh_config->_vpos[3].x);
	this->_vertices.push_back(this->_mesh_config->_vpos[3].y);
	this->_vertices.push_back(this->_mesh_config->_vpos[3].z);
	//COLOR
	if (this->_mesh_config->_vcolor.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vcolor[3]->_r);
		this->_vertices.push_back(this->_mesh_config->_vcolor[3]->_g);
		this->_vertices.push_back(this->_mesh_config->_vcolor[3]->_b);
		this->_vertices.push_back(this->_mesh_config->_vcolor[3]->_a);
	}
	//TEXTURE COORDS
	if (this->_mesh_config->_vtexture.size() > 0)
	{
		this->_vertices.push_back(this->_mesh_config->_vtexture[3]->_s);
		this->_vertices.push_back(this->_mesh_config->_vtexture[3]->_t);
	}
	//NORMAL
	v1 = this->_mesh_config->_vpos[2] - this->_mesh_config->_vpos[3];
	v2 = this->_mesh_config->_vpos[0] - this->_mesh_config->_vpos[3];
	norm = glm::normalize(glm::cross(v1, v2));
	this->_vertices.push_back(norm.x);
	this->_vertices.push_back(norm.y);
	this->_vertices.push_back(norm.z);


	this->set_buffer_data(this->_vertices, this->_indices);
	return;

}

void Relast::scene_manager::Basic_Mesh::loop()
{
	scene_manager::Entity3D::loop();
}

void Relast::scene_manager::Basic_Mesh::render()
{
	if (this->_buffer_data->_BO <= 0) return;

	Entity3D::render();

	GLenum element_type = GL_TRIANGLES;
	switch (this->_mesh_config->_poly_type)
	{
	case enums::POLY_TYPE::POINTS:
		element_type = GL_POINTS;
		break;
	case enums::POLY_TYPE::LINES:
		element_type = GL_LINES;
		break;
	case enums::POLY_TYPE::LINES_STRIP:
		element_type = GL_LINE_STRIP;
		break;
	case enums::POLY_TYPE::LOOP:
		element_type = GL_LINE_LOOP;
		break;
	case enums::POLY_TYPE::TRIANGLE_STRIP:
		element_type = GL_TRIANGLE_STRIP;
		break;
	}
	int indices_l = this->_indices.size();
	this->select_buffer_data();
	glDrawElements(element_type, indices_l, GL_UNSIGNED_INT, nullptr);
	this->select_buffer_data();

	this->end_render();
	//this->unselect_buffer_data();
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------