#include "colorScale.h"

const RGB ColorScale::BLACK(0, 0, 0);
const RGB ColorScale::RED(255, 0, 0);
const RGB ColorScale::GREEN(0, 255, 0);
const RGB ColorScale::BLUE(0, 0, 255);
const RGB ColorScale::YELLOW(255, 255, 0);

const RGB ColorScale::colors[] = {BLACK, BLUE, GREEN, YELLOW, RED};

ColorScale::ColorScale(int min_value, int max_value):_min_value(min_value), _max_value(max_value){};


void ColorScale::lin_interpol(float interval, float index, const RGB* StartColor, const RGB* EndColor, RGB* ResultColor)
{
	ResultColor->_Red = index /interval * EndColor->_Red + (interval - index) / interval * StartColor->_Red;
	ResultColor->_Green = index / interval * EndColor->_Green + (interval - index) / interval * StartColor->_Green;
	ResultColor->_Blue = index / interval * EndColor->_Blue + (interval - index) / interval * StartColor->_Blue;
}

RGB ColorScale::getLinColor(float value)
{
	int min_value = 0;
	int max_value = 100;
	int range_value = max_value - min_value;
	int nb_interval = sizeof(colors) / sizeof(RGB) - 1;
	int width_interval = range_value / nb_interval;

	if(value < min_value)
	{
		std::cout << "Valeur trop faible ..." << std::endl;
		return RGB(0,0,0);
	}
	else if(value > max_value)
	{
		std::cout << "Valeur trop grande ..." << std::endl;
		return RGB(255, 255, 255);
	}
	else
	{
		int div = value / width_interval;
		int rest = static_cast<int>(value) % width_interval;

		RGB couleurRes(0,0,0);

		lin_interpol(width_interval, rest, colors + div, colors + div + 1, &couleurRes);

		return couleurRes;
	}
		
}
