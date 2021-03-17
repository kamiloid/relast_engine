#include"../Relast_Engine.h"
//#include"Scene_Manager.h"

Relast::scene_manager::Node* Relast::scene_manager::create_empty_node(Relast::scene_manager::Node_config* config, Relast::scene_manager::Node* parent)
{
	Node* node = new Node();
	node->node_config(config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	return node;
}

Relast::scene_manager::Node2D* Relast::scene_manager::create_node2D(Relast::scene_manager::Node_config* config, Relast::scene_manager::Node* parent)
{
	Relast::scene_manager::Node2D* node = new Relast::scene_manager::Node2D();
	node->node_config(config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	return node;
}

Relast::scene_manager::Node3D* Relast::scene_manager::create_node3D(Relast::scene_manager::Node_config* config, Relast::scene_manager::Node* parent)
{
	Relast::scene_manager::Node3D* node = new Relast::scene_manager::Node3D();
	node->node_config(config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	return node;
}


Relast::scene_manager::Entity3D* Relast::scene_manager::create_entity3D(Relast::scene_manager::Node_config* config, Relast::scene_manager::Node* parent)
{
	Relast::scene_manager::Entity3D* node = new Relast::scene_manager::Entity3D();
	node->node_config(config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	return node;
}


Relast::scene_manager::Light* Relast::scene_manager::create_light(Node_config* config, Light_config* light_config, Node* parent)
{
	Relast::scene_manager::Light* node = new Relast::scene_manager::Light();
	node->node_config(config);
	node->light_config(light_config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	node->_ambient_color = light_config->_ambient_color;
	node->_diffuse_color = light_config->_diffuse_color;
	node->_specular_color = light_config->_specular_color;
	node->_ambient_intensity = light_config->_ambient_intensity;
	node->_diffuse_intensity = light_config->_diffuse_intensity;
	node->_specular_intensity = light_config->_specular_intensity;
	node->_specular_pow = light_config->_specular_pow;
	return node;
}


Relast::scene_manager::Camera* Relast::scene_manager::create_simple_camera(Node_config* config, Camera_config* camera_config, Relast::scene_manager::Node* parent)
{
	Relast::scene_manager::Camera* node = new Relast::scene_manager::Camera(camera_config);
	node->node_config(config);
	if (config->_ID != "")
		node->set_ID(config->_ID);
	if (config->_iID != -1)
		node->set_internal_ID(config->_iID);
	if (config->_name != "")
		node->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(node);
	return node;
}


Relast::scene_manager::Scene* Relast::scene_manager::create_scene(Relast::scene_manager::Scene_config* config)
{
	Scene* scene = new Scene();
	scene->_config = config;
	return scene;
}


Relast::scene_manager::Basic_Mesh* Relast::scene_manager::create_basic_mesh(Relast::scene_manager::Node_config* config, Relast::scene_manager::Node* parent)
{
	Relast::scene_manager::Basic_Mesh* mesh = new Relast::scene_manager::Basic_Mesh();
	mesh->node_config(config);
	mesh->mesh_config(new Relast::scene_manager::Basic_Mesh_config());
	if (config->_ID != "")
		mesh->set_ID(config->_ID);
	if (config->_iID != -1)
		mesh->set_internal_ID(config->_iID);
	if (config->_name != "")
		mesh->set_name(config->_name);
	if (parent != nullptr)
		parent->add_child(mesh);
	return mesh;
}