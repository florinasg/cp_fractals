/*
 * export_EIGENMODE.cpp
 *
 *  Created on: 27.03.2018
 *      Author: Florian Anderl
 */

#include "kfract.h"
#include <fstream>
#include <vector>


int kfract::export_EIGENMODE()
{
	int hdx = 0;
	int grid_index = 0;
	int eigenvec_index = 0;
	arma::vec EIG;
	std::ofstream eigenmode;

	for(hdx = 0; hdx < eigvec.n_cols; hdx++)
	{
		EIG = eigvec.col(hdx);
		eigenmode.open("Eigenmode_Level"+std::to_string(level_final)+"EM_"+std::to_string(hdx)+".csv");
		grid_index = 0;
		eigenvec_index = 0;

		for(int idx = 0; idx< (grid_vector_num+1); idx++)
		{
			/*denotes the row index of THE GRID (NOT THE MATRIX)*/
			for(int jdx = grid_vector_num; jdx >=0 ; jdx--)
			{
				/*reads the stored grid points column-wise top-down*/
				grid_index = (idx*(grid_vector_num+1))+jdx;
				if(kfract_grid[grid_index][2] == 1)
				{
					kfract_grid[grid_index].push_back(double(EIG[eigenvec_index]));
					eigenmode << kfract_grid.at(grid_index).at(0) << "," << kfract_grid.at(grid_index).at(1) << "," <<  kfract_grid.at(grid_index).at(2) <<","
							<<kfract_grid.at(grid_index).at(3)<<"\n";
				}
				else if (kfract_grid[grid_index][2] == -1)
				{
					kfract_grid[grid_index].push_back(double(0));
					eigenmode << kfract_grid.at(grid_index).at(0) << "," << kfract_grid.at(grid_index).at(1) << "," <<  kfract_grid.at(grid_index).at(2) <<","
							<<kfract_grid.at(grid_index).at(3)<<"\n";
				}


				/*Questionable if comment or uncomment*/
//				else if(kfract_grid[grid_index][2] == 0)
//				{
//					kfract_grid[grid_index].push_back(double(0));
//					eigenmode << kfract_grid.at(grid_index).at(0) << "," << kfract_grid.at(grid_index).at(1) << "," <<  kfract_grid.at(grid_index).at(2) <<","
//							<<kfract_grid.at(grid_index).at(3)<<"\n";
//
//				}

				eigenvec_index ++;
			}

		}
		eigenmode.close();
	}



	return 0;
}
