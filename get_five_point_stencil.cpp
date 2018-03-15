/*
 * get_five_point_stencil.cpp
 *
 *  Created on: 15. mar. 2018
 *      Author: florina
 */


#include <kfract.h>

int kfract::get_five_point_stencil(std::vector<double> grid_point, int grid_idx)
{

	std::vector<double> x_y = 0;
	std::vector<double> x_minus_h = 0;
	std::vector<double> x_plus_h = 0;
	std::vector<double> y_minus_h = 0;
	std::vector<double> y_plus_h = 0;
	int current_coord_block = 0;
	int pos_in_block = 0;

	x_y = grid_point;


	/*NB!*/
	y_minus_h = kfract_grid[grid_idx-1];
	y_plus_h =  kfract_grid[grid_idx+1];


	current_coord_block = grid_idx/(grid_vector_num+1);
	pos_in_block = grid_idx%(grid_vector_num+1);

	x_minus_h = kfract_grid[grid_idx-grid_vector_num+1];
	x_plus_h = kfract_grid[grid_idx+grid_vector_num+1];


	/*ASSIGNS VALUES OF STENCIL POINTS*/


	return 0;
}

