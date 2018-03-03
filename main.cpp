/*
 * main.cpp
 *
 *  Created on: 09.02.2018
 *      Author: Flo
 */
#include<iostream>
#include<kfract.h>

#define KFRACT_BASE_CONST 1

int main(int args, char * argv[])
{
	kfract * koch_fractal_1 = new kfract(20,KFRACT_BASE_CONST,4);

	int g = koch_fractal_1->get_level();

	std::cout << "kfract_level: " << g << std::endl;

	return 0;
}

