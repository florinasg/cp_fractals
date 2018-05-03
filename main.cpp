/*
 * main.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Sara Gasparini
 *
 *
 *      NOTES: Call function with args = [desired level of koch fractal {LEVEL},
 *      parameter which defines the resolution of the grid (0-10) {grid_const}]
 *      - NB! LEVEL <= (grid_const-1)
 */
#include<iostream>
#include<kfract.h>
#include <cstdlib>
#include <io.h>

#define KFRACT_BASE_CONST 1
#define L_MAX 2




int main(int args, char * argv[])
{
	/*Configures koch fractal*/
	std::cout << "Desired level (l) of koch fractal: " << argv[1] <<"\n";

	if(atoi(argv[1]) >= atoi(argv[2]))
	{
		std::cout << "ERROR: Desired LEVEL cannot be computed by system" << "\n";
		return -1;
	}





	kfract * koch_fractal_1 = new kfract(atoi(argv[1]),KFRACT_BASE_CONST,4, atoi(argv[2]));



	/*Constructs koch fractal*/
	koch_fractal_1->construct_kfract();

	koch_fractal_1->tag_grid();

	koch_fractal_1->export_kfract_data();

	koch_fractal_1->export_grid_data();

	koch_fractal_1->compute_eigenvalues();

	koch_fractal_1->export_EIGENMODE();



	return 0;
}

