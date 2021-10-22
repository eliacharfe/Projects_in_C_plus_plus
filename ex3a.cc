/* ./ex3a
  Counts equal left
  ==============================================
  Written by : Eliachar Feig. ID: 302278338
  ==============================================
 This program is building a binary tree. Then send the head (root) to another
 function that counts how many section cross the value in the section is
 equal to the its left child
  Input: serie of integers
  Output: the counter
*/
#include <iostream>
#include <new>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;

struct Node
{
	int _data;
	struct Node *_left,
		        *_right;
};
//------------------------------------------------
void build_tree(struct Node *&root);
void insert_into_tree(struct Node *temp_node, struct Node *&root);
int return_counter(int &counter, struct Node *root);
void count_equals(int &counter, struct Node *&root);
void free_tree(struct Node *root);
//--------------------------------------------
int main()
{
	struct Node *root = NULL;
	int counter = 0;

	build_tree(root);
	cout << return_counter( counter, root) << endl;
	free_tree(root);

	return EXIT_SUCCESS;
}
//--------------------------------------
void build_tree(struct Node *&root)
{// function the build a binary tree by calling a recursive function
	int num;
	cin >> num;
	while (!cin.eof())
	{
		struct Node *temp_node = new(nothrow) struct Node;
		if (temp_node == NULL)
		{
			cerr << "Cannot allocate memory...\n";
			exit(EXIT_FAILURE);
		}
		temp_node->_data = num;
		temp_node->_left = temp_node->_right = NULL;
		insert_into_tree(temp_node, root);

		cin >> num;
	}
}
//---------------------------------------
void insert_into_tree(struct Node *temp_node, struct Node *&root)
{// recursive function insert in order of place in the tree
	if (root == NULL)
		root = temp_node;
	else if (root->_data >= temp_node->_data)
	{
		insert_into_tree(temp_node, root->_left);
	}
	else
		insert_into_tree(temp_node, root->_right);
}
//-------------------------------------------------
int return_counter(int &counter, struct Node *root)
{// calling a recursion function with the parameters
		count_equals(counter, root);
		return counter;
}
//-------------------------------------------------
void count_equals(int &counter, struct Node *&root)
{// recursive func' adding
	if (root == NULL)
		return ;

	else
		if (root->_left != NULL )
		{
			if (root->_data == root->_left->_data)
				counter++;
			count_equals(counter, root->_left);
		}
	if (root->_right != NULL)
		count_equals(counter, root->_right);
}
//-----------------------------------------------
void free_tree(struct Node *root)
{
	if (root != NULL)
	{
		free_tree(root->_left);
		free_tree(root->_right);
		delete root;
	}
}
//-----------------------------------------------------
