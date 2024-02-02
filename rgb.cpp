#include "rgb.h"

const int RGB::_colorLevel = 255;

RGB::RGB()
{
	std::srand(std::time(NULL));
	int modulo = _colorLevel +1;
 	_Red = rand() % modulo;
	_Green = rand() % modulo;
	_Blue = rand() % modulo;
}

RGB::RGB(int r, int g, int b)
{
	_Red = r;
	_Green = g;
	_Blue = b;
}

RGB::RGB(std::string color)
{
	std::cout << "color ..." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const RGB& rgb)
{
	os << rgb._Red << " " << rgb._Green << " " << rgb._Blue;
	return os;
}


