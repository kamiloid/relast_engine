#pragma once
#ifndef __R_IO__
#define __R_IO__

#include<iostream>
#include<fstream>
#include<string>

#include"Tools.h"
//#include"DataType.h"

namespace Relast
{
	namespace io
	{
		String load_file_2_string(const String filepath);
	}
}

#endif // !__R_IO__