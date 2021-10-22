/* ./ex4a.cc
 * Finding member in 2 sides of link list (generic)
 * ==================================================
 * Written by: Eliachar Feig. ID: 302278338
 *==================================================
 * This program is building a liked list which saving a pointer to point
 * on the the start of the list and a pointer to point on the end of
 * the list. It reading until eof. Then call a generic function each
 * time with the pointer of the head or the pointer to the tail, and send
 * to the litlle functions that finds the first cell from beginning or
 * from the end that suit the conditions according to the exercise.
 * Input : integers unil eof.
 * Output : 6 integers that first suit the conditions
 */
#include <iostream>
#include <cstdlib>
#include <new>

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;
using std::cerr;

struct Node
{
	int _data;
	struct Node *_next,
		        *_prev;
};
enum call_t {F1, F2, F3, F4, F5, F6};
//-------------------------------------------------------
void build_link_list(struct Node *&first, struct Node *&last);
void find_func_ptr(struct Node *pointer, int num);
struct Node *return_next_or_prev_index(struct Node *&pointer, bool &found, int num);
void func_pos(int p2_cell, bool &printed);
void prime(int p2_cell, bool &printed);
void search_palindrom(int p2_cell, bool &printed);
//--------------------------------------------------------
int main()
{
	struct Node *first = NULL;
	struct Node *last = NULL;
	build_link_list(first, last);

	find_func_ptr(first, F1);
	find_func_ptr(last, F2);
	find_func_ptr(first, F3);
	find_func_ptr(last, F4);
	find_func_ptr(first, F5);
	cout << " ";
	find_func_ptr(last, F6);
	cout << endl;

	return EXIT_SUCCESS;
}
//------------------------------------------------------
void build_link_list(struct Node *&first, struct Node *&last)
{
	struct Node *tail = NULL;
		int num;
		cin >> num;
		while (!cin.eof())
		{
			struct Node *temp = new(nothrow) struct Node;
			if (temp == NULL)
			{
				cerr << "Cannot allocate memory...\n";
				exit(EXIT_FAILURE);
			}
			temp->_data = num;
			temp->_next = NULL;
			temp->_prev = last;
			last = temp;
			if (first == NULL)
			{
				first = tail = temp;
			}
			else
			{
				tail->_next = temp;
				tail = temp;
			}
			cin >> num;
		}
}
//----------------------------------------------------------
void find_func_ptr(struct Node *pointer, int num)
{ // generic funcion. get a pointer wich update in the function by calling
	// a second function to be the pointer of first cell or last cell
	// then call the print functions. return nothing.
	bool found = true;
	bool printed = false;
	while (pointer != NULL && !printed)
	{
	struct Node* p2_link = return_next_or_prev_index(pointer, found, num);
		int p2_cell = p2_link->_data;
		if (num == F1 || num == F2)
		{ func_pos(p2_cell, printed);
		}
		if (num == F3 || num == F4)
		{ prime(p2_cell, printed);
		}
		if (num == F5 || num == F6)
		{ search_palindrom(p2_cell, printed);
		}
	}
}
//---------------------------------------------------------
struct Node *return_next_or_prev_index(struct Node *&pointer,
		bool &found, int num)
{ // check if got the pointer of head or of tail. update the pointer and
//return it.get num of function and a boolian(true or false) by reference
	if (num == F1 || num == F3 || num == F5)
	{
		if (pointer->_prev == NULL && found)
			found = false;
		else
			pointer = pointer->_next;
	}
	else {
		if (pointer->_next == NULL && found)
			found = false;
		else
			pointer = pointer->_prev;
	}
	return pointer;
}
//-------------------------------------------------------
void func_pos(int p2_cell, bool &printed)
{ // finds first positive member from start or from last and prints
	// get the pointer to the current cell
	if (p2_cell > 0 && !printed)
	{
		cout << p2_cell << " ";
		printed = true;
	}
}
//-----------------------------------------------------------
void prime(int p2_cell, bool &printed)
{//finds first prime number (>= 2) from beg or from last and prints it
	// get boolian by reference . get the pointer to the current cell.
	bool is_prime = true;
	for (int i  = 2; i <= p2_cell / 2; ++i) {
		if (p2_cell % i == 0) {
			is_prime = false;
			break;
		}
	}
	if (is_prime && !printed && p2_cell >= 2)
	{
		cout << p2_cell << " ";
		printed = true;
	}
}
//-----------------------------------------------------------------
void search_palindrom(int p2_cell, bool &printed)
{// finds the first cell that the number is a palindrome from the beg or
	// from end and prints it. get pointer to current cell.get boolian by ref
	int num, digit, pal = 0;
	num = p2_cell;
	do
	{
		digit = p2_cell % 10;
		pal = (pal * 10) + digit;
		p2_cell = p2_cell / 10;
	} while (p2_cell != 0);
	p2_cell = pal;
	if (num == p2_cell && !printed)
	{
		cout << p2_cell ;
		printed = true;
	}
}
//---------------------------------------------------------
// -3 -1 17 3 -1 3 9 0



