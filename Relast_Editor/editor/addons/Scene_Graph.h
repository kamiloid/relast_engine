#pragma once
#ifndef __RE_SCENE_MANAGER__
#define __RE_SCENE_MANAGER__

#include<iostream>
#include<string>

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"Main_menu.h"
#include"Relast/scene_manager/Scene_Manager.h"
//#include"../../Relast/scene_manager/Entities.h"
//#include"../../Relast/scene_manager/Scene.h"

namespace addons
{
	namespace scene_manager
	{
		struct Tree_node
		{
			bool _selected = false;
			Relast::scene_manager::Node* _node;
			Tree_node(Relast::scene_manager::Node* node)
			{
				this->_node = node;
			}
		};

		void init(Relast::scene_manager::Scene* scene);
		bool add_node_to_tree(Relast::scene_manager::Node* node);
		void show_childs(Relast::scene_manager::Node* node);
		void show_submenu(Relast::scene_manager::Node* node);

		bool buffer_has_node(String node_id);
		Tree_node* get_item_from_buffer(String node_id);
		Tree_node* get_item_from_buffer_by_internal_id(UINT id);
		void add_to_buffer(Relast::scene_manager::Node* node, bool overwrite = false);

		void select_node(Relast::scene_manager::Node* node);
		std::vector<String> selected_node();
		void unselect_nodes(Relast::scene_manager::Node* except_node = nullptr);
		bool is_selected_node(Relast::scene_manager::Node* node);
		void remove_selected_node(Relast::scene_manager::Node* node);
		void clear_selection();


		void new_empty_node(Relast::scene_manager::Node* parent_node);
		void new_simple_camera(Relast::scene_manager::Node* parent_node);
	}
}

#endif // !__RE_SCENE_MANAGER__