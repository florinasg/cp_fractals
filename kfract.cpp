/*
 * kfract.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#include "kfract.h"

kfract::kfract() : level_final(0) , kfract_const(1)
{

}

kfract::kfract(int Level_final, int Kfract_const, int Kfract_vector_L) : level_final(Level_final) , kfract_const(Kfract_const), kfract_vector_L(Kfract_vector_L)
{
	level_current = 0;

	/*defines the 'koch' fractal base structure*/
	kfract_fractal = new int[kfract_vector_L][2];
	*(kfract_fractal) = {
			{0, kfract_const},
			{kfract_const, kfract_const},
			{0, kfract_const},
			{0,0}};

}

kfract::~kfract()
{
	delete kfract_fractal;
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
	int (*kfract_fractal_temp)[2];
	kfract_fractal_temp = kfract_fractal;

	/*delete previous matrix*/
	delete kfract_fractal;

	/*allocate new memory for new matrix*/
	kfract_fractal = new int[kfract_vector_L][2];

	/*update fractal constant*/
	kfract_const = kfract_const/4;

	int x_0,y_0,x_1,y_1;
	int xdummy, ydummy;

	int (*temp_coord_matrix)[2];
	temp_coord_matrix = new int[9][2];

	/*TODO*/
	for(idx=0; idx < number_gridP_nminusone; idx++)
	{

		x_0 = x_1;
		y_0 = y_1;
		if(idx == 0)
		{
			x_0 = kfract_fractal_temp[idx][0];
			y_0 = kfract_fractal_temp[idx][1];
		}
		x_1 = kfract_fractal_temp[idx+1][0];
		y_1 = kfract_fractal_temp[idx+1][1];


		/*Algorithm to create fractal base step structure*/

		if(y_1 - y_0)
		{
			if(x_1 < x_0)
			{
				xdummy = x_0;
				x_0 = x_1;
				x_1 = xdummy;
			}

			temp_coord_matrix[0] = {x_0,y_0};
			temp_coord_matrix[1] = {x_0+kfract_const, y_0};
			temp_coord_matrix[2] = {x_0+kfract_const, y_0+kfract_const};
			temp_coord_matrix[3] = {x_0+kfract_const+kfract_const, y_0+kfract_const};
			temp_coord_matrix[4] = {x_0+kfract_const+kfract_const, y_0};
			temp_coord_matrix[5] = {x_0+kfract_const+kfract_const, y_0-kfract_const};
			temp_coord_matrix[6] = {x_0+kfract_const+2*kfract_const, y_0-kfract_const};
			temp_coord_matrix[7] = {x_0+kfract_const+2*kfract_const, y_0};
			temp_coord_matrix[8] = {x_1,y_1};
		}

		else if(x_1 - x_0 == 0)
		{
			if(y_1 > y_0)
			{
				ydummy = y_0;
				y_0 = y_1;
				y_1 = ydummy;
			}

			temp_coord_matrix[0] = {x_0,y_0};
			temp_coord_matrix[1] = {x_0, y_0-kfract_const};
			temp_coord_matrix[2] = {x_0+kfract_const, y_0-kfract_const};
			temp_coord_matrix[3] = {x_0+kfract_const, y_0-2*kfract_const};
			temp_coord_matrix[4] = {x_0, y_0-2*kfract_const};
			temp_coord_matrix[5] = {x_0-kfract_const, y_0-2*kfract_const};
			temp_coord_matrix[6] = {x_0-kfract_const, y_0-3*kfract_const};
			temp_coord_matrix[7] = {x_0, y_0-3*kfract_const};
			temp_coord_matrix[8] = {x_1,y_1};

		}

		for(jdx=curr_pos;jdx<jdx+8;jdx++)
		{

			kfract_fractal[jdx] = temp_coord_matrix[jdx];

		}

		curr_pos = jdx;

		level_current = level_current +1;

		if(level_current<level_final)
			this->construct_kfract();


	}

	return 0;
}



int kfract::get_level()
{
	return level_current;
}




