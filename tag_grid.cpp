/*
 * tag_grid.cpp
 *
 *  Created on: 09.04.2018
 *      Author: Florian Anderl
 */

#include "kfract.h"



/*TODO: JORDAN CURVE THEOREM */
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

		/*TAGS all the remaining grid points located on the edge of the fractal with -1*/
		for(int idx = 0; idx < kfract_fractal.size()/2; idx++)
		{

			n = kfract_fractal[idx];
			nplusone = kfract_fractal[idx+1];

			if(idx == kfract_fractal.size()/2-1)
				/* TODO: what is this line ????!!!!!*/
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
			hitcount_offset= hitcount_offset + (kfract_const/kfract_grid_constant);

		}










		/*JORDAN CURVE THEOREM*/

		std::vector<double> current_shaft = {0};
		std::vector<double> running_line = {0};
		int cross_sections = 0;

		int dist = 0;

		/*NB loop boundrary*/
		for(int i = 0; i <= grid_vector_num; i++)
		{
			for(int j = 0; j <=grid_vector_num; j++)
			{

				current_shaft = kfract_grid[j];

				dist = (grid_vector_num)-(j);
				bool current_shaft_status;

				for(int running_idx = j+1; running_idx <= grid_vector_num; running_idx++  )
				{
					running_line = kfract_grid[running_idx];
					if(running_line[2] == -1)
					{
						cross_sections++;
					}
				}


				if((cross_sections%2) != 0)
				{
					kfract_grid[j][2] == 1;
				}

				cross_sections = 0;


			}
		}



	}

	catch(std::exception &e)
	{
		std::cout << "error occurred: " << e.what() << std::endl;
	}

	return 0;
}




/*OLD CODE*/
//std::vector<std::vector<double>>::iterator it;
//		int index;
//		int jdex;
//
//		int jdex_2;
//
//		/*edge_index_vec contains the indices of edge points within kfract_grid*/
//		std::vector<int> edge_index_vec;
//
//		std::cout << "size of kfract_fractl (NB! #double): "<< kfract_fractal.size() << std::endl;
//
//		/*this for loop tags edge points with -1*/
//		for(int jdx=0;jdx<(kfract_fractal.size())/2;jdx++)
//		{
//
//			//std::cout << "vector: " << kfract_fractal.at(jdx).at(0) << " " << kfract_fractal.at(jdx).at(1) << std::endl;
//			std::vector<double> p = {kfract_fractal.at(jdx).at(0),kfract_fractal.at(jdx).at(1), 0};
//			it = std::find(kfract_grid.begin(), kfract_grid.end(), p);
//			index = std::distance(kfract_grid.begin(), it);
//			edge_index_vec.push_back(int(index));
//			/*-1 indicates grid point is located on EDGE of fractal*/
//			kfract_grid[index][2] = -1;
//			//std::cout << "(" << jdx << ")values at index " << index << " "<< kfract_grid[index].at(0) << " " << kfract_grid[index].at(1) << " " << kfract_grid[index].at(2) << std::endl;
//		}
//
//
//		std::vector<double> n;
//		std::vector<double> nplusone;
//
//
//
//
//		int hitcounter = 0;
//		int hitcount_offset = 0;
//
//		/*VERY TRICKY PART COMES HERE*/
//		for(int idx = 0; idx < kfract_fractal.size()/2; idx++)
//		{
//
//
//
//			n = kfract_fractal[idx];
//			nplusone = kfract_fractal[idx+1];
//
//			if(idx == kfract_fractal.size()/2-1)
//				nplusone = kfract_fractal[idx+1] = {0,1};
//
//
//			//			std::cout << "n " << n[0] << " " << n[1] << std::endl;
//			//			std::cout << "nplusone " << nplusone[0] << " " << nplusone[1] << std::endl;
//
//
//			if((n[1]-nplusone[1] == 0) && (n[0] < nplusone[0]))
//			{
//				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
//				hitcounter = 0;
//
//				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
//				{
//					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//					if((kfract_grid[jdx][0]>n[0]) && (kfract_grid[jdx][0] < nplusone[0]) && kfract_grid[jdx][1] == n[1])
//					{
//						hitcounter++;
//						//std::cout <<"hit "<< jdx<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//						kfract_grid[jdx][2] = -1;
//						edge_index_vec.insert(edge_index_vec.begin()+(hitcounter+hitcount_offset), jdx);
//
//
//					}
//				}
//
//
//			}
//
//			else if((n[0]-nplusone[0] == 0) && (n[1] < nplusone[1]))
//			{
//				hitcounter = 0;
//
//				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
//				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
//				{
//					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//					if((kfract_grid[jdx][1]>n[1]) && (kfract_grid[jdx][1] < nplusone[1]) && kfract_grid[jdx][0] == n[0])
//					{
//						hitcounter++;
//						//std::cout <<"hit "<< jdx << kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//						kfract_grid[jdx][2] = -1;
//						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);
//					}
//				}
//
//			}
//
//
//			else if((n[1]-nplusone[1] == 0) && (n[0] > nplusone[0]))
//			{
//				hitcounter = 0;
//
//				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
//				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
//				{
//					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//					if((kfract_grid[jdx][0]<n[0]) && (kfract_grid[jdx][0] > nplusone[0]) && kfract_grid[jdx][1] == n[1])
//					{
//						hitcounter++;
//						//std::cout <<"hit "<< jdx<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//						kfract_grid[jdx][2] = -1;
//						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);
//
//					}
//				}
//
//
//			}
//
//			else if((n[0]-nplusone[0] == 0) && (n[1] > nplusone[1]))
//			{
//
//				hitcounter = 0;
//
//				/*BAD RUNTIME !!! TODO: OPTIMIZE*/
//				for(int jdx = 0; jdx< kfract_grid.size(); jdx++)
//				{
//
//
//					//std::cout << jdx << " " <<kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//					if((kfract_grid[jdx][1]<n[1]) && (kfract_grid[jdx][1] > nplusone[1])&& kfract_grid[jdx][0] == n[0])
//					{
//						hitcounter++;
//						//std::cout <<"hit "<< jdx <<" "<< kfract_grid[jdx][0] << " " << kfract_grid[jdx][1] << std::endl;
//						kfract_grid[jdx][2] = -1;
//						edge_index_vec.insert(edge_index_vec.begin()+(hitcount_offset+hitcounter), jdx);
//					}
//				}
//
//
//			}
//
//
//			/*TODO: FIND GENERIC TERM*/
//			hitcount_offset= hitcount_offset + (kfract_const/kfract_grid_constant);
//
//		}
//
//
//		std::cout << "edge index vector length: "<< edge_index_vec.size() << std::endl;
//
//
//		/*----------------------------------------------------------------------------------*/
//
//		/*TODO FIND NEW BOUNDARY CONDITION for for loop (14.03.2018)
//		 * UPDATE: deleted /2 in every limit condition */
//		for(int idx=0;idx<=(((edge_index_vec.size()))/4); idx++)
//		{
//			int dummy_idx = edge_index_vec[idx];
//
//			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
//			jdex = dummy_idx % (grid_vector_num+1);
//
//			/*grid points UNDER edge point*/
//			for(int jdx=jdex; jdx > 0; jdx=jdx-1)
//			{
//				//std::cout << "VOR " <<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] <<" " << kfract_grid[dummy_idx-jdx][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[dummy_idx-jdx][2] == 0)
//					kfract_grid[dummy_idx-jdx][2] = 1;
//
//				//std::cout << "NACH "<<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] << " " <<kfract_grid[dummy_idx-jdx][2] <<std::endl;
//			}
//
//		}
//
//
//		//std::cout << "RIGHT EDGE" << std::endl;
//
//		/*#2 RIGHT EDGE
//		 * NOTE THE '+1' in the initial value for idx*/
//		for(int idx=(((edge_index_vec.size()))/4)+1;idx<((edge_index_vec.size()))/2; idx++)
//		{
//			int dummy_idx = edge_index_vec[idx];
//
//			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
//			jdex = dummy_idx%(grid_vector_num+1);
//
//			/*floor rounds down value; jdex_2 denotes the current block of coordinates*/
//			jdex_2 = floor(edge_index_vec[idx]/(grid_vector_num+1));
//
//
//
//			/*grid points left of edge point TODO Validate*/
//			for(int jdx=0; jdx < jdex_2; jdx=jdx+1)
//			{
//				//std::cout << "VOR " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] <<" " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] == 0)
//					kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] = 1;
//
//				//std::cout << "NACH "<<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] << " " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//			}
//
//
//			/*grid points RIGHT of the right edge */
//			for(int jdx=jdex_2+1; jdx < grid_vector_num; jdx=jdx+1)
//			{
//				//std::cout << "VOR " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] <<" " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] == 1)
//					kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] = 0;
//
//				//std::cout << "NACH "<<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] << " " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//			}
//
//
//
//		}
//
//		/*NECESSARY SECOND ITERATION OF UPPER EDGE TO UPDDATE FALSELY ASSIGNED VALUES BY FORMER ITERATION OF (14.03.2018)*/
//		for(int idx=0;idx<=(((edge_index_vec.size()))/4); idx++)
//		{
//			int dummy_idx = edge_index_vec[idx];
//
//			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)
//			 * +1 because the first value is also included */
//			jdex = dummy_idx % (grid_vector_num+1);
//
//			/*grid points UNDER edge point*/
//			for(int jdx=1; jdx < (grid_vector_num+1)-jdex; jdx=jdx+1)
//			{
//				//std::cout << "VOR " <<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] <<" " << kfract_grid[dummy_idx-jdx][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[dummy_idx+jdx][2] == 1 )
//					kfract_grid[dummy_idx+jdx][2] = 0;
//
//				//std::cout << "NACH "<<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] << " " <<kfract_grid[dummy_idx-jdx][2] <<std::endl;
//			}
//
//		}
//
//
//
//
//		//std::cout << "LOWER EDGE" << std::endl;
//
//		/*#3 LOWER EDGE (has to redo down area)*/
//		for(int idx=(edge_index_vec.size()/2); idx<=((edge_index_vec.size()))-(edge_index_vec.size()/4); idx++)
//		{
//			int dummy_idx = edge_index_vec[idx];
//			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
//			jdex = dummy_idx % (grid_vector_num+1);
//
//			/*grid points UNDER edge point*/
//			for(int jdx=jdex; jdx > 0; jdx=jdx-1)
//			{
//				//std::cout << "VOR " <<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] <<" " << kfract_grid[dummy_idx-jdx][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[dummy_idx-jdx][2] == 1)
//					kfract_grid[dummy_idx-jdx][2] = 0;
//
//				//std::cout << "NACH "<<kfract_grid[dummy_idx-jdx][0] << " " << kfract_grid[dummy_idx-jdx][1] << " " <<kfract_grid[dummy_idx-jdx][2] <<std::endl;
//			}
//
//
//		}
//
//
//		//std::cout << "LEFT EDGE" << std::endl;
//
//		/*#4 LEFT EDGE (has to redo left area)*/
//		for(int idx=(((edge_index_vec.size()))-(edge_index_vec.size())/4);idx<(edge_index_vec.size());idx++)
//		{
//			int dummy_idx = edge_index_vec[idx];
//
//			/*jdex denotes the distance from the beginning of a new coordinate block (INDEX!!!)*/
//			jdex = dummy_idx%(grid_vector_num+1);
//			/*floor rounds down value; jdex_2 denotes the current block of coordinates*/
//			jdex_2 = floor(edge_index_vec[idx]/(grid_vector_num+1));
//
//
//
//			/*grid points left of edge point TODO Validate*/
//			for(int jdx=0; jdx < jdex_2; jdx=jdx+1)
//			{
//				//std::cout << "VOR " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] <<" " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//
//				/*TODO NB! CONDITION */
//				if(kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] == 1)
//					kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] = 0;
//
//				//std::cout << "NACH "<<kfract_grid[jdex+(jdx*(grid_vector_num+1))][0] << " " << kfract_grid[jdex+(jdx*(grid_vector_num+1))][1] << " " <<kfract_grid[jdex+(jdx*(grid_vector_num+1))][2] <<std::endl;
//			}
//
//
//		}
