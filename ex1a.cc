/* ./ex1a
 * Calculates th sum (Dynamic arrays+pointers)
 * =====================================================
 *          Written by: Eliachar Feig. ID: 302278338
 * =====================================================
 * This program ask from the user how many rows he wants to insert in the
 * 2D array, then in each row ask how many column in the row, then puts
 * number in the row. In the end the program summing all the numbers in the
 * array and return the sum.
 * Input: num of row, num of col (in each)+ insert in cols.
 * Output: sum.
 */
#include <iostream>
#include <cstdlib>
#include <new>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;
//-------------------PROTOTYPES-----------------
void read_data(int **&arr, int num_of_rows);
void exit_error();
int sum_and_print(int **arr, int num_of_rows);
void free(int **arr);
//--------------------------------------------
int main()
{
	int **arr, num_of_rows;
	cin >> num_of_rows;
	arr = new(nothrow) int *[num_of_rows];
	if (arr == NULL)
	{  exit_error(); }

	read_data(arr, num_of_rows);
	cout << sum_and_print(arr, num_of_rows) ;
	free(arr);

	return EXIT_SUCCESS;
}
//--------------------------------------------
void read_data(int **&arr, int num_of_rows)
{
	int num_of_cells;
	for (int row = 0; row < num_of_rows; row++)
	{
		cin >> num_of_cells;
		arr[row] = new(nothrow) int[num_of_cells + 1];
        if (arr[row] == NULL)
		{	exit_error(); }

		arr[row][0] = num_of_cells;
		for (int input = 1; input <= num_of_cells; input++)
		{   cin >> arr[row][input]; }
	}
}
//--------------------------------------------------------
int sum_and_print(int **arr, int num_of_rows)
{
	int sum = 0;
	for (int row = 0; row < num_of_rows; row++)
	{
		int size_of_row = arr[row][0];
		for (int col = 1; col <= size_of_row; col++)
		{
			sum += arr[row][col];
		}
	}
	return sum;
}
//---------------------------------------------------
void exit_error()
{
	cerr << "Cannot allocate memory\n";
	exit(EXIT_FAILURE);
}
//---------------------------------------------------
void free(int **arr)
{
	delete[] arr;
}



