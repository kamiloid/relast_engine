#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Relast/Relast_Engine.h"
#include"addons/addons_headers.h"
#include"Input_gestures.h"
#include"../ImGizmo/ImGuizmo.h"


using namespace Relast;

namespace Relast_Editor
{
	class Editor
	{
	private:
		//Engine _engine;
		Engine *_engine;
	protected:
	public:
		Editor();
		~Editor();
		void init(Engine *engine, Engine_params params);
		void loop();
		void style_editor();
	};
};