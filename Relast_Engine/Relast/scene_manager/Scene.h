#pragma once
#ifndef __R_SCENE__
#define __R_SCENE__


//#include"../core/Tools.h"
#include"Entities.h"


namespace Relast
{
	namespace scene_manager
	{
		class Scene
		{
		private:
			Node* _root;
			enums::TRANSFORM_TYPE _transform_type = enums::TRANSFORM_TYPE::TT_GLOBAL;

			void loop_treenode(Node* parent);
			void render_treenode(Node* parent);
		public:
			Scene();
			~Scene();

			Scene_config* _config;
			Node* get_root() { return this->_root; };

			void set_transform_type(enums::TRANSFORM_TYPE type) { this->_transform_type = type; };

			void config(Scene_config* config);
			void insert_node(Node* child, Node* parent=nullptr);
			void loop();
			void render();
		};
	}
}


#endif // !__R_SCENE__