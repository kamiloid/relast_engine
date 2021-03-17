//INCLUDE ALL SYSTEM DEPENDENCIES
#include<iostream>
#include<string>


#include"editor/Editor.h"

int main()
{
	Relast_Editor::Editor editor;
	Relast::Engine engine;

	//1600 x 900
	//1000 x 1000
	editor.init(&engine, Engine_params(1600, 900));

	return 0;
}