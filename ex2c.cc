/* ./ex1c
====================================
Series of dividing (linked-list + struct)
====================================
This program is building a link list 2D array (of pointer) , and getting
from the user numbers in a loop from the user (until he insert 0), and each
number the program calculates the smallest divider which start the line, then
the 1st cell in the row is the smallest divider and the rest is the numbers
that the prime in the first is their smallest divider.

Input: numbers until 0.
Output: the series by order.
g++ -Wall ex2c.cc -o ex2c
 */
#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;

struct Prime_Node
{
	int _prime;
	struct Prime_Node *_next_prime;
	struct Node *_right;
};
struct Node
{
	int _data;
	struct Node *_next;
};
//-----------------------------------------------------------
void build_link_list(struct Node &dat, struct Prime_Node &pri,
		             struct Prime_Node *&head_prime,
	                 struct  Node *&head_right);
int find_lowest_divide(struct Node &datas);
bool check_if_divSerie_exist(struct Prime_Node &pri,
	                         struct Prime_Node *&head_prime);
void start_new_lineSerie(struct Node &dat, struct Prime_Node &pri,
		                 struct Prime_Node **p2head_prime,
	                     struct  Node *&head_right,
						 struct Prime_Node *&temp_prime);
void insert_not_start_of_Serie(struct Node &dat, struct Prime_Node &pri,
	                           struct Prime_Node **p2head_prime,
	                           struct  Node *&head_right,
							   struct Prime_Node *&temp_prime);
void print_list_series(struct Prime_Node **p2head_prime);
void free_list(struct Prime_Node **p2head_prime);
//-------------------------------------------------------------------
int main()
{
	struct Node dat;
	struct Prime_Node pri;
	struct Prime_Node *head_prime = NULL;
	struct Node *head_right = NULL;

	build_link_list(dat, pri, head_prime, head_right);
	print_list_series(&head_prime);
	free_list(&head_prime);

	return EXIT_SUCCESS;
}
//--------------------------------------------
void build_link_list(struct Node &dat, struct Prime_Node &pri,
	                 struct Prime_Node *&head_prime,
					 struct  Node *&head_right)
{// main function that build the list through calling for other functions
	// of checking and insert
	cin >> dat._data;
	while (dat._data != 0)
	{
		struct Prime_Node *temp_prime = new(nothrow) struct Prime_Node;
		if (temp_prime == NULL)
		{
			cerr << "Cannot allocate memory...\n";
			exit(EXIT_FAILURE);
		}
		pri._prime = find_lowest_divide(dat);

			if (!check_if_divSerie_exist(pri, head_prime))
				// if serie dont exist
			{
				start_new_lineSerie(dat, pri, &head_prime, head_right,
						            temp_prime);
			}
			else
			{
				 insert_not_start_of_Serie(dat, pri, &head_prime,
						                   head_right, temp_prime);
			} //if already exist

		cin >> dat._data;
	}
}
//-----------------------------------------------------------------
int find_lowest_divide(struct Node &dat)
{// checking for the smallest divider of the number the user's input
	if (dat._data % 2 == 0)
	{
		return 2;
	}
	for (int div = 3; (div * div) <= dat._data; div += 2)
	{
		if (dat._data % div == 0)
			return div;
	}
	return dat._data;
}
//---------------------------------------------------------
bool check_if_divSerie_exist(struct Prime_Node &pri,
	struct Prime_Node *&head_prime)
{// boolian function return if divider serie exist
	struct Prime_Node *temp_prime = head_prime;
	while (temp_prime != NULL)
	{
		if (temp_prime->_prime == pri._prime)
			return true;
		temp_prime = temp_prime->_next_prime;
	}
	return false;
}
//------------------------------------------------
void start_new_lineSerie(struct Node &dat, struct Prime_Node &pri,
	                     struct Prime_Node **p2head_prime,
						 struct  Node *&head_right,
	                     struct Prime_Node *&temp_prime)
{// starting new row and insert the 1st number in the row and insert the
	// prime number to **
	struct Prime_Node *rear, *front;
	temp_prime->_prime = pri._prime; // pointer to 1st (prime)
	temp_prime->_next_prime = NULL; // insert to ** sorted
	if ((*p2head_prime) == NULL)
	{
		(*p2head_prime) = temp_prime;
		temp_prime->_next_prime = NULL;
	}
	else if (pri._prime <= (*p2head_prime)->_prime)
	{
		temp_prime->_next_prime = (*p2head_prime);
		(*p2head_prime) = temp_prime;
	}
	else
	{
		rear = (*p2head_prime);
		front = rear->_next_prime;
		while (front != NULL && front->_prime <= pri._prime)
		{
			rear = front;
			front = front->_next_prime;
		}
		rear->_next_prime = temp_prime;
		temp_prime->_next_prime = front;
	}
	temp_prime->_right = new(nothrow) struct Node; // 1st data in line
	if (temp_prime->_right == NULL)
	{
		cerr << "Cannot allocate memory...\n";
		exit(EXIT_FAILURE);
	}
	temp_prime->_right->_data = dat._data;
	temp_prime->_right->_next = NULL;
}
//----------------------------------------------------
void insert_not_start_of_Serie(struct Node &dat, struct Prime_Node &pri,
	struct Prime_Node **p2head_prime, struct  Node *&head_right,
	struct Prime_Node *&temp_prime)
{ // if divide serie exist insert the next num in the row
	temp_prime = (*p2head_prime);
	while (temp_prime != NULL)
	{
		if (dat._data % temp_prime->_prime == 0)
		{
			head_right = temp_prime->_right;
			while (head_right->_next != NULL)
			{
				head_right = head_right->_next;
			}
			struct Node *temp = new(nothrow) struct Node;
			if (temp == NULL)
			{
				cerr << "Cannot allocate memory...\n";
							exit(EXIT_FAILURE);
			}
			temp->_data = dat._data;
			temp->_next = NULL;
			head_right->_next = temp;
			break;
		}
		temp_prime = temp_prime->_next_prime;
	}
}
//-------------------------------------------------
void print_list_series(struct Prime_Node **p2head_prime)
{// print the linked list
	struct Prime_Node *temp_prime = (*p2head_prime);
	while (temp_prime != NULL)
	{
		struct Node *curr = temp_prime->_right;
		cout << temp_prime->_prime << " ";
		while (curr != NULL)
		{
			cout << curr->_data << " ";
			curr = curr->_next;
		}
		cout << endl;
		temp_prime = temp_prime->_next_prime;
	}
}
//---------------------------------------------
void free_list(struct Prime_Node **p2head_prime)
{// free the ** pointer
	delete[] (*p2head_prime);
}
