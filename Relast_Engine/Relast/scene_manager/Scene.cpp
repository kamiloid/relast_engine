#include"../Relast_Engine.h"

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------


Relast::scene_manager::Scene::Scene()
{
	if (this->_config == nullptr)
		this->_config = new Scene_config();
	this->_config->_bgcolor._r = 0.5f;
	this->_config->_bgcolor._g = 0.5f;
	this->_config->_bgcolor._b = 0.5f;

	Node_config* root_config = new Node_config();
	root_config->_name = "root";
	this->_root = Relast::scene_manager::create_empty_node(root_config);
}
Relast::scene_manager::Scene::~Scene()
{
}

void Relast::scene_manager::Scene::config(Scene_config* config)
{
	this->_config = config;
}

void Relast::scene_manager::Scene::insert_node(Relast::scene_manager::Node* child, Relast::scene_manager::Node* parent)
{
	Node* parent_ = parent;
	if (parent_ == nullptr)
		parent_ = this->_root;
	parent_->add_child(child);
}

void Relast::scene_manager::Scene::loop()
{
	if (this->_root == nullptr)
	{
		std::cout << "Scene: " << this->_config->_name << " does not have elements to update." << std::endl;
		return;
	}
	this->loop_treenode(this->_root);
}

void Relast::scene_manager::Scene::loop_treenode(Node* parent)
{
	parent->set_transform_type(this->_transform_type);
	UINT cl = parent->childs_count();
	if (cl <= 0)
	{
		//std::cout << "Node: " << parent->get_name() << " - ID: " << parent->get_nodeID() << " does not have elements to update." << std::endl;
		return;
	}
	for (UINT i = 0; i < cl; i++)
	{
		Node* child = parent->get_child(i);
		if (Node2D* node2d = dynamic_cast<Node2D*>(child))
			node2d->loop();
		else if (Node3D* node3d = dynamic_cast<Node3D*>(child))
			node3d->loop();
		/*if (Entity3D* entity3d = dynamic_cast<Entity3D*>(child))
			entity3d->loop();
		if (Basic_Mesh* basic_mesh = dynamic_cast<Basic_Mesh*>(child))
			basic_mesh->loop();
		if (Camera* camera = dynamic_cast<Camera*>(child))
			camera->loop();*/
		//HERE, TO ADD THE LEFT OBJECTS

		this->loop_treenode(child);
	}
}



void Relast::scene_manager::Scene::render()
{
	if (this->_root == nullptr)
	{
		std::cout << "Scene: " << this->_config->_name << " does not have elements to render." << std::endl;
		return;
	}
	this->render_treenode(this->_root);
}

void Relast::scene_manager::Scene::render_treenode(Node* parent)
{
	UINT cl = parent->childs_count();
	if (cl <= 0)
	{
		//std::cout << "Node: " << parent->get_name() << " - ID: " << parent->get_nodeID() << " does not have elements to render." << std::endl;
		return;
	}
	for (UINT i = 0; i < cl; i++)
	{
		Node* child = parent->get_child(i);
		if (Node2D* node2d = dynamic_cast<Node2D*>(child))
			node2d->render();
		if (Node3D* node3d = dynamic_cast<Node3D*>(child))
			node3d->render();
		if (Entity3D* entity3d = dynamic_cast<Entity3D*>(child))
			entity3d->render();
		if (Basic_Mesh* basic_mesh = dynamic_cast<Basic_Mesh*>(child))
			basic_mesh->render();
		//HERE, TO ADD THE LEFT OBJECTS

		this->render_treenode(child);
	}
}
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------