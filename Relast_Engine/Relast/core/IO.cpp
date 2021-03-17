#include"IO.h"

String Relast::io::load_file_2_string(const String filepath)
{
	std::ifstream stream(filepath);
	String line;
	String file = "";
	while (std::getline(stream, line))
	{
		file += line + "\n";
	}
	return file;
}