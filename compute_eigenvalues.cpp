/*
 * compute_eigenvalues.cpp

 *
 *  Created on: 12.03.2018
 *      Author: Florian Anderl
 */



#include <kfract.h>
#include <armadillo>
#include <iostream>



int kfract::compute_eigenvalues()
{


	try{

		/*denotes total number of gridpoints and hence A matrix dimension*/
		int matrix_dim = kfract_grid.size();


		//std::cout << "sizeofvector: " << matrix_dim << std::endl;

		/*NON - sparse matrix*/
		arma::sp_mat A(matrix_dim,matrix_dim);

	//	A.zeros();

		std::vector<double> current_grid_point = {0};
		std::vector<double> x_minus_h = { 0};
		std::vector<double> x_plus_h = {0};
		std::vector<double> y_minus_h = {0};
		std::vector<double> y_plus_h ={ 0};

		/*Help Variables for A Matrix*/
		int row_idx = 0;


		int grid_index = 0;

		//A = 4.*A.eye();


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

					/*+/- ??!!! -> should be correct like that */
					y_minus_h = kfract_grid[grid_index-1];
					y_plus_h = kfract_grid[grid_index+1];

					x_plus_h = kfract_grid[grid_index + (grid_vector_num+1)];
					x_minus_h = kfract_grid[grid_index - (grid_vector_num+1)];

					/*current point*/
					A(row_idx,row_idx) = 4;

					/*y+h*/
					if(y_plus_h[2] == 1)
						A(row_idx,row_idx -1) = -1;

					/*y-h*/
					if(y_minus_h[2] == 1)
						A(row_idx,row_idx+1) = -1;

					/*x+h*/
					if(x_plus_h[2] == 1)
						A(row_idx, row_idx+(grid_vector_num+1)) = -1;

					/*x-h*/
					if(x_minus_h[2] == 1)
						A(row_idx, row_idx-(grid_vector_num+1)) = -1;

				}

					/*increments row*/
					row_idx ++;
			}

			std::cout << std::endl;

		}

		
		
		A = A / (kfract_grid_constant*kfract_grid_constant); 
		A.save("A_matrix.csv", arma::arma_ascii);

//		/ generate sparse matrix
//		sp_mat A = sprandu<sp_mat>(1000, 1000, 0.1);
//
//		cx_vec eigval;
//		cx_mat eigvec;
//
//		eigs_gen(eigval, eigvec, A, 5);  // find 5 eigenvalues/eigenvectors


		arma::vec eigval;
		arma::mat eigvec;

		/*Computes 10 smallest eigenvalues*/
	    arma::eigs_sym(eigval,eigvec,A,10);

	    eigval.save("Eigenvalues.csv", arma::arma_ascii);
	    eigval.save("Eigenvectors.csv", arma::arma_ascii);


	    std::cout<< "Eigenvalues" << eigval << std::endl;

	}



	catch(std::exception &e)
	{
		std::cout << "EXCEPTION: " << e.what();
	}



	return 0;
}

