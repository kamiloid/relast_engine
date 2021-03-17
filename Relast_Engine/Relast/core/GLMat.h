#pragma once
#ifndef __R_GLMATH__
#define	_R_GLMATH__

#define _PI_ 3.14159265358979323846f
#define _RAD_ _PI_ / 180.0f
#define _DEG_ 180.0f / _PI_

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/quaternion.hpp>

#define MATH_3D_IMPLEMENTATION
#include"../deps/Math_3D/math_3d.h"


#endif //!__R_GLMATH__