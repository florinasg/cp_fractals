/*
 * compute_eigenvalues.cpp

 *
 *  Created on: 12.03.2018
 *      Author: Sara Gasparini
 *
 *
 *      Computes the Eigenvalues + Eigenmodes for the respective koch fractal
 *      Notes:
 *      - the grid that is defined within this scope in a x/y coordinate system is stored in a std::vector in the following manner
 *      	std::vector<std::vector> grid = {
 *			{double x_coordinate, double y_coordinate , int status}
 *      	{...},
 *      	...
 *      	  }
 *     	-  int status [0 -> outside fractal, 1-> inside fractal], -1 -> fractal edge
 *		- the grid points are stored column-wise from BOTTOM to TOP
 *		- this will require a workaround regarding the running index in this function since we will go through the grid columnwise from TOP to BOTTOM
 */



#include <kfract.h>
#include <armadillo>
#include <iostream>


int kfract::compute_eigenvalues()
{


	try{



		/*denotes total number of gridpoints and hence A matrix dimension*/
		int matrix_dim = kfract_grid.size();




		/*declares sparse matrix*/
		arma::sp_mat A(matrix_dim,matrix_dim);


		/*Declares & Initializes the grid points for use in the five-point-stencil*/
		std::vector<double> current_grid_point = {0};
		std::vector<double> x_minus_h = {0};
		std::vector<double> x_plus_h = {0};
		std::vector<double> y_minus_h = {0};
		std::vector<double> y_plus_h ={0};

		/*Help Variables for A Matrix*/
		int row_idx = 0;


		/*workaround- running index (see documentation)*/
		int grid_index = 0;



		/*Defines the matrix A (five-point-stencil) */
		/*denotes the column index of THE GRID (NOT THE MATRIX)*/
		for(int idx = 0; idx< (grid_vector_num+1); idx++)
		{
			/*denotes the row index of THE GRID (NOT THE MATRIX)*/
			for(int jdx = grid_vector_num; jdx >=0 ; jdx--)
			{
				/*reads the stored grid points column-wise top-down*/
				grid_index = (idx*(grid_vector_num+1))+jdx;



				current_grid_point = kfract_grid[grid_index];

				//std::cout << "("<<grid_index<<")" << " " << current_grid_point[0] << " " << current_grid_point[1] << " " << current_grid_point[2] << std::endl;



				if(current_grid_point[2] == 1)
				{


					y_minus_h = kfract_grid[grid_index-1];
					y_plus_h = kfract_grid[grid_index+1];

					x_plus_h = kfract_grid[grid_index + (grid_vector_num+1)];
					x_minus_h = kfract_grid[grid_index - (grid_vector_num+1)];

					/*current point*/
					A(row_idx,row_idx) = 4;


					/*y+h*/
					if(y_plus_h[2] == 1)
					{
						A(row_idx,row_idx -1) = -1;

					}

					/*y-h*/
					if(y_minus_h[2] == 1)
					{
						A(row_idx,row_idx+1) = -1;

					}

					/*x+h*/
					if(x_plus_h[2] == 1)
					{
						A(row_idx, row_idx+(grid_vector_num+1)) = -1;

					}

					/*x-h*/
					if(x_minus_h[2] == 1)
					{
						A(row_idx, row_idx-(grid_vector_num+1)) = -1;

					}

				}


				row_idx ++;
			}



		}



		/*Implements Definition of five-point-stenci (* 1/h^2)*/
		A = A / (kfract_grid_constant*kfract_grid_constant);

		/*saves matrix -> only for debugging purposes*/
//		arma::mat A_check(A);
//		A_check.save("A_matrix"+std::to_string(level_final)+".csv", arma::csv_ascii);


		/*Computes 10 smallest eigenvalues -> for symmetrix matrix
		 * IS A SYMMETRIC??! TODO: SOLVE!
		 * NB! use eigs_gen for general square matrix*/

		arma::eigs_gen(eigval_c,eigvec_c,A,100);

//		eigval.save("Eigenvalues.csv", arma::csv_ascii);
//		eigvec.save("Eigenvectors.csv", arma::csv_ascii);

		/*for general square matrix*/
		eigval_c.save("Eigenvalues_c.csv", arma::csv_ascii);
		eigvec_c.save("Eigenvectors_c.csv", arma::csv_ascii);


		std::cout<< "Eigenvalues: \n" << eigval << std::endl;

	}



	catch(std::exception &e)
	{
		std::cout << "EXCEPTION: " << e.what();
	}



	return 0;
}

