#ifndef HEADER_AREA_THREAD
#define HEADER_AREA_THREAD

#include <string>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <complex>

#include "rgb.h"
#include "colorScale.h"



const double re_min = -3;
const double re_max = 3;

const double im_min = -3;
const double im_max = 3;

class Image
{
public:
	Image(int width = 1920, int height = 1200, const char* cheminImg = "monImage.ppm");
	~Image();
	void write_header();
	void write_color(float value);
protected:
	int _width;
	int _height;
	std::string _cheminImg;
	std::ofstream _fluxImg;
	ColorScale _cs;
};


class AreaThread
{
public:
	AreaThread(int hMin = 0, int deltah = 0);
	AreaThread(const AreaThread &at);
	~AreaThread();
	static double map_to(int pixel, int imgDim, double mini, double maxi);
	static int compute_nb_iter(double re_zn1, double im_zn1);
	static void* job4Thread(void* arg);
	void initialize();
	pthread_t _area_thread;
	int *_pxl_matrix;
	static const int _width;
	static const int _height;
protected:
	int _hMin;
	int _hMax;
	int _deltah;
	static const int _nbMaxIter;
};

#endif // HEADER_AREA_THREAD
