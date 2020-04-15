#pragma once

/*
* \brief Filters the input 2D array according to input parameters.
*
* @param [in] {int} NumberOfNodes - the number of nodes on each axis of the grid
* @param [in] {float**} Arr_input - array to filter
* @param [in] {float*} X - array of coordinate axis values
* @param [in] {float*} Y - array of coordinate axis values
* @param [in] {float} P_input1 - bottom parameter of the filter
* @param [in] {float} P_input2 - top parameter of the filter
*/

class Filter {

private:
	float** Arr_input;
	float P_input1;
	float P_input2;
	float* X;
	float* Y;
	int NumberOfNodes;

public:
	Filter(int, float**, float*, float*, float, float);
	void EdgeShift(float);
	bool** getFilterArray2D();
	void writeFilterArray2txt(bool**);
	~Filter();
};

