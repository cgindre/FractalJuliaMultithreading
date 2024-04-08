#include "areaThread.h"

Image::Image(int width, int height, const char* cheminImg): _width(width), _height(height), _cheminImg(cheminImg)
{
	_fluxImg.open(cheminImg);
}


void Image::write_header()
{
	_fluxImg << "P3" << std::endl;
	_fluxImg << _width << " " << _height << std::endl;
	_fluxImg << RGB::_colorLevel << std::endl;
	_fluxImg << std::endl;
}

void Image::write_color(float value)
{
	_fluxImg << _cs.getLinColor(value) << '\n';
}

Image::~Image()
{
	//std::cout << "Appel destructeur image" << std::endl;
	_fluxImg.close();
}


const int AreaThread::_width = 1920;
const int AreaThread::_height = 1200;
const int AreaThread::_nbMaxIter = 100;

AreaThread::AreaThread(int hMin, int deltah):_hMin(hMin), _hMax(hMin + deltah), _deltah(deltah)
{
	std::cout << "Appel constructeur AreaThread" << std::endl;
	//_pxl_matrix _nbMaxIter= NULL;
	_pxl_matrix = NULL;
}

AreaThread::AreaThread(const AreaThread &at): _hMin(at._hMin), _hMax(at._hMax), _deltah(at._deltah)
{
	std::cout << "Appel constructeur copie AreaThread" << std::endl;
	if(at._pxl_matrix != NULL)
	{
		int size = _deltah * _width;
		_pxl_matrix = new int [size];
		for(int i = 0 ; i < size ; ++i)
			_pxl_matrix[i] = at._pxl_matrix[i];
	}
	else _pxl_matrix = NULL;
}

AreaThread::~AreaThread()
{
	std::cout << "Appel destructeur AreaThread" << std::endl;
	delete [] _pxl_matrix;
}

void AreaThread::initialize()
{
	std::cout << "IN initialize .." << std::endl;
	if(_deltah != 0)
		_pxl_matrix = new int[_deltah * _width];
	else 
		_pxl_matrix = NULL;

}

double AreaThread::map_to(int pixel, int imgDim, double mini, double maxi)
{
	double rang = maxi - mini;
	double value = pixel * rang / imgDim + mini; 
	return value;
}

// N.B. Possible aussi d'utiliser l'en-tête <complex> ...
int AreaThread::compute_nb_iter(double re_zn1, double im_zn1)
{
	int counter = 0;
	double re_zn1_tmp = 0;

	double re_c = 0.3;
	double im_c = 0.5; 

	while((re_zn1 * re_zn1 + im_zn1 * im_zn1) <= 4.0 && counter < _nbMaxIter)
	{
		++counter;
		re_zn1_tmp = re_zn1;
		re_zn1 = (re_zn1 * re_zn1 - im_zn1 * im_zn1 + re_c);
		im_zn1 = (2 * re_zn1_tmp * im_zn1 + im_c);
	}

	return counter;
}

void* AreaThread::job4Thread(void* arg)
{
	std::cout << "IN job4Thread ..." << std::endl;

	AreaThread *at = static_cast<AreaThread*>(arg);
	int nb_iter = 0;
	int counter = 0;

	for(int h = at->_hMin ; h < at->_hMax ; ++h)
	{

		double x_val = map_to(h, _height, im_min, im_max);
		for(int w = 0 ; w < _width ; ++w, ++counter)
		{
			double y_val = map_to(w, _width, re_min, re_max);
			nb_iter = compute_nb_iter(x_val, y_val);

			if(at->_pxl_matrix != NULL)
				at->_pxl_matrix[counter] = nb_iter; 

		}
	}

	return NULL;
}
