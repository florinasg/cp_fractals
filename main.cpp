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
	/*Configures koch fractal*/
	kfract * koch_fractal_1 = new kfract(7,KFRACT_BASE_CONST,4);

	/*Constructs koch fractal*/
	koch_fractal_1->construct_kfract();

	koch_fractal_1->export_kfract_data();

	return 0;
}

