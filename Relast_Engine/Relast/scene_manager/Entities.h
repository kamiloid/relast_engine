#pragma once
#ifndef __R_ENTITIES__
#define __R_ENTITIES__


#include<iostream>
#include<vector>
#include<map>

#include"../core/Transform.h"
#include"../core/Shader.h"


namespace Relast
{
	namespace scene_manager
	{
		class Node
		{
		private:
		protected:
			UINT _internal_id;
			String _id;
			String _name;
			Node_config* _config;
			Node* _parent;
			std::vector<Node*> _childs;
			Buffer_data* _buffer_data;

			enums::TRANSFORM_TYPE _transform_type = enums::TRANSFORM_TYPE::TT_GLOBAL;

			Node* get_child_by_name(String name, Node* parent);

		public:
			Node() 
			{
				this->_buffer_data = new Buffer_data();
			};
			virtual ~Node() {};
			UINT get_internalID() { return this->_internal_id; }
			String get_nodeID() { return this->_id; };
			String get_name() { return this->_name; };
			Buffer_data* get_buffer_data() { return this->_buffer_data; };
			enums::TRANSFORM_TYPE get_transform_type() { return this->_transform_type; };
			Node* get_parent() { return this->_parent; }
			UINT childs_count() { return this->_childs.size(); };
			Node* get_child(UINT index) { return this->_childs[index]; }
			Node* get_child_by_name(String name);


			void set_ID(String id = "")
			{
				this->_id = id;
			}
			void set_name(String name)
			{
				this->_name = string::replace(name, " ", "_");
			}
			void set_internal_ID(UINT id)
			{
				this->_internal_id = id;
			}
			void set_buffer_data(Buffer_data* data)
			{
				this->_buffer_data = data;
			};
			void set_transform_type(enums::TRANSFORM_TYPE type) { this->_transform_type = type; };

			void node_config(Node_config* _config);
			void add_child(Node* child);
			void set_parent(Node* parent) { this->_parent = parent; };
			Node* remove_child(String node_id);
			void set_buffer_data(std::vector<FLOAT> vertices, std::vector<UINT> indices);
			void select_buffer_data();
			void unselect_buffer_data();
		};
		
		class Node2D:public Node
		{
		protected:
			glm::vec2 _ipos;
			glm::vec2 _pos;
			FLOAT _irot;
			FLOAT _rot;
			glm::vec2 _iscale;
			glm::vec2 _scale;
		public:
			Node2D():Node() {};
			virtual ~Node2D() {};

			glm::vec2 get_initial_position() { return this->_ipos; };
			FLOAT get_initial_rotation() { return this->_irot; };
			glm::vec2 get_initial_scale() { return this->_iscale; };

			glm::vec2 get_position() { return this->_pos; };
			FLOAT get_rotation() { return this->_rot; };
			glm::vec2 get_scale() { return this->_scale; };

			void set_initial_position(glm::vec2 pos) { this->_ipos = pos; };
			void set_initial_rotation(FLOAT rotation) { this->_irot = rotation; };
			void set_initial_scale(glm::vec2 scale) { this->_iscale = scale; };

			void set_position(glm::vec2 pos) { this->_pos = pos; };
			void set_rotation(FLOAT rotation) { this->_rot = rotation; };
			void set_scale(glm::vec2 scale) { this->_scale = scale; };

			virtual void loop();
			virtual void render();
		};
		
		class Node3D :public Node
		{
		protected:
			glm::vec3 _ipos, _irot;
			glm::vec3 _iscale = glm::vec3(1.0f);

		public:
			Transform3D _transform;



			glm::vec3 _rot2;
			Node3D():Node() {};
			virtual ~Node3D() {};

			glm::vec3 get_initial_position() { return this->_ipos; };
			glm::vec3 get_initial_rotation() { return this->_irot; };
			glm::vec3 get_initial_scale() { return this->_iscale; };

			Transform3D get_transform() { return this->_transform; };

			virtual void loop();
			virtual void render();
		};

		class Entity3D :public Node3D
		{
		protected:
			std::vector<Material*> _materials;
			void end_render();
		public:
			Entity3D():Node3D() {};
			virtual ~Entity3D() {};

			Material* get_material(String name);

			void add_material(Material* material);

			virtual void loop();
			virtual void render();
		};


		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------------------------
	}
}

#endif // !__R_ENTITIES__