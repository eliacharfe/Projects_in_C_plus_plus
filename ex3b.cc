/* ./ex3b
  Biggest under tree of same quarter
  ==============================================
  Written by : Eliachar Feig. ID: 302278338
  ==============================================
  This program is building a binary tree of points sorted by ID, then calling
  a function that return a pointer to the head of the under tree that all the
  points underness it are in the same quarter as the head point of the under
  tree.
  if doesnt find return 0 0 .
  Input: ID (of a point), x coordinate, y coordinate.
  Output: The head of the pointer that point to the biggest under tree that
  fit the conditions
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
	int _id, _qurter_id;
	struct Point * _data;
	struct Node *_left,
		        *_right;
};
//------------------------------------------------
struct Node *build_tree(struct Node *&root, struct Node &id);
void read_a_point(struct Node *&root, double &x, double &y,
		          struct Node &id, int id_num);
void check_qurter(double x, double y, struct Node &id);
void insert_into_tree(struct Node *temp_node, struct Node *&root);
struct Node *retun_biggest(const struct Node *root, struct Node *big_under);
bool biggest_under_tree(const struct Node *root, struct Node *&big_under,
	                   int &counter, int &counter_prev, bool wrong);
void free_tree(struct Node *root);
//------------------------------------------------------------------
int main()
{
	struct Node id;
	struct Node *root = NULL,
                *big_under = NULL;
	root = build_tree(root, id);
	big_under = retun_biggest(root, big_under);
	cout << big_under->_data->_x << " " << big_under->_data->_y << endl;
	free_tree(root);

	return EXIT_SUCCESS;
}
//---------------------------------------------------------
struct Node *build_tree(struct Node *&root, struct Node &id)
{//function reads the points in loop by calling read_a_point
	int id_num;
	double x, y;
	cin >> id_num;
	cin >> x;
	cin >> y;
	while (!cin.eof())
	{
		read_a_point(root, x, y, id, id_num);
		cin >> id_num;
		cin >> x;
		cin >> y;
	}
	return root;
}
//---------------------------------------------------------
void read_a_point(struct Node *&root,double &x, double &y,
		          struct Node &id, int id_num)
{// reads one point
	check_qurter(x,  y, id);// checking in which quarter the point is
	struct Node *temp_node = new(nothrow) struct Node;
	temp_node->_data = new(nothrow) struct Point;
	if (temp_node == NULL)
	{
		cerr << "Cannot allocate memory...\n";
		exit(EXIT_FAILURE);
	}
	temp_node->_id = id_num;//save current id
	temp_node->_qurter_id = id._qurter_id;//save current quarter of the point
	temp_node->_data->_x = x;//save x
	temp_node->_data->_y = y;//save y
	temp_node->_left = temp_node->_right = NULL;//(re)set the childs

	insert_into_tree(temp_node, root);// calling function
}
//-------------------------------------------------------------
void insert_into_tree(struct Node *temp_node, struct Node *&root)
{// insert the point
	if (root == NULL)
		root = temp_node;
	else
		if (root->_id >= temp_node->_id)
			insert_into_tree(temp_node, root->_left);
	    else
		    insert_into_tree(temp_node, root->_right);
}
//--------------------------------------------------------------
struct Node *retun_biggest(const struct Node *root, struct Node *big_under)
{// return the pointer to the biggest under tree that all the points are
	//in same quarter
	int counter = 0, counter_prev = 0;
	bool wrong = false;
	biggest_under_tree(root, big_under, counter, counter_prev, wrong);
	if (counter == 0)
	{	cout << "0 0" << endl;
	    exit(EXIT_FAILURE);}
	return big_under;//return the pointer
}
//------------------------------------------------------------------
bool biggest_under_tree(const struct Node *root, struct Node *&big_under,
	                    int &counter, int &counter_prev, bool wrong)
{
	int counter_left, counter_right ;
	bool left_ok, right_ok;
	if (root == NULL)
	{
		counter = 0;
		return true;
	}
	left_ok = biggest_under_tree(root->_left, big_under, counter_left,
		counter_prev, wrong);//recursive left
	right_ok = biggest_under_tree(root->_right, big_under, counter_right,
		counter_prev, wrong); // recursive right

	if (left_ok && right_ok)// if both return true
	{
		if (root->_left != NULL && root->_right != NULL
			&& root->_left->_qurter_id != root->_right->_qurter_id)
				wrong = true; //not good
		else if (root->_left == NULL && root->_right != NULL
			&& root->_qurter_id != root->_right->_qurter_id)
		      wrong = true;//not good
		else if	(root->_left != NULL && root->_right == NULL
			     && root->_qurter_id != root->_left->_qurter_id)
			   wrong = true;//not good

		counter = counter_left + counter_right + 1;//sum
			if (counter > counter_prev && !wrong)
			{
				big_under = (Node*)root;//save the biggest
				counter_prev = counter; //save
				counter = 0;//reset counter
			}
			wrong = false;//reset boolian
			return true;
		}
		return false;
}
//------------------------------------------------------------
void check_qurter(double x, double y, struct Node &id)
{
	if (x > 0 && y > 0)//1st quarter
		id._qurter_id = 1;
	if (x < 0 && y > 0)//2nd quarter
		id._qurter_id = 2;
	if (x < 0 && y < 0)//3rd quarter
		id._qurter_id = 3;
	if (x > 0 && y < 0)//4th quarter
		id._qurter_id = 4;
}
//-----------------------------------------------------------
void free_tree(struct Node *root)
{
	if (root != NULL)
	{
		free_tree(root->_left);
		free_tree(root->_right);
		delete root;
	}
}

