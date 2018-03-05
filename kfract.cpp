/*
 * kfract.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#include "kfract.h"
#include <array>
#include <fstream>
#include <iostream>

int temp_coord_matrix[9][2];

kfract::kfract() : level_final(0) , kfract_const(1)
{

}

kfract::kfract(int Level_final, double Kfract_const, int Kfract_vector_L) : level_final(Level_final) , kfract_const(Kfract_const), kfract_vector_L(Kfract_vector_L)
{
	level_current = 0;

	kfract_fractal = {
			{0, kfract_const},
			{kfract_const, kfract_const},
			{kfract_const, 0},
			{0,0}};
}

kfract::~kfract()
{

}


int kfract::construct_kfract()
{


	/*Help Variables*/
	int idx,jdx = 0;
	int number_gridP = 0;
	int curr_pos = 0;

	/*Stores information from previous state*/
	int number_gridP_nminusone = kfract_vector_L;

	/*Calculates the updated number of 'grip points'*/
	number_gridP = kfract_vector_L*8   -  kfract_vector_L /*for edges counted twice*/ + kfract_vector_L /*for the straight part in the middle*/;

	/*Update Initialization*/
	kfract_vector_L = number_gridP;

	/*Creates temporal copy of grid_point matrix*/
	std::vector<std::vector<double>> kfract_fractal_temp = kfract_fractal;


	std::vector<std::vector<double>> temp_coord_matrix;


	/*Delete previous matrix*/
	kfract_fractal.clear();
	kfract_fractal.resize(kfract_vector_L);



	/*Update fractal constant*/
	kfract_const = kfract_const/4;

	double x_0,y_0,x_1,y_1;
	double xdummy, ydummy;






	/*TODO*/
	for(idx=0; idx < number_gridP_nminusone; idx++)
	{

		x_0 = x_1;
		y_0 = y_1;
		if(idx == 0)
		{
			x_0 = kfract_fractal_temp.at(idx).at(0);
			y_0 = kfract_fractal_temp.at(idx).at(1);
		}
		x_1 = kfract_fractal_temp.at(idx+1).at(0);
		y_1 = kfract_fractal_temp.at(idx+1).at(1);


		/*Algorithm to create fractal-base-step-structure*/

		if(y_1 - y_0 == 0)
		{
			if(x_1 < x_0)
			{
				xdummy = x_0;
				x_0 = x_1;
				x_1 = xdummy;
			}

			temp_coord_matrix = {
					{x_0,y_0},
					{x_0+kfract_const, y_0},
					{x_0+kfract_const, y_0+kfract_const},
					{x_0+kfract_const+kfract_const, y_0+kfract_const},
					{x_0+kfract_const+kfract_const, y_0},
					{x_0+kfract_const+kfract_const, y_0-kfract_const},
					{x_0+kfract_const+2*kfract_const, y_0-kfract_const},
					{x_0+kfract_const+2*kfract_const, y_0},
			};
		}

		else if(x_1 - x_0 == 0)
		{
			if(y_1 > y_0)
			{
				ydummy = y_0;
				y_0 = y_1;
				y_1 = ydummy;
			}

			temp_coord_matrix= {
					{x_0,y_0},
					{x_0, y_0-kfract_const},
					{x_0+kfract_const, y_0-kfract_const},
					{x_0+kfract_const, y_0-2*kfract_const},
					{x_0, y_0-2*kfract_const},
					{x_0-kfract_const, y_0-2*kfract_const},
					{x_0-kfract_const, y_0-3*kfract_const},
					{x_0, y_0-3*kfract_const},
			};

		}

		std::cout << kfract_fractal.size();

		for(jdx=curr_pos;jdx<curr_pos+8;jdx++)
		{

			kfract_fractal.push_back(temp_coord_matrix.at(jdx));

		}

		curr_pos = jdx;

		level_current = level_current +1;

		/*Recursion ;)*/
		if(level_current<level_final)
			this->construct_kfract();


	}

	return 0;
}



int kfract::get_level()
{
	return level_current;
}



int kfract::export_kfract_data()
{
	int idx;
	std::ofstream kfract_data;
	kfract_data.open("kfract_data.txt");

	/*Loop writes data to file*/
	for(idx=0;idx < kfract_fractal.size();idx++)
	{
		kfract_data << kfract_fractal[idx][0] << "," << kfract_fractal[idx][1] << "\n";
	}

	kfract_data.close();


	return 0;
}


