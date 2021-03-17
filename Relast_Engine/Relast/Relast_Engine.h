#pragma once
#ifndef __R_RELAST_ENGINE__
#define __R_RELAST_ENGINE__

#define _I_ "int"
#define _F_	"float"
#define _FVEC2_ "vec2"
#define _FVEC3_ "vec3"
#define _FVEC4_ "vec4"
#define _SAMPLER2D_ "sampler2D"
#define _MAT4_ "mat4"


#include<iostream>
#include<string>
#include<vector>
#include<map>

//#include"GL/glew.h"
//#include"GLFW/glfw3.h"
//#include"core/GLMat.h"
#include"GL/glew.h"
#include"GLFW/glfw3.h"

//#include"core/DataType.h"
#include"core/Tools.h"
#include"core/IO.h"
#include"core/Texture.h"
#include"core/Shader.h"
#include"core/Transform.h"

#include"GUI/GUI_Engine.h"

#include"scene_manager/Scene_Manager.h"

#include"core/input/Mouse.h"
#include"core/Engine.h"

#endif // !__R_RELAST_ENGINE__