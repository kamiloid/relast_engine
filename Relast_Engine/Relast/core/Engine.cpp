#include"../Relast_Engine.h"

using namespace Relast;


void Engine::add_2_render(scene_manager::Node* node)
{
	Buffer_data* data = node->get_buffer_data();
	INT vl = data->_vertices.size();
	INT il = data->_indices.size();

	FLOAT* vertices = data->_vertices.data();
	UINT* indices = data->_indices.data();

	for (INT i = 0; i < vl; i++)
		vertices[i] = data->_vertices[i];

	for (INT i = 0; i < il; i++)
		indices[i] = data->_indices[i];

	//std::cout << vl << std::endl;

	glGenVertexArrays(1, &data->_BO);
	glBindVertexArray(data->_BO);

	glGenBuffers(1, &data->_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, data->_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(FLOAT) * vl, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &data->_ABO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->_ABO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT) * il, indices, GL_STATIC_DRAW);

	//------------------------------------------------------------
	//------------------------------------------------------------
	//------------------------------------------------------------
	UINT ll = data->_layouts.size();
	INT acum = 0;
	for (INT i = 0; i < ll; i++)
	{
		Vertex_Layout layout = data->_layouts[i];
		// std::cout << acum << " x " << sizeof(float) << " = " << acum * sizeof(float) << std::endl;
		glVertexAttribPointer(layout._layout, layout._count, GL_FLOAT, GL_FALSE, vl, (void*)(acum * sizeof(float)));
		glEnableVertexAttribArray(layout._layout);
		acum += layout._count;
	}
	//------------------------------------------------------------
	//------------------------------------------------------------
	//------------------------------------------------------------

	////std::cout << (0 * sizeof(float)) << " " << data->_num_coords << std::endl;
	//glVertexAttribPointer(data->_pos_layout, data->_num_coords, GL_FLOAT, GL_FALSE, vl, (void*)(0 * sizeof(float)));
	//glEnableVertexAttribArray(data->_pos_layout);

	////std::cout << (data->_num_coords * sizeof(float)) << " " << data->_num_colors << std::endl;
	//glVertexAttribPointer(data->_color_layout, data->_num_colors, GL_FLOAT, GL_FALSE, vl, (void*)(data->_num_coords * sizeof(float)));
	//glEnableVertexAttribArray(data->_color_layout);
	//
	////std::cout << ((data->_num_coords + data->_num_colors) * sizeof(float)) << " " << data->_num_texcoords << std::endl;
	//glVertexAttribPointer(data->_tex_layout, data->_num_texcoords, GL_FLOAT, GL_FALSE, vl, (void*)((data->_num_coords + data->_num_colors) * sizeof(float)));
	//glEnableVertexAttribArray(data->_tex_layout);
	//
	////std::cout << ((data->_num_coords + data->_num_colors + data->_num_texcoords) * sizeof(float)) << " " << data->_num_normals << std::endl;
	//glVertexAttribPointer(data->_norm_layout, data->_num_normals, GL_FLOAT, GL_FALSE, vl, (void*)(data->_num_coords + data->_num_colors + data->_num_texcoords) * sizeof(float));
	//glEnableVertexAttribArray(data->_norm_layout);

	//std::cout << data->_num_coords * sizeof(float) << std::endl;
	//std::cout << (data->_num_coords + data->_num_colors) * sizeof(float) << std::endl;
	//std::cout << (data->_num_coords + data->_num_colors + data->_num_texcoords) * sizeof(float) << std::endl;
}





Engine_params::Engine_params(S_UINT width, S_UINT height, String title)
{
	this->_w = width;
	this->_h = height;
	this->_win_title = title;
}


Engine::Engine()
{
	this->_color;
	this->_color._r = this->_color._g = this->_color._b = 0.5f;
}

Engine::~Engine()
{
}


GLFWwindow* Engine::get_window()
{
	return this->_window;
}


int Engine::init(Engine_params params)
{
	this->_params = params;
	std::cout << "Initializing Relast Engine" << std::endl;
	
	if (!glfwInit())
	{
		std::cout << "Error initializing GLFW!!" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->_window = glfwCreateWindow(this->_params._w, this->_params._h, this->_params._win_title.c_str(), NULL, NULL);
	if (!this->_window)
	{
		glfwTerminate();
		std::cout << "Error initializing OpenGL Window!!" << std::endl;
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(this->_window);

	GLenum glew_init = glewInit();
	if (glew_init != GLEW_OK)
	{
		std::cout << "Error initializing GLEW!!" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	//GLint m_viewport[4];
	//glGetIntegerv(GL_VIEWPORT, m_viewport);
	//this->_viewport_size._w = m_viewport[2];
	//this->_viewport_size._h = m_viewport[3];

	this->_viewport_size._w = this->_params._w;
	this->_viewport_size._h = this->_params._h;

	return 1;
}

void Engine::end()
{
	glfwTerminate();
}

bool Engine::run()
{
	return glfwWindowShouldClose(this->_window);
}

void Engine::clear()
{
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->_color._r, this->_color._g, this->_color._b, this->_color._a);
}

void Engine::swap()
{
	glfwSwapBuffers(this->_window);

	glfwPollEvents();
}

void Engine::loop()
{
	UINT l = this->_scenes.size();
	for (UINT i = 0; i < l; i++)
	{
		scene_manager::Scene* scene = this->_scenes[i];
		scene->set_transform_type(this->_trans_type);
		scene->loop();
	}
}

void Engine::render()
{
	UINT l = this->_scenes.size();
	for (UINT i = 0; i < l; i++)
	{
		scene_manager::Scene* scene = this->_scenes[i];
		scene->render();
	}
}



void Engine::add_scene(scene_manager::Scene_config* config)
{
	scene_manager::Scene* scene = scene_manager::create_scene(config);
	this->_scenes.push_back(scene);
}