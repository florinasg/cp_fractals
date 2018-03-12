/*
 * main.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */
#include<iostream>
#include<kfract.h>
#include <cstdlib>

#define KFRACT_BASE_CONST 1

int main(int args, char * argv[])
{
	/*Configures koch fractal*/
	std::cout << "Desired level (l) of koch fractal: " << argv[1] << std::endl;
	kfract * koch_fractal_1 = new kfract(atoi(argv[1]),KFRACT_BASE_CONST,4);

	/*Constructs koch fractal*/
	koch_fractal_1->construct_kfract();

	koch_fractal_1->tag_grid();

	koch_fractal_1->export_kfract_data();

	koch_fractal_1->export_grid_data();



	return 0;
}

