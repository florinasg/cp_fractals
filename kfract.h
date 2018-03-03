/*
 * kfract.h
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#ifndef KFRACT_H_
#define KFRACT_H_

class kfract {
public:
	kfract();
	kfract(int Level_final, int Kfract_const, int Kfract_vector_L);

	virtual ~kfract();

	/*construt_kfract gets called recursively*/
	int construct_kfract();
	int get_level();




private:
	int level_final;
	int level_current;
	int kfract_const;
	int kfract_vector_L;
	//pointer to fractal_array
	int  (*kfract_fractal)[2];

	static double fract_inital_struct;
	static double fract_step_struct;

};

#endif /* KFRACT_H_ */
