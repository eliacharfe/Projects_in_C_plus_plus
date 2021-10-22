/* ./ex2b
* Count Middles (linked-list)
=============================================
      Written by : Eliachar Feig. ID: 302278338
=============================================
This program is building a linked-list (of integers), then count how many
digits there are which are bigger from their previous digit in the
linked-list and at the same time are smaller from the the number in
the next place in the list. The program return the counter.
Input: integer numbers (until end of file (!cin.eof())
Output: counter
g++ -Wall ex2a.cc -o ex2a
 */
#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;

struct Numbers
{
	int _data;
    struct Numbers *_next;
};
//--------------------------PROTOTYPES------------------
struct Numbers *insert();
int count_middles(struct Numbers *head);
void free_list(struct Numbers *head);
//---------------------------------------------------
int main()
{
	struct Numbers *head = NULL;
	head = insert();
	int counter_mid = count_middles(head);
	if (head != NULL)
	{
	cout << counter_mid << endl;
	}
	free_list(head);

	return EXIT_SUCCESS;
}
//-------------------------------------------------
struct Numbers *insert() // building linked-list
{ // build list and return the head pointer, receive nothing, return pointer
	// to the head
	struct Numbers *head = NULL;
	struct Numbers *tail = NULL;
	int num;
	cin >> num;
	while (!cin.eof())
	{
		struct Numbers *temp = new(nothrow) struct Numbers;
		if (temp == NULL)
		{
			cerr << "Cannot allocate memory...\n";
			exit(EXIT_FAILURE);
		}
		temp->_data = num;
		temp->_next = NULL;
		if (head == NULL)
		{
			head = tail = temp;
		}
		else
		{ tail->_next = temp;
		  tail = temp;
		}
		cin >> num;
	}
	return head;
}
//------------------------------------------------
int count_middles(struct Numbers *head)
{ // counts the numbers that are in the correct conditions, recive head,
	// return counter
	struct Numbers *prev = NULL;
	struct Numbers *curr = NULL;
	struct Numbers *after = NULL;
	int counter = 0;

	prev = head;
	curr = prev->_next;
	after = curr->_next;
	if (prev->_data < curr->_data)// for the 1st member
		counter++;

	while (after != NULL)
	{
		if (prev->_data < curr->_data && curr->_data < after->_data)
		{
			 counter++; // if conditions are correct
		}
		curr->_next = after;
		prev = curr;
		curr = after;
		after = after->_next;
	}
	if (prev->_data < curr->_data)//for the last member
		counter++;
	return counter;
}
//--------------------------------------------------
void free_list(struct Numbers *head)
{// free the head pointer
	struct Numbers *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->_next;
        delete temp;
	}
}



