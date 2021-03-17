#include"../Relast_Engine.h"


//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************

void Relast::scene_manager::Node::node_config(Relast::scene_manager::Node_config* config)
{
	this->_config = config;
	this->_name = Relast::string::replace(this->_config->_name, " ", "_");
	this->_internal_id = Relast::number::random_i(0, 9999999);
	this->_id = Relast::string::get_uid();
	std::cout << "name: " << this->_name << " - ID: " << this->_id << " - internal ID: " << this->_internal_id << std::endl;
}
void Relast::scene_manager::Node::set_buffer_data(std::vector<FLOAT> vertices, std::vector<UINT> indices)
{
	this->_buffer_data->_vertices = vertices;
	this->_buffer_data->_indices = indices;
}
void Relast::scene_manager::Node::add_child(Relast::scene_manager::Node* child)
{
	Node* parent_aux = child->get_parent();
	if (parent_aux != nullptr)
	{
		if(this->get_parent() != nullptr)
			if (child->get_nodeID() == this->get_parent()->get_nodeID()) return;
		String id = child->get_nodeID();
		parent_aux->remove_child(id);
	}
	this->_childs.push_back(child);
	child->set_parent(this);
}
Relast::scene_manager::Node* Relast::scene_manager::Node::remove_child(String node_id)
{
	INT l = this->_childs.size();
	INT item_index = 0;
	Node* node = nullptr;
	for (size_t i = 0; i < l; i++)
	{
		item_index = i;
		node = this->_childs[i];
		if (node->get_nodeID() == node_id) break;
	}
	if(node != nullptr)
		this->_childs.erase(this->_childs.begin() + item_index);
	return node;
}
void Relast::scene_manager::Node::select_buffer_data()
{
	glBindVertexArray(this->_buffer_data->_BO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_buffer_data->_ABO);
	glBindBuffer(GL_BUFFER, this->_buffer_data->_VBO);
}
void Relast::scene_manager::Node::unselect_buffer_data()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Relast::scene_manager::Node* Relast::scene_manager::Node::get_child_by_name(String name)
{
	return this->get_child_by_name(name, this);
}
Relast::scene_manager::Node* Relast::scene_manager::Node::get_child_by_name(String name, Node* parent)
{
	if (parent == nullptr) return nullptr;
	INT cl = parent->_childs.size();
	for (INT i = 0; i < cl; i++)
	{
		Node* child = parent->_childs[i];
		if (child->_config->_name == name)
			return child;
		child->get_child_by_name(name, child);
	}
	return nullptr;
}
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************




//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
void Relast::scene_manager::Node2D::loop()
{
}

void Relast::scene_manager::Node2D::render()
{
}
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************







//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
void Relast::scene_manager::Node3D::loop()
{
	//this->apply_transform();

	Transform3D transform;
	if (Node3D* parent = dynamic_cast<Node3D*>(this->_parent))
		transform = parent->_transform;
	this->_transform.apply(transform, this->_parent->get_transform_type());
}

void Relast::scene_manager::Node3D::render()
{
}
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************








//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
Relast::Material* Relast::scene_manager::Entity3D::get_material(String name)
{
	for (Material* mat : this->_materials)
		if (mat->get_config()._name == name)
			return mat;
	return nullptr;
}
void Relast::scene_manager::Entity3D::add_material(Material* material)
{
	this->_materials.push_back(material);
}
void Relast::scene_manager::Entity3D::loop()
{
	Node3D::loop();
}

void Relast::scene_manager::Entity3D::render()
{
	Node3D::render();
	for (Material* mat : this->_materials)
	{
		mat->render_maps();
		Shader* shader = mat->get_shader();
		std::map<String, Texture*> textures = shader->get_textures();
		std::map<String, Texture*>::iterator it_texture;
		for (it_texture = textures.begin(); it_texture != textures.end(); it_texture++)
			shader->texture(it_texture->first);
		shader->use();
	}
}

void Relast::scene_manager::Entity3D::end_render()
{
	for (Material* mat : this->_materials)
	{
		Shader* shader = mat->get_shader();
		std::map<String, Shader_uniform*> uniforms = shader->get_uniforms();
		std::map<String, Shader_uniform*>::iterator it_uniforms;
		for (it_uniforms = uniforms.begin(); it_uniforms != uniforms.end(); it_uniforms++)
		{
			Shader_uniform* uniform = it_uniforms->second;
			
			if (uniform->_type == enums::SHADER_UNIFORM_TYPE::I1)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_1i* u1i = dynamic_cast<uniforms_config::Uniform_1i*>(uniform->_args);
				shader->run_uniform_i1(it_uniforms->first, u1i->_a1);
			}
			else if (uniform->_type == enums::SHADER_UNIFORM_TYPE::F1)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_1f* u1f = dynamic_cast<uniforms_config::Uniform_1f*>(uniform->_args);
				shader->run_uniform_f1(it_uniforms->first, u1f->_a1);
			}
			else if (uniform->_type == enums::SHADER_UNIFORM_TYPE::FVEC2)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_2f* u4f = dynamic_cast<uniforms_config::Uniform_2f*>(uniform->_args);
				shader->run_uniform_f2(it_uniforms->first, u4f->_a1, u4f->_a2);
			}
			else if (uniform->_type == enums::SHADER_UNIFORM_TYPE::FVEC3)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_3f* u4f = dynamic_cast<uniforms_config::Uniform_3f*>(uniform->_args);
				shader->run_uniform_f3(it_uniforms->first, u4f->_a1, u4f->_a2, u4f->_a3);
			}
			else if (uniform->_type == enums::SHADER_UNIFORM_TYPE::FVEC4)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_4f* u4f = dynamic_cast<uniforms_config::Uniform_4f*>(uniform->_args);
				shader->run_uniform_f4(it_uniforms->first, u4f->_a1, u4f->_a2, u4f->_a3, u4f->_a4);
			}
			else if (uniform->_type == enums::SHADER_UNIFORM_TYPE::M4)
			{
				if (uniform->_args == nullptr) continue;
				uniforms_config::Uniform_mat4* um4 = dynamic_cast<uniforms_config::Uniform_mat4*>(uniform->_args);
				shader->run_uniform_m4(it_uniforms->first, um4->_a1);
			}
		}
	}
}
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************