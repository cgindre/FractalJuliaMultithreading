#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>

#include "rgb.h"
#include "colorScale.h"
#include "areaThread.h"

int main()
{	
	std::cout << "Compute fractal" << std::endl;

	const int width = 1920;
	const int height = 1200;
	const char* cheminImg = "fractaljulia.ppm";
	int nbThreads = 9;

	clock_t start, end;
	//std::vector<AreaThread> vect_at; 
    std::vector<AreaThread> vect_at(2); 

	int deltah = height / nbThreads;

	start = clock();
/*
	//AreaThread a;
	{
		vect_at.push_back(AreaThread(5, 10));
	}
	vect_at[0].initialize();
*/

	int no_thread = 0;
	for(int h = 0 ; h < height ; h += deltah, ++no_thread)
	{
		std::cout << "no_thread = " << no_thread << std::endl;
		//vect_at.push_back(AreaThread(h, deltah));
		vect_at[no_thread] = AreaThread(h, deltah);

		vect_at[no_thread].initialize();
		pthread_create(&(vect_at[no_thread]._area_thread), NULL, AreaThread::job4Thread, &vect_at[no_thread]);				
	}
/*
	for(int i = 0 ; i < nbThreads ; ++i)
	{
		pthread_join(vect_at[i]._area_thread, NULL);
	}
*/

	Image img(width, height, cheminImg);
	img.write_header();

	for(no_thread = 0 ; no_thread < nbThreads ; ++no_thread)
	{
		for(int w = 0 ; w < (width * deltah) ; ++w)
		{
			img.write_color(static_cast<float>(vect_at[no_thread]._pxl_matrix[w]));
		}
	}

	end = clock();

	double exetime = ((double) end - start) / CLOCKS_PER_SEC;
	std::cout << "Le delai d'execution vaut : " << exetime << "s." << std::endl;

	return 0;
}
