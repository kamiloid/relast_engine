#pragma once

#ifndef __RE_TRANSFORM_CONTROL__
#define __RE_TRANSFORM_CONTROL__

#include"Relast/core/Tools.h"
#include"Relast/core/Transform.h"
#include"Main_menu.h"

namespace addons
{
	namespace transform
	{
		void init(Relast::Rectf viewport_size);
		Relast::enums::TRANSFORM_TYPE get_transform_type();
		Relast::enums::TRANSFORM_OPERATION get_transform_operation();
	}
}

#endif // !__RE_TRANSFORM_CONTROL__
