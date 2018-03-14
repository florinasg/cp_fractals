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
#include <algorithm>
#include <string.h>
#include <cmath>



double x_0,y_0,x_1,y_1;

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


	/*Defines grid constant for koch fractal*/
	kfract_const_init = kfract_const;
	kfract_grid_constant = kfract_const_init;


	int l_max = 5;

	for(int idx = 0; idx <l_max; idx++)
	{
		kfract_grid_constant = kfract_grid_constant/4;
	}


	/*Creates grid & tags grip-point with marker in function (see method-call in main())*/

	/*defines grid*/
	double x_grid = kfract_const_init;
	double y_grid = kfract_const_init;
	double y_grid_reset = 0;
	double x_grid_reset = 0;
	for(int idx = 1; idx <= level_final; idx++)
	{
		x_grid = x_grid + kfract_const_init/(pow(4,idx));
		y_grid = y_grid + kfract_const_init/(pow(4,idx));
	}

	/*Start Coordinates*/
	x_grid = - (x_grid-kfract_const_init);
	y_grid = - (y_grid-kfract_const_init);

	/*Assistance Index*/

	x_grid_reset = x_grid;
	y_grid_reset = y_grid;
	int sum_idx = 0;

	/*Class member assignment*/
	grid_vector_num = (kfract_const_init+(2*(-x_grid_reset)))/kfract_grid_constant;


	for(int jdx = 0;jdx<=(kfract_const_init+(2*(-x_grid_reset)))/kfract_grid_constant; jdx++)
	{

		y_grid = y_grid_reset;
		for(int gdx=0;gdx<=(kfract_const_init+(2*(-y_grid_reset)))/kfract_grid_constant;gdx++)
		{


			kfract_grid.push_back(std::vector<double>());
			kfract_grid[sum_idx].push_back(double());
			kfract_grid[sum_idx][0] = x_grid;
			kfract_grid[sum_idx].push_back(double());
			kfract_grid[sum_idx][1] = y_grid;
			kfract_grid[sum_idx].push_back(double());
			kfract_grid[sum_idx][2] = 0;

			//std::cout << sum_idx << " " << kfract_grid[sum_idx][0] << " " << kfract_grid[sum_idx][1] << std::endl;

			y_grid = y_grid + kfract_grid_constant;
			sum_idx+=1;

		}
		x_grid = x_grid + kfract_grid_constant;
	}



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
	temp_coord_matrix.resize(8);


	/*Delete previous matrix*/
	kfract_fractal.clear();

	/*14.03.2017 DO NOT CHANGE!!!*/
	kfract_fractal.resize(kfract_vector_L);



	/*Update fractal constant*/
	kfract_const = kfract_const/4;









	/*TODO*/
	for(idx=0; idx < number_gridP_nminusone; idx++)
	{

		int dummy_idx = idx;
		x_0 = x_1;
		y_0 = y_1;
		if(idx == 0)
		{
			x_0 = kfract_fractal_temp.at(idx).at(0);
			y_0 = kfract_fractal_temp.at(idx).at(1);
		}

		if(idx+1 == number_gridP_nminusone)
		{
			dummy_idx = -1;
		}

		x_1 = kfract_fractal_temp.at(dummy_idx+1).at(0);
		y_1 = kfract_fractal_temp.at(dummy_idx+1).at(1);


		/*Algorithm to create fractal-base-step-structure*/

		if(y_1 - y_0 == 0)
		{
			if(x_1 < x_0)
			{
				temp_coord_matrix = {
						{x_0,y_0},
						{x_0-kfract_const, y_0},
						{x_0-kfract_const, y_0-kfract_const},
						{x_0-kfract_const-kfract_const, y_0-kfract_const},
						{x_0-kfract_const-kfract_const, y_0},
						{x_0-kfract_const-kfract_const, y_0+kfract_const},
						{x_0-kfract_const-2*kfract_const, y_0+kfract_const},
						{x_0-kfract_const-2*kfract_const, y_0},
				};
			}
			else
			{
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
		}

		else if(x_1 - x_0 == 0)
		{
			if(y_1 > y_0)
			{
				temp_coord_matrix= {
						{x_0,y_0},
						{x_0, y_0+kfract_const},
						{x_0-kfract_const, y_0+kfract_const},
						{x_0-kfract_const, y_0+2*kfract_const},
						{x_0, y_0+2*kfract_const},
						{x_0+kfract_const, y_0+2*kfract_const},
						{x_0+kfract_const, y_0+3*kfract_const},
						{x_0, y_0+3*kfract_const},
				};
			}
			else
			{
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
		}



		for(jdx=curr_pos;jdx<curr_pos+8;jdx++)
		{

			kfract_fractal.push_back(std::vector<double>());
			kfract_fractal[jdx].push_back(double());
			kfract_fractal[jdx][0] = temp_coord_matrix.at(jdx-curr_pos).at(0);
			kfract_fractal[jdx].push_back(double());
			kfract_fractal[jdx][1] = temp_coord_matrix.at(jdx-curr_pos).at(1);

		}

		curr_pos = jdx;





	}


	level_current = level_current +1;

	/*Recursion ;)*/
	if(level_current<level_final)
		this->construct_kfract();



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
	kfract_data.open("kfract_data"+std::to_string(level_final)+".csv");

	/*Loop writes data to file*/
	for(idx=0;idx < kfract_vector_L;idx++)
	{
		kfract_data << kfract_fractal.at(idx).at(0) << "," << kfract_fractal.at(idx).at(1) << "\n";
	}

	kfract_data << "0" << "," << kfract_const_init << "\n";
	kfract_data.close();

	std::cout << "(EXPORT FRACTAL DATA)...Finished successfully\n" << "Grid constant 'rho': "<< kfract_grid_constant << std::endl;

	return 0;
}



int kfract::export_grid_data()
{
	int idx;
	std::ofstream kfract_data;
	kfract_data.open("kfract_grid_data"+std::to_string(level_final)+".csv");

	/*Loop writes data to file*/
	for(idx=0;idx < (grid_vector_num+1)*(grid_vector_num+1);idx++)
	{
		kfract_data << kfract_grid.at(idx).at(0) << "," << kfract_grid.at(idx).at(1) << "," <<  kfract_grid.at(idx).at(2) <<"\n";
	}

	kfract_data << "0" << "," << kfract_const_init << "," << "-1" << "\n";
	kfract_data.close();

	std::cout << "(EXPORT GRID DATA) ... Finished successfully\n" <<  std::endl;

	return 0;
}






int kfract::tag_grid()
{
	try
	{
		std::vector<std::vector<double>>::iterator it;
		int index;
		int jdex;

		int jdex_2;

		/*edge_index_vec contains the indices of edge points within kfract_grid*/
		std::vector<int> edge_index_vec;

		std::cout << "size of kfract_fractl (NB! #double): "<< kfract_fractal.size() << std::endl;

		/*this for loop tags edge points with -1*/
		for(int jdx=0;jdx<(kfract_fractal.size())/2;jdx++)
		{

			//std::cout << "vector: " << kfract_fractal.at(jdx).at(0) << " " << kfract_fractal.at(jdx).at(1) << std::endl;
			std::vector<double> p = {kfract_fractal.at(jdx).at(0),kfract_fractal.at(jdx).at(1), 0};
			it = std::find(kfract_grid.begin(), kfract_grid.end(), p);
			index = std::distance(kfract_grid.begin(), it);
			edge_index_vec.push_back(int(index));
			/*-1 indicates grid point is located on EDGE of fractal*/
			kfract_grid[index][2] = -1;
			//std::cout << "(" << jdx << ")values at index " << index << " "<< kfract_grid[index].at(0) << " " << kfract_grid[index].at(1) << " " << kfract_grid[index].at(2) << std::endl;
		}


		std::vector<double> n;
		std::vector<double> nplusone;




		int hitcounter = 0;
		int hitcount_offset = 0;

		/*VERY TRICKY PART COMES HERE*/
		for(int idx = 0; idx < kfract_fractal.size()/2; idx++)
		{



			n = kfract_fractal[idx];
			nplusone = kfract_fractal[idx+1];

			if(idx == kfract_fractal.size()/2-1)
				nplusone = kfract_fractal[idx+1] = {0,1};


//			std::cout << "n " << n[0] << " " << n[1] << std::endl;
//			std::cout << "nplusone " << nplusone[0] << " " << nplusone[1] << std::endl;


			if((n[1]-nplusone[1] == 0) && (n[0] < nplusone[0]))
			{
				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
				hitcounter = 0;

				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
				{
					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
					if((kfract_grid[jdx][0]>n[0]) && (kfract_grid[jdx][0] < nplusone[0]) && kfract_grid[jdx][1] == n[1])
					{
						hitcounter++;
						//std::cout <<"hit "<< jdx<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
						kfract_grid[jdx][2] = -1;
						edge_index_vec.insert(edge_index_vec.begin()+(hitcounter+hitcount_offset), jdx);


					}
				}


			}

			else if((n[0]-nplusone[0] == 0) && (n[1] < nplusone[1]))
			{
				hitcounter = 0;

				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
				{
					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
					if((kfract_grid[jdx][1]>n[1]) && (kfract_grid[jdx][1] < nplusone[1]) && kfract_grid[jdx][0] == n[0])
					{
						hitcounter++;
						//std::cout <<"hit "<< jdx << kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
						kfract_grid[jdx][2] = -1;
						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);
					}
				}

			}


			else if((n[1]-nplusone[1] == 0) && (n[0] > nplusone[0]))
			{
				hitcounter = 0;

				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
				{
					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
					if((kfract_grid[jdx][0]<n[0]) && (kfract_grid[jdx][0] > nplusone[0]) && kfract_grid[jdx][1] == n[1])
					{
						hitcounter++;
						//std::cout <<"hit "<< jdx<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
						kfract_grid[jdx][2] = -1;
						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);

					}
				}


			}

			else if((n[0]-nplusone[0] == 0) && (n[1] > nplusone[1]))
			{

				hitcounter = 0;

				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
				{


					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
					if((kfract_grid[jdx][1]<n[1]) && (kfract_grid[jdx][1] > nplusone[1])&& kfract_grid[jdx][0] == n[0])
					{
						hitcounter++;
						//std::cout <<"hit "<< jdx <<" "<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
						kfract_grid[jdx][2] = -1;
						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);
					}
				}


			}


			/*TODO: FIND GENERIC TERM*/
			hitcount_offset= hitcount_offset + 4;

		}


		std::cout << "edge index vector length: "<< edge_index_vec.size() << std::endl;


		/*----------------------------------------------------------------------------------*/

		/*TODO FIND NEW BOUNDARY CONDITION for for loop (14.03.2018)
		 * UPDATE: deleted /2 in every limit condition */
		for(int idx=0;idx<=(((edge_index_vec.size()))/4); idx++)
		{
			int dummy_idx = edge_index_vec[idx];

			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
			jdex = dummy_idx % (grid_vector_num+1);

			/*grid points UNDER edge point*/
			for(int jdx=jdex; jdx > 0; jdx=jdx-1)
			{
				std::cout << "VOR " <<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] <<" " << kfract_grid[dummy_idx-jdx][2] <<std::endl;

				/*TODO NB! CONDITION */
				if(kfract_grid[dummy_idx-jdx][2] == 0)
					kfract_grid[dummy_idx-jdx][2] = 1;

				std::cout << "NACH "<<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] << " " <<kfract_grid[dummy_idx-jdx][2] <<std::endl;
			}

		}


		std::cout << "RIGHT EDGE" << std::endl;

		/*#2 RIGHT EDGE
		 * NOTE THE '+1' in the initial value for idx*/
		for(int idx=(((edge_index_vec.size()))/4)+1;idx<((edge_index_vec.size()))/2; idx++)
		{
			int dummy_idx = edge_index_vec[idx];

			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
			jdex = dummy_idx%(grid_vector_num+1);

			/*floor rounds down value; jdex_2 denotes the current block of coordinates*/
			jdex_2 = floor(edge_index_vec[idx]/(grid_vector_num+1));



			/*grid points left of edge point TODO Validate*/
			for(int jdx=0; jdx < jdex_2; jdx=jdx+1)
			{
				std::cout << "VOR " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] <<" " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;

				/*TODO NB! CONDITION */
				if(kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] == 0)
					kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] = 1;

				std::cout << "NACH "<<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] << " " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
			}


		}

		std::cout << "LOWER EDGE" << std::endl;

		/*#3 LOWER EDGE (has to redo down area)*/
		for(int idx=(edge_index_vec.size()/2); idx<=((edge_index_vec.size()))-(edge_index_vec.size()/4); idx++)
		{
			int dummy_idx = edge_index_vec[idx];
			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
			jdex = dummy_idx % (grid_vector_num+1);

			/*grid points UNDER edge point*/
			for(int jdx=jdex; jdx > 0; jdx=jdx-1)
			{
				std::cout << "VOR " <<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] <<" " << kfract_grid[dummy_idx-jdx][2] <<std::endl;

				/*TODO NB! CONDITION */
				if(kfract_grid[dummy_idx-jdx][2] == 1)
					kfract_grid[dummy_idx-jdx][2] = 0;

				std::cout << "NACH "<<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] << " " <<kfract_grid[dummy_idx-jdx][2] <<std::endl;
			}


		}


		std::cout << "LEFT EDGE" << std::endl;

		/*#4 LEFT EDGE (has to redo left area)*/
		for(int idx=(((edge_index_vec.size()))-(edge_index_vec.size())/4);idx<(edge_index_vec.size());idx++)
		{
			int dummy_idx = edge_index_vec[idx];

			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
			jdex = dummy_idx%(grid_vector_num+1);
			/*floor rounds down value; jdex_2 denotes the current block of coordinates*/
			jdex_2 = floor(edge_index_vec[idx]/(grid_vector_num+1));



			/*grid points left of edge point TODO Validate*/
			for(int jdx=0; jdx < jdex_2; jdx=jdx+1)
			{
				std::cout << "VOR " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] <<" " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;

				/*TODO NB! CONDITION */
				if(kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] == 1)
					kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] = 0;

				std::cout << "NACH "<<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] << " " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
			}


		}


	}

	catch(std::exception &e)
	{
		std::cout << "error occurred: " << e.what() << std::endl;
	}


	return 0;
}


std::vector<std::vector<double>> kfract::get_kfract_fractal()
{
	return kfract_fractal;
}





