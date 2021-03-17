#include"Scene_Graph.h"


namespace addons
{
	namespace scene_manager
	{
		ImGuiTreeNodeFlags _tree_node_flags = ImGuiTreeNodeFlags_OpenOnArrow | 
			ImGuiTreeNodeFlags_OpenOnDoubleClick | 
			ImGuiTreeNodeFlags_SpanAvailWidth | 
			ImGuiTreeNodeFlags_SpanFullWidth;
		std::map<String, Tree_node*> _sm_buffer;
	}
}



void addons::scene_manager::init(Relast::scene_manager::Scene* scene)
{
	if (Main_Menu::_panel_scenegraph)
	{
		ImGui::Begin("Scene Manager", &Main_Menu::_panel_scenegraph, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize | 
			ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("New"))
			{
				std::vector<String> selected_treenodes = selected_node();
				if (selected_treenodes.size() == 1)
				{
					Tree_node* selected_treenode = _sm_buffer[selected_treenodes[0]];
					if (ImGui::MenuItem("Empty node"))
						new_empty_node(selected_treenode->_node);
					if (ImGui::MenuItem("New layer"))
						addons::Scene_Graph_Menu::_sm_new_layer = true;
					if (ImGui::MenuItem("New camera"))
						new_simple_camera(selected_treenode->_node);
					ImGui::Separator();
					if (ImGui::MenuItem("New spot light"))
						addons::Scene_Graph_Menu::_sm_new_spot_light = true;
					if (ImGui::MenuItem("New point light"))
						addons::Scene_Graph_Menu::_sm_new_point_light = true;
					if (ImGui::MenuItem("New ambient light"))
						addons::Scene_Graph_Menu::_sm_new_ambient_light = true;
					if (ImGui::MenuItem("New specular light"))
						addons::Scene_Graph_Menu::_sm_new_specular_light = true;
					if (ImGui::MenuItem("New diffuse light"))
						addons::Scene_Graph_Menu::_sm_new_diffuse_light = true;
				}
				else {
					ImGui::Text("Select only one node to add a sub-node, please!");
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		Relast::scene_manager::Node* root = scene->get_root();
		add_to_buffer(root);
		ImGuiTreeNodeFlags selected_flag = is_selected_node(scene->get_root()) ? ImGuiTreeNodeFlags_Selected : 0;
		bool root_selected = ImGui::TreeNodeEx((void*)(intptr_t)scene->get_root()->get_internalID(), _tree_node_flags | selected_flag, "Main World");
		
		show_submenu(scene->get_root());
		if (ImGui::IsItemClicked())
		{
			select_node(scene->get_root());
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_GRAPH_NODES"))
			{
				Tree_node* new_child_node = get_item_from_buffer_by_internal_id(*(const int*)payload->Data);
				scene->get_root()->add_child(new_child_node->_node);
				std::cout << "Node " << new_child_node->_node->get_name() << " - (" << new_child_node->_node->get_nodeID() << ") added into Root Node " << std::endl;
			}
			ImGui::EndDragDropTarget();
		}
		if (root_selected)
		{	
			addons::scene_manager::show_childs(scene->get_root());
			ImGui::TreePop();
		}
		ImGui::End();
	}
}


bool addons::scene_manager::buffer_has_node(String node_id)
{
	return _sm_buffer[node_id] != nullptr;
}
addons::scene_manager::Tree_node* addons::scene_manager::get_item_from_buffer(String node_id)
{
	if (buffer_has_node(node_id))
		return _sm_buffer[node_id];
	return nullptr;
}
addons::scene_manager::Tree_node* addons::scene_manager::get_item_from_buffer_by_internal_id(UINT id)
{
	std::map<String, Tree_node*>::iterator it;
	for (it = _sm_buffer.begin(); it != _sm_buffer.end(); it++)
	{
		Tree_node* node = _sm_buffer[it->first];
		if (node->_node->get_internalID() == id)
			return node;
	}
	return nullptr;
}
void addons::scene_manager::add_to_buffer(Relast::scene_manager::Node* node, bool overwrite)
{
	bool is_in_buffer = buffer_has_node(node->get_nodeID());
	if (!overwrite && is_in_buffer) return;
	addons::scene_manager::Tree_node* tree_node = new Tree_node(node);
	_sm_buffer[node->get_nodeID()] = tree_node;
}




bool addons::scene_manager::add_node_to_tree(Relast::scene_manager::Node* node)
{
	return ImGui::TreeNodeEx((const void*)node->get_internalID(), _tree_node_flags, node->get_name().c_str());
}

void addons::scene_manager::show_childs(Relast::scene_manager::Node* node)
{
	UINT cl = node->childs_count();
	for (size_t i = 0; i < cl; i++)
	{
		if (i >= node->childs_count()) break;

		Relast::scene_manager::Node* child = node->get_child(i);
		UINT iid = child->get_internalID();
		String name = child->get_name();
		add_to_buffer(child);
		ImGuiTreeNodeFlags selected_flag = is_selected_node(child) ? ImGuiTreeNodeFlags_Selected : 0;
		bool root_selected = ImGui::TreeNodeEx((void*)(intptr_t)iid, _tree_node_flags | selected_flag, name.c_str());
		show_submenu(child);
		if (ImGui::IsItemClicked())
			select_node(child);
		if (ImGui::BeginDragDropSource())
		{
			INT iid = (INT)child->get_internalID();
			ImGui::SetDragDropPayload("SCENE_GRAPH_NODES", (void*)(intptr_t)&iid, sizeof(INT));
			ImGui::Text(child->get_name().c_str());
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SCENE_GRAPH_NODES"))
			{
				Tree_node* new_child_node = get_item_from_buffer_by_internal_id(*(const int*)payload->Data);
				child->add_child(new_child_node->_node);
				//std::cout << *(const int*)payload->Data << " - " << child->get_internalID() << std::endl;
				std::cout << "Node " << new_child_node->_node->get_name() << " - (" << new_child_node->_node->get_nodeID() << ") added into Node " << child->get_name() << "(" << child->get_nodeID() << ")" << std::endl;
			}
			ImGui::EndDragDropTarget();
		}
		if (root_selected)
		{
			addons::scene_manager::show_childs(child);
			ImGui::TreePop();
		}
	}
}

void addons::scene_manager::show_submenu(Relast::scene_manager::Node* node)
{
	if (ImGui::BeginPopupContextItem((node->get_nodeID()).c_str()))
	{
		select_node(node);
		if (ImGui::Selectable("New empty node"))
			new_empty_node(node);
		if(ImGui::Selectable("New layer"))
			addons::Scene_Graph_Menu::_sm_new_layer = true;
		if (ImGui::Selectable("New camera"))
			new_simple_camera(node);
		ImGui::Separator();
		if(ImGui::Selectable("New spot light"))
			addons::Scene_Graph_Menu::_sm_new_spot_light = true;
		if(ImGui::Selectable("New point light"))
			addons::Scene_Graph_Menu::_sm_new_point_light = true;
		if(ImGui::Selectable("New ambient light"))
			addons::Scene_Graph_Menu::_sm_new_ambient_light = true;
		if(ImGui::Selectable("New specular light"))
			addons::Scene_Graph_Menu::_sm_new_specular_light = true;
		if(ImGui::Selectable("New diffuse light"))
			addons::Scene_Graph_Menu::_sm_new_diffuse_light = true;

		ImGui::EndPopup();
	}
}




void addons::scene_manager::select_node(Relast::scene_manager::Node* node)
{
	if (!buffer_has_node(node->get_nodeID())) return;
	if(!ImGui::GetIO().KeyCtrl)
		unselect_nodes(node);
	_sm_buffer[node->get_nodeID()]->_selected = true;
}
std::vector<String> addons::scene_manager::selected_node()
{
	std::vector<String> buffer;
	std::map<String, Tree_node*>::iterator it;
	for (it = _sm_buffer.begin(); it != _sm_buffer.end(); it++)
		if (_sm_buffer[it->first]->_selected) buffer.push_back(it->first);
	return buffer;
}
void addons::scene_manager::unselect_nodes(Relast::scene_manager::Node* except_node)
{
	std::map<String, Tree_node*>::iterator it;
	for (it = _sm_buffer.begin(); it != _sm_buffer.end(); it++)
	{
		if (it->first == except_node->get_nodeID()) continue;
		_sm_buffer[it->first]->_selected = false;
	}
}
bool addons::scene_manager::is_selected_node(Relast::scene_manager::Node* node)
{
	if (!buffer_has_node(node->get_nodeID())) return false;
	return _sm_buffer[node->get_nodeID()]->_selected;
}
void addons::scene_manager::remove_selected_node(Relast::scene_manager::Node* node)
{
	if (buffer_has_node(node->get_nodeID()))
	{
		std::map<String, scene_manager::Tree_node*>::iterator it = _sm_buffer.find(node->get_nodeID());
		if (it != _sm_buffer.end())
			_sm_buffer.erase(it);
	}
}
void addons::scene_manager::clear_selection()
{
	_sm_buffer.clear();
}




void addons::scene_manager::new_empty_node(Relast::scene_manager::Node* parent_node)
{
	addons::Scene_Graph_Menu::_sm_new_empty_node = true;
	Relast::scene_manager::Node_config* node_config = new Relast::scene_manager::Node_config();
	Relast::scene_manager::Node* new_node = Relast::scene_manager::create_empty_node(node_config, parent_node);
	show_childs(parent_node);
}
void addons::scene_manager::new_simple_camera(Relast::scene_manager::Node* parent_node)
{
	addons::Scene_Graph_Menu::_sm_new_camera = true;
	Relast::scene_manager::Node_config* node_config = new Relast::scene_manager::Node_config();
	Relast::scene_manager::Camera_config* cam_config = new Relast::scene_manager::Camera_config();
	node_config->_name = "New Camera";
	cam_config->_type = Relast::enums::PROJECTION_TYPE::PT_PERSPECTIVE;
	cam_config->_fov = 45.0f;
	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	cam_config->_ratio = (FLOAT)m_viewport[3] / (FLOAT)m_viewport[2];
	cam_config->_near = 1.0f;
	cam_config->_far = 100.0f;
	Relast::scene_manager::Camera* camera = Relast::scene_manager::create_simple_camera(node_config, cam_config, parent_node);
	show_childs(camera);
}