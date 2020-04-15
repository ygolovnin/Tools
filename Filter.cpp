#include "Filter.h"
#include <vector>
#include <iostream>
#include <fstream>




Filter::Filter(int NON, float** R_c_grid, float* X_grid, float* Y_grid, float P1, float P2) {
	Arr_input = R_c_grid;
	X = X_grid;
	Y = Y_grid;
	P_input1 = P1;
	P_input2 = P2;
	NumberOfNodes = NON;
}


/*
* Finds the edge between the values at the nodes and -1 and shifts this edge by sqrt(eps),
* reducing the length of the border.
*
* @param [in] {float} epsilon - square of the distance the edge will be shifted
*/

void Filter::EdgeShift(float epsilon) {
	float eps = epsilon;

	/*vector of coordinates of the edge*/
	std::vector <int> EdgeIJ; 
	
	/*find initial point*/
	int i_enter = NumberOfNodes / 2;
	int j_enter = 0;
	for (int j = 0; j < NumberOfNodes / 2; ++j) {
		if (Arr_input[i_enter][j] != -1) {
			j_enter = j;
			EdgeIJ.push_back(i_enter);
			EdgeIJ.push_back(j_enter);
			break;
		}
	}
	int counter = 0;
	/*initializing EdgeXY*/
	bool check = true;
	int i_curr = i_enter;
	int j_curr = j_enter;
	int i_edge = 0;
	int j_edge = 0;
	while (check) {
		if ((Arr_input[i_curr - 1][j_curr - 1] == -1) && (Arr_input[i_curr - 1][j_curr] >= 0)) {
			i_edge = i_curr - 1;
			j_edge = j_curr;
			counter = 1;
		}
		else if ((Arr_input[i_curr - 1][j_curr] == -1) && (Arr_input[i_curr - 1][j_curr + 1] >= 0)) {
			i_edge = i_curr - 1;
			j_edge = j_curr + 1;
			counter = 2;
		}
		else if ((Arr_input[i_curr - 1][j_curr + 1] == -1) && (Arr_input[i_curr][j_curr + 1] >= 0)) {
			i_edge = i_curr;
			j_edge = j_curr + 1;
			counter = 3;
		}
		else if ((Arr_input[i_curr][j_curr + 1] == -1) && (Arr_input[i_curr + 1][j_curr + 1] >= 0)) {
			i_edge = i_curr + 1;
			j_edge = j_curr + 1;
			counter = 4;
		}
		else if ((Arr_input[i_curr + 1][j_curr + 1] == -1) && (Arr_input[i_curr + 1][j_curr] >= 0)) {
			i_edge = i_curr + 1;
			j_edge = j_curr;
			counter = 5;
		}
		else if ((Arr_input[i_curr + 1][j_curr] == -1) && (Arr_input[i_curr + 1][j_curr - 1] >= 0)) {
			i_edge = i_curr + 1;
			j_edge = j_curr - 1;
			counter = 6;
		}
		else if ((Arr_input[i_curr + 1][j_curr - 1] == -1) && (Arr_input[i_curr][j_curr - 1] >= 0)) {
			i_edge = i_curr;
			j_edge = j_curr - 1;
			counter = 7;
		}
		else if ((Arr_input[i_curr][j_curr - 1] == -1) && (Arr_input[i_curr - 1][j_curr - 1] >= 0)) {
			i_edge = i_curr - 1;
			j_edge = j_curr - 1;
			counter = 8;
		}

		EdgeIJ.push_back(i_edge);
		EdgeIJ.push_back(j_edge);
		i_curr = i_edge;
		j_curr = j_edge;

		counter = 0;

		if ((i_edge == i_enter) && (j_edge == j_enter)) {
			check = false;
		}
	}


	/*shifting the edge and filling -1*/
	for (int i = 0; i < NumberOfNodes; ++i) {
		for (int j = 0; j < NumberOfNodes; ++j) {
			for (int k = 0; k < EdgeIJ.size() - 1; k += 2) {
				if (((X[i] - X[EdgeIJ[k]]) * (X[i] - X[EdgeIJ[k]]) + (Y[j] - Y[EdgeIJ[k + 1]]) * (Y[j] - Y[EdgeIJ[k + 1]])) < eps) {
					Arr_input[i][j] = -1;
				}
			}
		}
	}
	return;
}

/*
* Creates a bool 2D array from the original array according the input parameters,
*if the value of an element agrees with the conditions, then element 1, if it does not agree, then 0.
*
* @return {bool**} FilterArray2D - array after filtering
*/

bool** Filter::getFilterArray2D() {

	/*2D dynamic array for Mask*/
	bool** FilterArray2D = new bool*[NumberOfNodes];
	for (int i = 0; i < NumberOfNodes; ++i)
		FilterArray2D[i] = new bool[NumberOfNodes];

	for (int i = 0; i < NumberOfNodes; ++i) {
		for (int j = 0; j < NumberOfNodes; ++j) {
			if ((Arr_input[i][j] >= P_input1) && (Arr_input[i][j] <= P_input2)) {
				/*filling of the Mask*/
				FilterArray2D[i][j] = 1;
			}
			else {
				FilterArray2D[i][j] = 0;
			}
		}
	}
	return FilterArray2D;
}

/*
* Write result of function getFilterArray2D in the .txt file.
* 
*@param [in] {bool**} Arr - result of function getFilterArray2D
*/

void Filter::writeFilterArray2txt(bool** Arr) {
	std::ofstream out("FilterArray2D.txt", std::ofstream::out);
	for (int i = 0; i < NumberOfNodes; ++i) {
		for (int j = 0; j < NumberOfNodes; ++j) {
			out << Arr[i][j];
		}
	}
	return;
}

Filter::~Filter() {
	std::cout << "Kill filter" << std::endl;
}
