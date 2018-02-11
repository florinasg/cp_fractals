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
	kfract(int Level, int Kfract_const);

	virtual ~kfract();

	int construct_kfract(int Level);
	int get_level();
	void set_level(int new_level);


private:
	int level;
	int kfract_const;
	//pointer to fractal_array
	int  (*kfract_fractal)[4];
};

#endif /* KFRACT_H_ */
