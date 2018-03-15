/*
 * compute_eigenvalues.cpp
 *
 *  Created on: 12.03.2018
 *      Author: Florian Anderl
 */
#include <kfract.h>



int kfract::compute_eigenvalues()
{

	/*DEFINES INITIAL VALUE of U(x) for every grid_point inside the fractal structure*/
	for(int idx = 0; idx < kfract_grid.size(); idx++)
	{
		if(kfract_grid[idx][2] == 1)
			kfract_grid[idx].push_back(double(1));
	}



	return 0;
}

