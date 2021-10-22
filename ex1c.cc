/* ./ex1c
====================================
Series of dividing (dynamic arrays + pointers)
====================================
This program is starting with a 2D array with 1 row and 1 column, and getting
from the user numbers in a loop from the user (until he insert 0), and each
number the program calculates the smallest divider which start the line, then
the 2nd cell in the row tells how many column there are (every time there is
no place in the column the program duplicate the number of cells), the 3rd row
tells how many cols are in used. Same thing with the rows, if there is no
empty row and need to start a new line of divider serie, the program duplicate
the number of rows. In the and I use a bubble sort function to put in order
the series from the smallest divider serie to the biggest one, the prints.
Input: numbers in a loop.
Output: the series by order.
*/
#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;
//---------------------------------------------------
struct Divide
{
	int **_arr ;
	int _num;
	int _prime;
	int _size_rows ;
	int _size_rows_used;
	int _size_cols ;
	int _size_cols_used ;
};
//--------------------------PROTOTYPES------------------
void insert_in_array(struct Divide &D);
int find_lowest_divide(struct Divide &D);
bool is_prime(struct Divide &D, int &i);
bool check_if_divSerie_exist(struct Divide &D);
void start_new_lineSerie(struct Divide &D);
void insert_not_start_of_Serie(struct Divide &D);
int duplicate_row(struct Divide &D);
int duplicate_col_newSerie(struct Divide &D);
int duplicate_col_in_usedSerie(struct Divide &D, int row);
void bubble_sort(struct Divide &D);
void print(struct Divide &D);
void free(struct Divide &D);
//--------------------------------------------------
int main()
{
	struct  Divide D;
	insert_in_array(D);
	bubble_sort(D);
	print(D);
	free(D);

	return EXIT_SUCCESS;
}
//-------------------------------------------------
void insert_in_array(struct Divide &D)
{
	D._arr = NULL;
	D._size_rows = 1 ; D. _size_rows_used = 0;
	D. _size_cols = 1 ; D. _size_cols_used = 0 ;
	cin >> D._num;
	D._arr = new (nothrow) int *[D._size_rows];
	*D._arr = new (nothrow) int[D._size_cols];
	while (D._num != 0)
	{
		D._prime = find_lowest_divide(D); // cout << "lowest prime : " << D._prime << endl;
		int i = 2;
		if (is_prime(D, i)) // prime num
		{
			if (!check_if_divSerie_exist(D)) // if serie dont exist
			{ start_new_lineSerie(D);
			}
			else { insert_not_start_of_Serie(D); } //if already exist
		}
		else //not prime
		{
			if (!check_if_divSerie_exist(D))// if serie dont exist
			{ start_new_lineSerie(D);
			}
			else { insert_not_start_of_Serie(D); } //if already exist
		}
		cin >> D._num;
	}
}
//--------------------------------------------------
int find_lowest_divide(struct Divide &D)
{
	if (D._num % 2 == 0) { return 2; }
	for (int div = 3; (div * div) <= D._num; div += 2)
	{
		if (D._num % div == 0)
			return div;
	}
	return D._num;
}
//----------------------------------------------------------
bool is_prime(struct Divide &D, int &i)
{
	if (D._num <= 2)
		return (D._num == 2) ? true : false;
	if (D._num % i == 0)
		return false;
	if (i * i > D._num)
		return true;
	i++;
	return is_prime(D, i);
}
//----------------------------------------------------------
bool check_if_divSerie_exist(struct Divide &D)
{
	for (int row = 0; row < D._size_rows_used
		&& (D._arr[row] != NULL); row++)
	{
		if (D._arr[row][0] == D._prime)
			return true;
	}
	return false;
}
//--------------------------------------------------------
void start_new_lineSerie(struct Divide &D)
{
	if (D._size_rows_used == D._size_rows) {
		D._size_rows = duplicate_row(D);
	}
	D._size_cols = 1;
	D._size_cols_used = 0;
	D._arr[D._size_rows_used] = new (nothrow) int[D._size_cols];
	while (D._size_cols < 4)
	{
		D._size_cols = duplicate_col_newSerie(D);
	}
	D._arr[D._size_rows_used] = new (nothrow) int[D._size_cols];
	D._arr[D._size_rows_used][0] = D._prime;//insert prime
	D._size_cols_used++;
	D._arr[D._size_rows_used][1] = D._size_cols_used;//insert size of columns
	D._arr[D._size_rows_used][2] = D._size_cols_used;//size of columns in use
	D._arr[D._size_rows_used][3] = D._num;
	D._size_rows_used++;
	bubble_sort(D);
}
//----------------------------------------------------------
int duplicate_row(struct Divide &D)
{
	int **temp_arr = NULL;
	temp_arr = new(nothrow) int*[D._size_rows * 2];
	for (int i = 0; i < D._size_rows; i++) {
		temp_arr[i] = new(nothrow) int[D._arr[i][1] + 3];
	}
	for (int i = 0; i <= D._size_rows; i++) {
		temp_arr[i] = D._arr[i];
	}
	int size_extra_row = ((D._size_rows *2) - D._size_rows_used);
	for (int row = size_extra_row; row < (D._size_rows * 2); row++) {
		temp_arr[row] = NULL;
	}
	free(D);
	D._arr = temp_arr;
	return (D._size_rows * 2);
}
//----------------------------------------------------
int duplicate_col_newSerie(struct Divide &D)
{
	int *temp_arr = NULL;
	temp_arr = new(nothrow) int[(D._size_cols * 2)];
	for (int i = 0; i <= D._size_cols_used; i++)
	{
		temp_arr[i] = D._arr[D._size_rows_used][i];
		temp_arr[i + 1] = NULL;
	}
	delete[] D._arr[D._size_rows_used];
	D._arr[D._size_rows_used] = temp_arr;
	return (D._size_cols * 2);
}
//------------------------------------------------------
void insert_not_start_of_Serie(struct Divide &D)
{
	for (int row = 0; row <= D._size_rows_used; row++)
	{
		if (D._num % D._arr[row][0] == 0)
		{
			if (D._arr[row][1] == D._arr[row][2])
			{
				D._size_cols = D._arr[row][1];
				D._size_cols_used = D._arr[row][2];
				D._size_cols = duplicate_col_in_usedSerie(D, row);
				D._arr[row][D._size_cols_used + 3] = D._num;
				D._size_cols_used++;
				D._arr[row][1] = D._size_cols;
				D._arr[row][2] = D._size_cols_used;
				break;
			}
			else
			{
				D._size_cols = D._arr[row][1];
				D._size_cols_used = D._arr[row][2];
				D._arr[row][D._size_cols_used + 3] = D._num;
				D._size_cols_used++;
				D._arr[row][1] = D._size_cols;
				D._arr[row][2] = D._size_cols_used;
				break;
			} } }
}
//---------------------------------------------------
int duplicate_col_in_usedSerie(struct Divide &D, int row)
{
	int *temp_arr = NULL;
	temp_arr = new(nothrow) int[(D._size_cols * 2) + 3];
	for (int i = 0; i < D._size_cols_used + 3; i++)
	{
		temp_arr[i] = D._arr[row][i];
		temp_arr[i + 1] = NULL;
	}
	delete[] D._arr[row];
	D._arr[row] = temp_arr;
	return (D._size_cols * 2);
}
//--------------------------------------------------
void bubble_sort(struct Divide &D)
{
	for (int i = 0; i < D._size_rows_used; i++) {
		for (int k = 0; k < D._size_rows_used; k++) {
			for (int j = k + 1; j < D._size_rows_used; j++) {
				if (D._arr[j][0] < D._arr[k][0])
				{
					int *temp = D._arr[j];
					D._arr[j] = D._arr[k];
					D._arr[k] = temp;
				} } } }
}
//----------------------------------------------
void print(struct Divide &D)
{
	cout << D._size_rows << " " << D._size_rows_used << endl;
	for (int i = 0; i < D._size_rows_used; i++)
	{
		for (int j = 0; j < D._arr[i][2] + 3; j++)
		{ cout << D._arr[i][j] << " "; } cout << endl;
	}
}
//---------------------------------------------------------
void free(struct Divide &D)
{
	delete[] D._arr;
}
//---------------------------------------------------
/*
5 7 52 30 15 39 25 625 99 125 55 455 950 765 27 6 21 33 69 123 6 8 76 34 17 37 1369 29 13 139 11 10 0
*/
