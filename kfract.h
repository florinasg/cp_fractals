/*
 * kfract.h
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#include <armadillo>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <random>



#ifndef KFRACT_H_
#define KFRACT_H_

class kfract {

public:
	kfract();
	kfract(int Level_final, double Kfract_const, int Kfract_vector_L, int l_max);

	virtual ~kfract();

	/*construt_kfract gets called recursively*/
	int construct_kfract();

	int compute_eigenvalues();


	int get_level();

	int export_kfract_data();

	int tag_grid();

	int export_grid_data();

	int export_EIGENMODE();





	std::vector<std::vector<double>> get_kfract_fractal();



private:
	int level_final;
	int level_current;
	double kfract_const;
	int kfract_vector_L;
	double kfract_const_init;
	int grid_vector_num;

	int l_max;

	double kfract_grid_constant;

	std::vector<std::vector<double>> kfract_grid;

	//pointer to fractal_array
	std::vector<std::vector<double>> kfract_fractal;
	//int  (*kfract_fractal)[2];

	arma::vec eigval;
	arma::mat eigvec;

};

#endif /* KFRACT_H_ */
