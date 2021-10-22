/* ./ex3c
  Biggest under tree with sequence order
  ==============================================
  Written by : Eliachar Feig. ID: 302278338
  ==============================================
  This program is building a binary tree of points sorted by order of the
  input, reading integers from the user. The program is checking the
  biggest under tree that it childs are put in order (+1 in the ID for the
  child of each section cross.
  a function that return a pointer to the head of the under tree that all the
  sections underness fit the condition.
  Input: integers until eof.
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


struct Node
{
	int _id;
	int _data;
	struct Node *_left,
		        *_right;
};
//------------------------------------------------
void build_tree(struct Node *&root);
void insert_into_tree(struct Node *temp_node, struct Node *&root);
struct Node*return_deepest(struct Node *root, struct Node *deepest_und_tree,
	                        int &depth);
bool look_for_deepest(struct Node *root, struct Node *&deepest_und_tree,
	                  int &curr_nod, int &nodes);
void free_tree(struct Node *root);
//------------------------------------------------------------------
int main()
{
	struct Node *root = NULL,
		        *deepest_und_tree = NULL;
	int depth ;// the depth of the under tree that will return
	build_tree(root);
	deepest_und_tree = return_deepest(root, deepest_und_tree, depth);
	cout << deepest_und_tree->_id << " "
			<< deepest_und_tree->_data << " "  << depth  <<endl;
	free_tree(root);

	return EXIT_SUCCESS;
}
//---------------------------------------------------------
void build_tree(struct Node *&root)
{// the function is building the binary tree sorted by order of the input
	// it receive by reference root
	int num, id_num = 1;
	cin >> num;
	while (!cin.eof())
	{
		struct Node *temp_node = new(nothrow) struct Node;
		if (temp_node == NULL)
		{
			cerr << "Cannot allocate memory...\n";
			exit(EXIT_FAILURE);
		}
		temp_node->_id = id_num;//save current id
		temp_node->_data = num;//save num
		temp_node->_left = temp_node->_right = NULL;//(re)set the childs

		insert_into_tree(temp_node, root);// calling function
		id_num++;
		cin >> num;//next input
	}
}
//-----------------------------------------------------
void insert_into_tree(struct Node *temp_node, struct Node *&root)
{// insert the data
	if (root == NULL)
		root = temp_node;
	else
		if (root->_data >= temp_node->_data)
			insert_into_tree(temp_node, root->_left);//recursive
		else
			insert_into_tree(temp_node, root->_right);//recursive
}
//------------------------------------------------------
struct Node *return_deepest(struct Node *root, struct Node *deepest_und_tree,
	                         int &depth)
{//this function is the holder of the next function (maatefet)
	// it receive the root, a pointer which will be updated to point on the
	//biggest under tree that fit the condition, and an integer (by reference)
	//that will be updated to save the depth of the longest under tree that
	//fit. The function return the head of the pointer
	int nodes = 0;
	int  curr_nod;
	look_for_deepest(root, deepest_und_tree, curr_nod, nodes);//calling
	depth = nodes;
	return deepest_und_tree;
}
//-------------------------------------------------------------
bool look_for_deepest(struct Node *root, struct Node *&deepest_und_tree,
	                  int &curr_nod, int &nodes)
{//The main function that check for the biggest. it uses recursion (pre-order)
	//when finds it saves the correct data
	// It receive the root, thae pointer that will point to the head of the
	//biggest under tree that fit (by reference), 2 integers (by refernce) to
	// check for the biggest.
	int nod_left, nod_right;
	bool left_ok, right_ok;
	if (root == NULL)
	{
		curr_nod = 0;
		return true;
	}
	left_ok = look_for_deepest(root->_left, deepest_und_tree,
			                   nod_left, nodes);//recursive left
	right_ok = look_for_deepest(root->_right, deepest_und_tree,
			                    nod_right, nodes); // recursive right

	if (left_ok && right_ok)
	{
		if (root->_left != NULL && root->_right == NULL)
		{
			if (root->_id == (root->_left->_id - 1))
				  curr_nod = nod_left + 1;
			else curr_nod = 1;
		}
		else if (root->_right != NULL && root->_left == NULL)
		{
			if (root->_id == (root->_right->_id - 1))
			     curr_nod = nod_right + 1;
			else curr_nod = 1;
		}
		else if (root->_right != NULL && root->_left != NULL)
		{
			if (root->_id == (root->_left->_id - 1))
				curr_nod = nod_left + 1;
			 if (root->_id == (root->_right->_id - 1))
				curr_nod = nod_right + 1;
			 if (root->_id != (root->_left->_id - 1)
					 && root->_id != (root->_right->_id - 1))
				 curr_nod = 1;
		}
		else
		{ curr_nod = 1;	}

		if (curr_nod > nodes)//if biggest under tree that fit conditions
		{
		  deepest_und_tree = (Node*)root;//point to the head of the under-tree
		  nodes = curr_nod;//save for later check
		}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------
void free_tree(struct Node *root)
{// free the allocated memory
	if (root != NULL)
	{
		free_tree(root->_left);
		free_tree(root->_right);
		delete root;
	}
}
