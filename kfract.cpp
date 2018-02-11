/*
 * kfract.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */

#include "kfract.h"

kfract::kfract() : level(0) , kfract_const(1)
{
	// TODO Auto-generated constructor stub

}

kfract::kfract(int Level, int Kfract_const) : level(Level) , kfract_const(Kfract_const)
{
  kfract_fractal = new int[4][1];
}


kfract::~kfract() {
	// TODO Auto-generated destructor stub
}


int kfract::construct_kfract(int Level)
{

	return 0;
}

int kfract::get_level()
{
	return level;
}


void kfract::set_level(int new_level)
{
	this->construct_kfract(new_level);
	level = new_level;
}


