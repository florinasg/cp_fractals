/*
 * kfract.h
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#include <vector>


#ifndef KFRACT_H_
#define KFRACT_H_

class kfract {

public:
	kfract();
	kfract(int Level_final, double Kfract_const, int Kfract_vector_L);

	virtual ~kfract();

	/*construt_kfract gets called recursively*/
	int construct_kfract();

	int compute_eigenvalues();

	int get_level();

	int export_kfract_data();
	
	int tag_grid();
	
	int export_grid_data();
	
	
	std::vector<std::vector<double>> get_kfract_fractal();



private:
	int level_final;
	int level_current;
	double kfract_const;
	int kfract_vector_L;
	double kfract_const_init;
	int grid_vector_num;
	
	
	double kfract_grid_constant;
	
	std::vector<std::vector<double>> kfract_grid;
	
	//pointer to fractal_array
	std::vector<std::vector<double>> kfract_fractal;
	//int  (*kfract_fractal)[2];

	static double fract_inital_struct;
	static double fract_step_struct;

};

#endif /* KFRACT_H_ */
