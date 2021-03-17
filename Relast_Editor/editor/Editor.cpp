#include"Editor.h"

using namespace Relast;
using namespace Relast_Editor;


Editor::Editor()
{
	std::cout << "Editor initialized" << std::endl;
}

Editor::~Editor()
{
}

void Editor::init(Relast::Engine *engine, Engine_params params)
{
	Relast::number::seed();

	this->_engine = engine;
	this->_engine->init(params);

	Relast::imgui::init();
	Relast::imgui::style_color(Relast::imgui::Style_color::LIGHT);
	this->style_editor();

	const char* glsl_version = Relast::imgui::glsl_version();
	Relast::imgui_glfw::init(this->_engine->get_window(), glsl_version);



	//TEMPORAL
	scene_manager::Scene_config* main_scene_config = new scene_manager::Scene_config();
	this->_engine->add_scene(main_scene_config);

	scene_manager::Node_config* camera_node_config = new scene_manager::Node_config();
	scene_manager::Camera_config* camera_config = new scene_manager::Camera_config();
	camera_node_config->_name = "Main camera";
	camera_config->_ratio = (FLOAT)this->_engine->get_viewport_size()._h / (FLOAT)this->_engine->get_viewport_size()._w;
	camera_config->_fov = 45.0f;
	camera_config->_near = 0.5f;
	camera_config->_far = 100.0f;
	//camera_config->_viewport_size = Rectf(0.0f, 0.0f, (FLOAT)this->_engine->get_viewport_size()._w, (FLOAT)this->_engine->get_viewport_size()._h);
	camera_config->_viewport_size = Rectf(-1.0f, -1.0f, 1.0f, 1.0f);
	camera_config->_camera_type = enums::CAMERA_TYPE::CT_EDITOR;
	scene_manager::Camera* cam = scene_manager::create_simple_camera(camera_node_config, camera_config, this->_engine->get_scene(0)->get_root());
	this->_engine->set_main_camera(cam);

	scene_manager::Node_config* light_node_config = new scene_manager::Node_config();
	scene_manager::Light_config* light_config = new scene_manager::Light_config();
	light_node_config->_name = "Main Light";
	scene_manager::Light* light = scene_manager::create_light(light_node_config, light_config, this->_engine->get_scene(0)->get_root());
	//

	ed_input::mouse::start_mouse_input(new ed_input::mouse::Mouse_config(this->_engine->get_window(), this->_engine));

	this->loop();

	Relast::imgui_glfw::shutdown();
	Relast::imgui::shutdown();

	this->_engine->end();
}


void Editor::loop()
{
	scene_manager::Scene* main_scene = this->_engine->get_scene(0);
	scene_manager::Node* root_node = main_scene->get_root();
	scene_manager::Camera* main_camera = this->_engine->get_main_camera();
	scene_manager::Light* main_light = dynamic_cast<scene_manager::Light*>(root_node->get_child_by_name("Main Light"));


	String mesh_shader_file = io::load_file_2_string("res/shaders/basic3.shader");
	Relast::Shader_config shaders = Shader::split_strShader(mesh_shader_file);


	scene_manager::Node_config* mesh1_config = new scene_manager::Node_config();
	mesh1_config->_viewport_size = this->_engine->get_viewport_size();
	mesh1_config->_name = "Mesh 1";
	scene_manager::Basic_Mesh* mesh1 = scene_manager::create_basic_mesh(mesh1_config, root_node);
	mesh1->get_buffer_data()->add_layout("i_pos", 3, 0);
	mesh1->get_buffer_data()->add_layout("i_color", 4, 1);
	mesh1->get_buffer_data()->add_layout("i_tex_coords", 2, 2);
	mesh1->get_buffer_data()->add_layout("i_normal", 3, 3);
	mesh1->vertex_pos(
		glm::fvec3(0.5f, 0.5f, 0), 
		glm::fvec3(0.5f, -0.5f, 0), 
		glm::fvec3(-0.5f, -0.5f, 0), 
		glm::fvec3(-0.5f, 0.5f, 0));
	mesh1->vertex_color(new Color(1, 1, 1, 1));
	mesh1->vertex_texture(
		new Texture_coords(1.0f, 1.0f, 0.0f),
		new Texture_coords(1.0f, 0.0f, 0.0f),
		new Texture_coords(0.0f, 0.0f, 0.0f),
		new Texture_coords(0.0f, 1.0f, 0.0f)
	);
	mesh1->vertex_normal(
		glm::fvec3(0.0f, 0.0f, -1.0f),
		glm::fvec3(0.0f, 0.0f, 1.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, -1.0f)
	);
	mesh1->init();
	//mesh1->get_buffer_data()->set_parameters(3, 4, 2, 3, 0, 1, 2, 3);
	Engine::add_2_render(mesh1);

	mesh1->select_buffer_data();
	Shader* shader1 = Relast::create_shader("basic_shader", shaders);

	Material_config material1_config;
	material1_config._name = "Material 1";
	Material* material1 = create_material(material1_config);
	material1->set_shader(shader1);
	mesh1->add_material(material1);







	scene_manager::Node_config* mesh2_config = new scene_manager::Node_config();
	mesh2_config->_viewport_size = this->_engine->get_viewport_size();
	mesh2_config->_name = "Mesh 2";
	scene_manager::Basic_Mesh* mesh2 = scene_manager::create_basic_mesh(mesh2_config, root_node);
	mesh2->get_buffer_data()->add_layout("i_pos", 3, 0);
	mesh2->get_buffer_data()->add_layout("i_color", 4, 1);
	mesh2->get_buffer_data()->add_layout("i_tex_coords", 2, 2);
	mesh2->get_buffer_data()->add_layout("i_normal", 3, 3);
	mesh2->vertex_pos(
		glm::fvec3(0.5f, 0.5f, 0),
		glm::fvec3(0.5f, -0.5f, 0),
		glm::fvec3(-0.5f, -0.5f, 0),
		glm::fvec3(-0.5f, 0.5f, 0));
	mesh2->vertex_color(new Color(1, 1, 1, 1));
	mesh2->vertex_texture(
		new Texture_coords(1.0f, 1.0f, 0.0f),
		new Texture_coords(1.0f, 0.0f, 0.0f),
		new Texture_coords(0.0f, 0.0f, 0.0f),
		new Texture_coords(0.0f, 1.0f, 0.0f)
	);
	mesh2->vertex_normal(
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f)
	);
	mesh2->init();
	//mesh2->get_buffer_data()->set_parameters(3, 4, 2, 3, 0, 1, 2, 3);
	Engine::add_2_render(mesh2);

	mesh2->select_buffer_data();
	Shader* shader2 = Relast::create_shader("basic_shader", shaders);

	Material_config material2_config;
	material2_config._name = "Material 1";
	Material* material2 = create_material(material2_config);
	material2->set_shader(shader2);
	mesh2->add_material(material2);







	scene_manager::Node_config* mesh3_config = new scene_manager::Node_config();
	mesh3_config->_viewport_size = this->_engine->get_viewport_size();
	mesh3_config->_name = "Mesh 3";
	scene_manager::Basic_Mesh* mesh3 = scene_manager::create_basic_mesh(mesh3_config, root_node);
	mesh3->get_buffer_data()->add_layout("i_pos", 3, 0);
	mesh3->get_buffer_data()->add_layout("i_color", 4, 1);
	mesh3->get_buffer_data()->add_layout("i_tex_coords", 0, 2);
	mesh3->get_buffer_data()->add_layout("i_normal", 3, 3);
	mesh3->vertex_pos(
		glm::fvec3(0.1f, 0.1f, 0),
		glm::fvec3(0.1f, -0.1f, 0),
		glm::fvec3(-0.1f, -0.1f, 0),
		glm::fvec3(-0.1f, 0.1f, 0));
	mesh3->vertex_color(new Color(1, 1, 1, 1));
	mesh3->vertex_normal(
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f),
		glm::fvec3(0.0f, 0.0f, 0.0f)
	);
	mesh3->init();
	//mesh3->get_buffer_data()->set_parameters(3, 4, 0, 3, 0, 1, 2, 3);
	Engine::add_2_render(mesh3);

	mesh3->select_buffer_data();
	Shader* shader3 = Relast::create_shader("basic_shader", shaders);

	Material_config material3_config;
	material3_config._name = "Material 1";
	Material* material3 = create_material(material3_config);
	material3->set_shader(shader3);
	mesh3->add_material(material3);

	main_camera->_temp_mesh = mesh3;







	//d148f7y-20b1d892-fd32-412b-936e-466623e7d091.jpg
	//d1nc576-47a1f6a4-689b-49aa-a4e1-26519482f4a9.jpg
	//d5negwl-5d2009f5-c00b-4095-93c8-177a5d6b4c53.jpg
	//d1c8ckg-e5409402-49d2-4759-8fe4-0649e44936d2.jpg

	shader1->use();
	Texture* albedo_m1s1 = material1->add_texture_2_MapCategory(_MAP_DIFFUSE_);
	albedo_m1s1->load("C:/Users/andre/OneDrive/Imágenes/wallpapers/d148f7y-20b1d892-fd32-412b-936e-466623e7d091.jpg");
	albedo_m1s1->setup();
	Texture* specular_m1s1 = material1->add_texture_2_MapCategory(_MAP_SPECULAR_);
	specular_m1s1->load("C:/Camilo/projects/C++/Relast_1/images_bank/d148f7y-20b1d892-fd32-412b-936e-466623e7d091.jpg");
	specular_m1s1->setup();


	shader2->use();
	Texture* albedo_m2s1 = material2->add_texture_2_MapCategory(_MAP_DIFFUSE_);
	albedo_m2s1->load("C:/Camilo/projects/C++/Relast_1/images_bank/elephant-walking-transparent-background.png");
	albedo_m2s1->setup();


	//main_camera->set_position(0.0f, 5.0f, 1.0f);
	main_camera->_transform._position = glm::vec3(0.0f, 0.0f, 3.0f);
	main_camera->set_target(0.0f, 0.0f, -8.0f);
	//main_light->_transform._position = glm::vec3(0.0f, 0.0f, 1.5f);
	main_light->_transform._position = glm::vec3(0.0f, 0.0f, 0.0f);
	mesh1->_transform._position = glm::vec3(-0.5f, 0.0f, 0.0f);
	mesh2->_transform._position = glm::vec3(0.5f, 0.0f, 0.0f);












	glm::vec2 i_mouse_pos = glm::vec2();
	glm::vec2 cam_angles = glm::vec2();
	glm::vec3 mouse_angles = glm::vec3();
	glm::vec3 new_cam_pos = main_camera->_transform._position;

	////-----
	bool show_demo_window = true;
	while (!this->_engine->run())
	{
		ImGui::GetStyle().WindowRounding = 6.0f;

		this->_engine->_color = main_scene->_config->_bgcolor;
		this->_engine->clear();

		Relast::imgui_glfw::loop();
		Relast::imgui::loop();
		//ImGui::ShowDemoWindow(&show_demo_window);

		Rectf viewport_size = this->_engine->get_viewport_size();
		addons::main_menu::init();
		addons::transform::init(viewport_size);
		addons::toolbox::init();
		addons::assets::init();
		addons::console::init();
		addons::scene::init_props(main_scene->_config, main_camera->_cam_config);
		addons::scene_manager::init(main_scene);

		this->_engine->set_transform_type(addons::transform::get_transform_type());
		enums::TRANSFORM_TYPE trans_type = this->_engine->get_transform_type();
		enums::TRANSFORM_OPERATION trans_operation = addons::transform::get_transform_operation();

		ed_input::mouse::loop_mouse();

		ed_input::mouse::mouse_gestures();
		ed_input::mouse::mouse_selection();






		this->_engine->loop();


		glm::mat4 mesh1_transform = mesh1->_transform.get_matrix();
		glm::mat4 mesh2_transform = mesh2->_transform.get_matrix();
		glm::mat4 main_light_trans = main_light->_transform.get_matrix();
		glm::mat4 cam_view = main_camera->get_view();
		glm::mat4 cam_proj = main_camera->get_projection();

		ImGuizmo::OPERATION guizmo_operation = ImGuizmo::OPERATION::TRANSLATE;
		if (trans_operation == enums::TRANSFORM_OPERATION::TO_ROTATE)
			guizmo_operation = ImGuizmo::OPERATION::ROTATE;
		else if (trans_operation == enums::TRANSFORM_OPERATION::TO_SCALE)
			guizmo_operation = ImGuizmo::OPERATION::SCALE;

		ImGuizmo::MODE guizmo_mode = trans_type == enums::TRANSFORM_TYPE::TT_GLOBAL ? ImGuizmo::MODE::WORLD : ImGuizmo::MODE::LOCAL;

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist(ImGui::GetForegroundDrawList());
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		ImGuizmo::Manipulate(glm::value_ptr(cam_view), glm::value_ptr(cam_proj), guizmo_operation, guizmo_mode, glm::value_ptr(mesh1_transform), NULL, NULL);
		ImGuizmo::Enable(true);

		if (ImGuizmo::IsUsing())
		{
			ed_input::mouse::stop_mouse();

			glm::vec3 trans = glm::vec3();
			glm::vec3 rot = glm::vec3();
			glm::vec3 scale = glm::vec3();
			ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(mesh1_transform), glm::value_ptr(trans), glm::value_ptr(rot), glm::value_ptr(scale));

			mesh1->_transform._position = trans;
			mesh1->_transform._rotation = rot;
			mesh1->_transform._scale = scale;
		}

		if (ImGui::Begin("Main light"))
		{
			static ImVec4 color = ImVec4(main_light->_ambient_color._r, main_light->_ambient_color._g, main_light->_ambient_color._b, 1.0f);
			FLOAT acI = main_light->_ambient_intensity;
			FLOAT dcI = main_light->_diffuse_intensity;
			FLOAT scI = main_light->_specular_intensity;
			FLOAT scP = main_light->_specular_pow;
			FLOAT lx = main_light->_transform._position.x;
			FLOAT ly = main_light->_transform._position.y;
			FLOAT lz = main_light->_transform._position.z;

			ImGui::ColorEdit3("Ambient Light", (float*)&color);
			ImGui::SliderFloat("Ambient Intensity (0 -> 1)", &acI, 0.0f, 1.0f, "%.3f");
			ImGui::Separator();
			ImGui::DragFloat("Diffuse Intensity", &dcI, 0.005f);
			ImGui::DragFloat("Light Dir X", &lx, 0.005f);
			ImGui::DragFloat("Light Dir Y", &ly, 0.005f);
			ImGui::DragFloat("Light Dir Z", &lz, 0.005f);
			ImGui::Separator();
			ImGui::SliderFloat("Specular Intensity (0 -> 1)", &scI, 0.0f, 1.0f, "%.3f");
			ImGui::SliderFloat("Specular Pow (0 -> 2)", &scP, 0.0f, 2.0f, "%.3f");

			main_light->_ambient_color = Color(color.x, color.y, color.z);
			main_light->_ambient_intensity = acI;
			main_light->_diffuse_intensity = dcI;
			main_light->_specular_intensity = scI;
			main_light->_specular_pow = scP;
			main_light->_transform._position = glm::vec3(lx, ly, lz);
			ImGui::End();
		}

		if (ImGui::Begin("camera_pos_test"))
		{
			float cam_x = main_camera->_transform._position.x;
			float cam_y = main_camera->_transform._position.y;
			float cam_z = main_camera->_transform._position.z;

			float target_x = main_camera->get_target().x;
			float target_y = main_camera->get_target().y;
			float target_z = main_camera->get_target().z;

			float cam_rx = main_camera->_transform._rotation.x;
			float cam_ry = main_camera->_transform._rotation.y;
			float cam_rz = main_camera->_transform._rotation.z;

			float zoom = main_camera->get_zoom();

			ImGui::DragFloat("cam pos x", &cam_x, 0.005f);
			ImGui::DragFloat("cam pos y", &cam_y, 0.005f);
			ImGui::DragFloat("cam pos z", &cam_z, 0.005f);

			ImGui::DragFloat("cam rot x", &cam_rx, 0.05f);
			ImGui::DragFloat("cam rot y", &cam_ry, 0.05f);
			ImGui::DragFloat("cam rot z", &cam_rz, 0.05f);

			ImGui::DragFloat("target pos x", &target_x, 0.005f);
			ImGui::DragFloat("target pos y", &target_y, 0.005f);
			ImGui::DragFloat("target pos z", &target_z, 0.005f);

			ImGui::DragFloat("cam zoom", &zoom, 0.005f);


			main_camera->_transform._position = glm::vec3(cam_x, cam_y, cam_z);
			main_camera->set_target(target_x, target_y, target_z);
			main_camera->set_zoom(zoom);
			main_camera->_transform._rotation = glm::vec3(cam_rx, cam_ry, cam_rz);

			ImGui::Text((std::to_string(cam_view[0].x) + " " + std::to_string(cam_view[1].x) + " " + std::to_string(cam_view[2].x) + " " + std::to_string(cam_view[3].x)).c_str());
			ImGui::Text((std::to_string(cam_view[0].y) + " " + std::to_string(cam_view[1].y) + " " + std::to_string(cam_view[2].y) + " " + std::to_string(cam_view[3].y)).c_str());
			ImGui::Text((std::to_string(cam_view[0].z) + " " + std::to_string(cam_view[1].z) + " " + std::to_string(cam_view[2].z) + " " + std::to_string(cam_view[3].z)).c_str());
			ImGui::Text((std::to_string(cam_view[0].w) + " " + std::to_string(cam_view[1].w) + " " + std::to_string(cam_view[2].w) + " " + std::to_string(cam_view[3].w)).c_str());

			ImGui::Separator();

			ImGui::Text((std::to_string(cam_proj[0].x) + " " + std::to_string(cam_proj[1].x) + " " + std::to_string(cam_proj[2].x) + " " + std::to_string(cam_proj[3].x)).c_str());
			ImGui::Text((std::to_string(cam_proj[0].y) + " " + std::to_string(cam_proj[1].y) + " " + std::to_string(cam_proj[2].y) + " " + std::to_string(cam_proj[3].y)).c_str());
			ImGui::Text((std::to_string(cam_proj[0].z) + " " + std::to_string(cam_proj[1].z) + " " + std::to_string(cam_proj[2].z) + " " + std::to_string(cam_proj[3].z)).c_str());
			ImGui::Text((std::to_string(cam_proj[0].w) + " " + std::to_string(cam_proj[1].w) + " " + std::to_string(cam_proj[2].w) + " " + std::to_string(cam_proj[3].w)).c_str());

			ImGui::Separator();

			float mesh1_px = mesh1->_transform._position.x;
			float mesh1_py = mesh1->_transform._position.y;
			float mesh1_pz = mesh1->_transform._position.z;

			float mesh1_rx = mesh1->_transform._rotation.x;
			float mesh1_ry = mesh1->_transform._rotation.y;
			float mesh1_rz = mesh1->_transform._rotation.z;

			ImGui::DragFloat("mesh_1 x", &mesh1_px, 0.005f);
			ImGui::DragFloat("mesh_1 y", &mesh1_py, 0.005f);
			ImGui::DragFloat("mesh_1 z", &mesh1_pz, 0.005f);

			ImGui::DragFloat("mesh_1 rx", &mesh1_rx, 0.005f);
			ImGui::DragFloat("mesh_1 ry", &mesh1_ry, 0.005f);
			ImGui::DragFloat("mesh_1 rz", &mesh1_rz, 0.005f);

			mesh1->_transform._position = glm::vec3(mesh1_px, mesh1_py, mesh1_pz);
			mesh1->_transform._rotation = glm::vec3(mesh1_rx, mesh1_ry, mesh1_rz);

			ImGui::Text((std::to_string(mesh1_transform[0].x) + " " + std::to_string(mesh1_transform[1].x) + " " + std::to_string(mesh1_transform[2].x) + " " + std::to_string(mesh1_transform[3].x)).c_str());
			ImGui::Text((std::to_string(mesh1_transform[0].y) + " " + std::to_string(mesh1_transform[1].y) + " " + std::to_string(mesh1_transform[2].y) + " " + std::to_string(mesh1_transform[3].y)).c_str());
			ImGui::Text((std::to_string(mesh1_transform[0].z) + " " + std::to_string(mesh1_transform[1].z) + " " + std::to_string(mesh1_transform[2].z) + " " + std::to_string(mesh1_transform[3].z)).c_str());
			ImGui::Text((std::to_string(mesh1_transform[0].w) + " " + std::to_string(mesh1_transform[1].w) + " " + std::to_string(mesh1_transform[2].w) + " " + std::to_string(mesh1_transform[3].w)).c_str());



			ImGui::Separator();

			float mesh2_px = mesh2->_transform._position.x;
			float mesh2_py = mesh2->_transform._position.y;
			float mesh2_pz = mesh2->_transform._position.z;

			ImGui::DragFloat("mesh_2 x", &mesh2_px, 0.005f);
			ImGui::DragFloat("mesh_2 y", &mesh2_py, 0.005f);
			ImGui::DragFloat("mesh_2 z", &mesh2_pz, 0.005f);

			mesh2->_transform._position = glm::vec3(mesh2_px, mesh2_py, mesh2_pz);

			ImGui::Text((std::to_string(mesh2_transform[0].x) + " " + std::to_string(mesh2_transform[1].x) + " " + std::to_string(mesh2_transform[2].x) + " " + std::to_string(mesh2_transform[3].x)).c_str());
			ImGui::Text((std::to_string(mesh2_transform[0].y) + " " + std::to_string(mesh2_transform[1].y) + " " + std::to_string(mesh2_transform[2].y) + " " + std::to_string(mesh2_transform[3].y)).c_str());
			ImGui::Text((std::to_string(mesh2_transform[0].z) + " " + std::to_string(mesh2_transform[1].z) + " " + std::to_string(mesh2_transform[2].z) + " " + std::to_string(mesh2_transform[3].z)).c_str());
			ImGui::Text((std::to_string(mesh2_transform[0].w) + " " + std::to_string(mesh2_transform[1].w) + " " + std::to_string(mesh2_transform[2].w) + " " + std::to_string(mesh2_transform[3].w)).c_str());
			
			
			

			
			
			
			ImGui::End();

			//mesh3->set_position(target_x, target_y, target_z);
		}

		mesh1_transform = mesh1->_transform.get_matrix();
		mesh2_transform = mesh2->_transform.get_matrix();
		cam_view = main_camera->get_view();
		cam_proj = main_camera->get_projection();


		shader1->get_uniform("u_color")->set_args(new uniforms_config::Uniform_4f(1.0f, 1.0f, 1.0f, 1.0f));
		shader1->get_uniform("u_model")->set_args(mesh1->_transform.transform_uniform());
		shader1->get_uniform("u_view")->set_args(new uniforms_config::Uniform_mat4(cam_view));
		shader1->get_uniform("u_projection")->set_args(new uniforms_config::Uniform_mat4(cam_proj));
		shader1->get_uniform("u_camera_pos")->set_args(main_camera->_transform.position_uniform());
		if (ImGui::Begin("Mesh 1 material"))
		{
			ImVec4 ambient_color = ImVec4(material1->_ambient_color._r, material1->_ambient_color._g, material1->_ambient_color._b, 1.0f);
			ImVec4 diffuse_color = ImVec4(material1->_diffuse_color._r, material1->_diffuse_color._g, material1->_diffuse_color._b, 1.0f);
			ImVec4 specular_color = ImVec4(material1->_specular_color._r, material1->_specular_color._g, material1->_specular_color._b, 1.0f);
			FLOAT shininess = material1->_shininess;
			ImGui::ColorEdit3("Ambient Color", (float*)&ambient_color);
			ImGui::ColorEdit3("Diffuse Color", (float*)&diffuse_color);
			ImGui::ColorEdit3("Specular Color", (float*)&specular_color);
			ImGui::SliderFloat("Shininess Pow (0 -> 2)", &shininess, 0.0f, 2.0f, "%.3f");
			mesh1->get_material("Material 1")->_ambient_color = Color(ambient_color.x, ambient_color.y, ambient_color.z);
			mesh1->get_material("Material 1")->_diffuse_color = Color(diffuse_color.x, diffuse_color.y, diffuse_color.z);
			mesh1->get_material("Material 1")->_specular_color = Color(specular_color.x, specular_color.y, specular_color.z);
			mesh1->get_material("Material 1")->_shininess = shininess;
			ImGui::End();
		}
		shader1->get_uniform("u_material1.diffuse_map")->set_args(material1->diffuse_map_uniform(material1->get_map_index(_MAP_DIFFUSE_)));
		shader1->get_uniform("u_material1.specular_map")->set_args(material1->specular_map_uniform(material1->get_map_index(_MAP_SPECULAR_)));
		shader1->get_uniform("u_material1.ambient_col")->set_args(material1->ambient_color_uniform());
		shader1->get_uniform("u_material1.diffuse_col")->set_args(material1->diffuse_color_uniform());
		shader1->get_uniform("u_material1.specular_col")->set_args(material1->specular_color_uniform());
		shader1->get_uniform("u_material1.shininess")->set_args(material1->shininess_uniform());
		shader1->get_uniform("u_light1.ambient_col")->set_args(main_light->ambient_color_uniform());
		shader1->get_uniform("u_light1.diffuse_col")->set_args(main_light->diffuse_color_uniform());
		shader1->get_uniform("u_light1.specular_col")->set_args(main_light->specular_color_uniform());
		shader1->get_uniform("u_light1.position")->set_args(main_light->_transform.position_uniform());
		shader1->get_uniform("u_light1.ambient_level")->set_args(main_light->ambient_level_uniform());
		shader1->get_uniform("u_light1.diffuse_level")->set_args(main_light->diffuse_level_uniform());
		shader1->get_uniform("u_light1.specular_level")->set_args(main_light->specular_level_uniform());

		shader2->get_uniform("u_color")->set_args(new uniforms_config::Uniform_4f(1.0f, 1.0f, 1.0f, 1.0f));
		shader2->get_uniform("u_model")->set_args(mesh2->_transform.transform_uniform());
		shader2->get_uniform("u_view")->set_args(new uniforms_config::Uniform_mat4(cam_view));
		shader2->get_uniform("u_projection")->set_args(new uniforms_config::Uniform_mat4(cam_proj));
		shader2->get_uniform("u_camera_pos")->set_args(main_camera->_transform.position_uniform());
		Material* mesh2_material = mesh2->get_material("Material 1");
		shader2->get_uniform("u_material1.diffuse_map")->set_args(material2->diffuse_map_uniform(material2->get_map_index(_MAP_DIFFUSE_)));
		shader2->get_uniform("u_material1.ambient_col")->set_args(mesh2_material->ambient_color_uniform());
		shader2->get_uniform("u_material1.diffuse_col")->set_args(mesh2_material->diffuse_color_uniform());
		shader2->get_uniform("u_material1.specular_col")->set_args(mesh2_material->specular_color_uniform());
		shader2->get_uniform("u_material1.shininess")->set_args(mesh2_material->shininess_uniform());
		shader2->get_uniform("u_light1.ambient_col")->set_args(main_light->ambient_color_uniform());
		shader2->get_uniform("u_light1.diffuse_col")->set_args(main_light->diffuse_color_uniform());
		shader2->get_uniform("u_light1.specular_col")->set_args(main_light->specular_color_uniform());
		shader2->get_uniform("u_light1.position")->set_args(main_light->_transform.position_uniform());
		shader2->get_uniform("u_light1.ambient_level")->set_args(main_light->ambient_level_uniform());
		shader2->get_uniform("u_light1.diffuse_level")->set_args(main_light->diffuse_level_uniform());
		shader2->get_uniform("u_light1.specular_level")->set_args(main_light->specular_level_uniform());

		mesh3->_transform._scale = glm::vec3(10.0f, 1.0f, 1.0f);
		glm::mat4 mesh3_transform = mesh3->_transform.get_matrix();
		shader3->get_uniform("u_color")->set_args(new uniforms_config::Uniform_4f(1.0f, 0.0f, 0.0f, 1.0f));
		shader3->get_uniform("u_model")->set_args(mesh3->_transform.transform_uniform());
		shader3->get_uniform("u_view")->set_args(new uniforms_config::Uniform_mat4(cam_view));
		shader3->get_uniform("u_projection")->set_args(new uniforms_config::Uniform_mat4(cam_proj));
		shader3->get_uniform("u_camera_pos")->set_args(main_camera->_transform.position_uniform());
		Material* mesh3_material = mesh3->get_material("Material 1");
		shader3->get_uniform("u_material1.ambient_col")->set_args(mesh3_material->ambient_color_uniform());
		shader3->get_uniform("u_material1.diffuse_col")->set_args(mesh3_material->diffuse_color_uniform());
		shader3->get_uniform("u_material1.specular_col")->set_args(mesh3_material->specular_color_uniform());
		shader3->get_uniform("u_material1.shininess")->set_args(mesh3_material->shininess_uniform());
		shader3->get_uniform("u_light1.ambient_col")->set_args(main_light->ambient_color_uniform());
		shader3->get_uniform("u_light1.diffuse_col")->set_args(main_light->diffuse_color_uniform());
		shader3->get_uniform("u_light1.specular_col")->set_args(main_light->specular_color_uniform());
		shader3->get_uniform("u_light1.position")->set_args(main_light->_transform.position_uniform());
		shader3->get_uniform("u_light1.ambient_level")->set_args(main_light->ambient_level_uniform());
		shader3->get_uniform("u_light1.diffuse_level")->set_args(main_light->diffuse_level_uniform());
		shader3->get_uniform("u_light1.specular_level")->set_args(main_light->specular_level_uniform());

		this->_engine->render();
		
		Relast::imgui::render();

		this->_engine->swap();
	}
}



void Relast_Editor::Editor::style_editor()
{
	ImGuiIO& io = ImGui::GetIO();
	//ImFont* pFont = io.Fonts->AddFontFromFileTTF("res/fonts/droid-sans/DroidSans.ttf", 14.0f);
	ImFont* pFont = io.Fonts->AddFontFromFileTTF("res/fonts/Roboto/Roboto-Medium.ttf", 14.0f);

	ImVec2* framepadding = &ImGui::GetStyle().FramePadding;
	framepadding->y = 9;

	ImGui::GetStyle().ScrollbarSize = 10;

	ImGui::GetStyle().FrameRounding = 4;
	ImGui::GetStyle().TabRounding = 4;
	ImGui::GetStyle().GrabRounding = 12;

	ImGui::GetStyle().WindowTitleAlign.x = 0.5f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.34f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.97f, 0.97f, 0.97f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
	colors[ImGuiCol_Border] = ImVec4(0.91f, 0.90f, 0.90f, 0.99f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.71f, 0.83f, 0.38f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.56f, 0.65f, 0.61f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.58f, 0.67f, 0.57f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.71f, 0.83f, 0.88f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.49f, 0.57f, 0.83f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.58f, 0.67f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.58f, 0.67f, 0.39f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.58f, 0.67f, 0.89f);
	colors[ImGuiCol_Button] = ImVec4(0.00f, 0.58f, 0.67f, 0.57f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 0.75f, 0.87f, 0.75f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.01f, 0.48f, 0.55f, 0.84f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.63f, 0.68f, 0.62f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.78f, 0.83f, 0.75f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.47f, 0.50f, 0.62f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.24f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 0.17f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.67f, 0.81f, 0.81f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.74f, 0.90f, 0.91f, 0.93f);
	colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.81f, 0.84f, 0.93f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);






}