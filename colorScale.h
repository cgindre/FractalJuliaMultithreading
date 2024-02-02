#ifndef HEADER_COLORSCALE
#define HEADER_COLORSCALE

#include "rgb.h"

class ColorScale
{
private:
	int _min_value;
	int _max_value;

	static const RGB BLACK;
	static const RGB RED;
	static const RGB GREEN;
	static const RGB BLUE;
	static const RGB YELLOW;

	static const RGB colors[];

public:
	ColorScale(int min_value = 0, int max_value = 100);
	RGB getLinColor(float value);
	void lin_interpol(float interval, float index, const RGB* StartColor, const RGB* EndColor, RGB* ResultColor);

};

#endif //HEADER_COLORSCALE
