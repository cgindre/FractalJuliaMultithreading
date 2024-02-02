#ifndef HEADER_COLOR_SCALE
#define HEADER_COLOR_SCALE

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

struct RGB{
public:
	static const int _colorLevel;
	int _Red;
	int _Green;
	int _Blue;
	RGB();
	RGB(int r, int g, int b);
	RGB(std::string color);
	friend std::ostream& operator<<(std::ostream& os, const RGB& rgb);
};

#endif // HEADER_COLOR_SCALE
