/*./ex2b
Update pointer to the next point in the same quarter (struct&linked-list)
=============================================
      Written by : Eliachar Feig. ID: 302278338
=============================================
This program is using struct to build a linked-list of points, which every place in
the linked-list contains 2 integer (x, y). Once the list is built, a function gets the
head of this list and pass on the list and every point update a pointer to point
on the next point in the list which is in the same quarter.
In the end, a function prints every point (in order) and the next point in the
same quarter (that the updated pointer _next_same_quarter), if there isn’t a point
in the same quarter it prints 0 0 (and the the update pointer point to NULL at this
place.
Input: integer numbers (until end of file (!cin.eof())
Output: The list with the updated pointer..
g++ -Wall ex2b.cc -o ex2b
*/
#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;

struct Point
{
	double _x, _y;
};
struct Node
{
	struct Point _data;
	struct Node * _next,
		        *_next_same_quarter;
};
//------------------------------------------------
struct Node *read_points(struct Node *&head);
void read_a_point(struct Node *&head, struct Node *&tail,
		          double &x, double &y);
void sort_in_quarters(struct Node *&head);
void print(const struct Node *head);
void free_list(struct Node *head);
//--------------------------------------------
int main()
{
	struct Node *head = NULL;
	head = read_points(head);
	if (head != NULL)
	{
	sort_in_quarters(head);
	print(head);
	cout << "0" << " " << "0" << " " << endl;
	}
	free_list(head);

	return EXIT_SUCCESS;
}
//--------------------------------------
struct Node *read_points(struct Node *&head)
{ // reads points from the user, receive head, return head
	struct Node *tail = NULL;
	double x, y;
	cin >> x;
	cin >> y;
	while (!cin.eof())
	{
		read_a_point(head, tail, x, y); // reads single point
	}
	return head;
}
//---------------------------------------------
void read_a_point(struct Node *&head, struct Node *&tail,
		          double &x, double &y)
{ // reads single point, receive by reference x, y, tail
	struct Node *temp = new(nothrow) struct Node;
	if (temp == NULL)
	{
		cerr << "Cannot allocate memory...\n";
		exit(EXIT_SUCCESS);
	}
	temp->_data._x = x;
	temp->_data._y = y;
	temp->_next = NULL;
	if (head == NULL)
	{
		tail = temp;
		head = temp;
	}
	else
	{
		tail->_next = temp;
		tail = temp;
	}
	cin >> x;
	cin >> y;
}
//-------------------------------------------
void sort_in_quarters(struct Node *&head)
{ // update the pointer to point for every point to the next
// in the list that in the same quarter and print, receive head
	bool found = false;
	while (head->_next != NULL)
	{
		struct Node *head_temp = head;
		if (head->_data._x > 0 && head->_data._y > 0)//1st quarter
		{
			print(head);
			while (head_temp->_next != NULL)
			{
				head_temp = head_temp->_next;
				if (head_temp->_data._x > 0 && head_temp->_data._y > 0)
				{
					head_temp->_next_same_quarter = head;//update
					cout << head_temp->_data._x << " "
							<< head_temp->_data._y << " ";
					found = true; break;
				}
			}
			if (head_temp->_next == NULL && !found)
			{ cout << "0" << " " << "0 " ; }
		}
		if (head->_data._x < 0 && head->_data._y > 0)//2nd quarter
		{
			print(head);
			while (head_temp->_next != NULL)
			{
				head_temp = head_temp->_next;
				if (head_temp->_data._x < 0 && head_temp->_data._y > 0)
				{
					head_temp->_next_same_quarter = head;//update
					cout << head_temp->_data._x << " "
							<< head_temp->_data._y << " ";
					found = true; break;
				}
			}
			if (head_temp->_next == NULL && !found)
			{ cout << "0" << " " << "0 "; }
		}
		if (head->_data._x < 0 && head->_data._y < 0)// 3rd quarter
		{
			print(head);
			while (head_temp->_next != NULL)
			{
				head_temp = head_temp->_next;
				if (head_temp->_data._x < 0 && head_temp->_data._y < 0)
				{
					head_temp->_next_same_quarter = head;//update
					cout << head_temp->_data._x << " "
							<< head_temp->_data._y << " ";
					found = true; break;
				}
			}
			if (head_temp->_next == NULL && !found)
			{ cout << "0" << " " << "0 "; }
		}
		if (head->_data._x > 0 && head->_data._y < 0)// 4th quarter
		{
			print(head);
			while (head_temp->_next != NULL)
			{
				head_temp = head_temp->_next;
				if (head_temp->_data._x > 0 && head_temp->_data._y < 0)
				{
					head_temp->_next_same_quarter = head;//update
					cout << head_temp->_data._x << " "
							<< head_temp->_data._y << " ";
					found = true; break;
				}
			}
			if (head_temp->_next == NULL && !found)
			{ cout << "0" << " " << "0 " ; }
		}
		found = false;
		head_temp = head_temp->_next_same_quarter;
		head = head->_next;
	}
}
//------------------------------------------
void print(const struct Node *head)
{// print, receive head
	if (head != NULL)
	{	cout << head->_data._x << " " << head->_data._y << " "; }
}
//-------------------------------------------------
void free_list(struct Node *head)
{// free list
	struct Node *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->_next;
        delete temp;
	}
}


