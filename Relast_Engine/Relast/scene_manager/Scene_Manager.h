#pragma once
#ifndef __R_SCENE_MANAGER__
#define __R_SCENE_MANAGER__


//#include "../core/Tools.h"
#include "../scene_manager/Entities.h"
#include "../scene_manager/Camera.h"
#include "../scene_manager/Scene.h"
#include "../scene_manager/Light.h"
#include "../scene_manager/Primitives.h"

namespace Relast
{
	namespace scene_manager
	{
		Node* create_empty_node(Node_config* config, Relast::scene_manager::Node* parent = nullptr);
		Node2D* create_node2D(Node_config* config, Relast::scene_manager::Node* parent = nullptr);
		Node3D* create_node3D(Node_config* config, Relast::scene_manager::Node* parent = nullptr);
		Entity3D* create_entity3D(Node_config* config, Relast::scene_manager::Node* parent = nullptr);
		Light* create_light(Node_config* config, Light_config* light_config, Node* parent = nullptr);
		Camera* create_simple_camera(Node_config* config, Camera_config* camera_config, Relast::scene_manager::Node* parent = nullptr);
		Basic_Mesh* create_basic_mesh(Node_config* config, Relast::scene_manager::Node* parent = nullptr);
		Scene* create_scene(Scene_config* config);
	}
}


#endif // !__R_SCENE_MANAGER__