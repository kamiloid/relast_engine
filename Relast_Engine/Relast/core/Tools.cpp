//#include"../Relast_Engine.h"
#include"Tools.h"
#include <stdlib.h>
#include <time.h>



//void Relast::Color::set_color(FLOAT r, FLOAT g, FLOAT b, FLOAT a)
//{
//	this->_r = r;
//	this->_g = g;
//	this->_b = b;
//	this->_a = a;
//}

void Relast::Buffer_data::save_data(std::vector<FLOAT> vertices, std::vector<UINT> indices)
{
	Relast::Buffer_data data;
	data._vertices = vertices;
	data._indices = indices;
}


void Relast::number::seed()
{
	std::srand(time(NULL));
}
INT Relast::number::random_i(INT min, INT max)
{
	return min + (std::rand() % max);
}




bool Relast::string::match_str(String txt, String match)
{
	return txt.find(match) != String::npos;
}

std::vector<String> Relast::string::str_split(String str, String delimiter)
{
	rsize_t pos = 0;
	String token;
	std::vector<String> buffer;
	while ((pos = str.find(delimiter)) != String::npos)
	{
		String next_str = str;
		next_str.erase(pos, pos + delimiter.length());
		rsize_t next_pos = next_str.find(delimiter);
		token = str.substr(pos + delimiter.length(), next_pos);
		if (token != "")
		{
			buffer.push_back(token);
			str.erase(pos, pos + delimiter.length());
			str.erase(pos, next_pos);
		}
	}
	return buffer;
}

std::vector<String> Relast::string::super_split(String str, String delimiter)
{
	String txt_aux = str + delimiter;
	rsize_t pos = 0;
	String token;
	std::vector<String> buffer;
	std::vector<rsize_t> indices;
	while ((pos = txt_aux.find(delimiter)) != String::npos)
	{
		indices.push_back(pos + 1);
		token = txt_aux.substr(0, pos);
		buffer.push_back(token);
		txt_aux.erase(0, pos + 1);
	}
	return buffer;
}

std::vector<String> Relast::string::split_range(String str, String init_delimiter, String finish_delimiter)
{
	//String txt_aux = str;
	rsize_t pos = 0;
	String token;
	std::vector<String> buffer;
	while ((pos = str.find(init_delimiter)) != String::npos)
	{
		String aux = str;
		String next_str = str.erase(0, pos);
		rsize_t end_pos = next_str.find(finish_delimiter);
		token = aux.substr(pos, end_pos);
		buffer.push_back(token);
		str.erase(0, end_pos);
	}
	return buffer;
}

String Relast::string::replace(String text, String match_text, String new_text)
{
	rsize_t pos = 0;
	String str = text;
	while ((pos = str.find(match_text)) != String::npos)
		str = str.replace(pos, match_text.length(), new_text.c_str());
	return str;
}

UINT Relast::string::char_lenght(char* c)
{
	return std::strlen(c);
}

char* Relast::string::string_2_array(String text)
{
	char* ca = new char[text.size() + 1];
	std::copy(text.begin(), text.end(), ca);
	ca[text.size()] = '\0';
	return ca;
}

String Relast::string::array_2_string(char* array_)
{
	UINT size = string::char_lenght(array_);
	std::string text(array_, size);
	return text;
}

String Relast::string::get_uid(UINT length)
{
	char l[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	String gui = "";
	for (UINT i = 0; i < length; i++)
	{
		INT rnd = number::random_i(0, sizeof(l) / sizeof(*l) - 1);
		gui += l[rnd];
	}
	return gui;
}