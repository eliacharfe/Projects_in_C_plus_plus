/* ./ex1b
 * Split sentences to words (dynamic + pointers + struct)
 * =====================================================
 *          Written by: Eliachar Feig. ID: 302278338
 * =====================================================
 * This program reads from the user how many sentences he wants to insert,
 * then reads the sentences. The program use struct data, and insert the
 * sentences into it, then counts the number of spaces there are in the
 * sentences and make a new struct data with the number of spaces(num of
 * rows in the new array of pointers). In the end insert each word in a
 * new line in the new array.
 * Input: number of sentences + sentences.
 * Output: the new array of words
 */
#include <iostream>
#include <new>
#include <cctype>
#include <cstring>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::nothrow;

const int MAX_STR_LEN = 1000;
//---------------------------------------------------
struct Sentences
{
	char **_data;
	int _num_of_sentences;
};
//--------------------------PROTOTYPES------------------
void read_num_sentences(struct Sentences &s);
void alloc_data_row_col(struct Sentences &s);
char **split_to_words(struct Sentences &s, int &num_of_words);
void print(char **words, int num_of_words);
void free(char **words, int num_of_words);
void error();
//-------------------------------------------------------
int main()
{
	struct Sentences s;
	read_num_sentences(s);
	alloc_data_row_col(s);

	int num_of_words = 0;
	char **words = split_to_words(s, num_of_words);
	print(words, num_of_words);
	free(words, num_of_words);

	return EXIT_SUCCESS;
}
//------------------------------------------------------
void read_num_sentences(struct Sentences &s)
{
	cin >> s._num_of_sentences;
	cin.get();
}
//----------------------------------------------------------------
void alloc_data_row_col(struct Sentences &s)
{
	s._data = new(nothrow) char *[s._num_of_sentences];
	if (s._data == NULL)
	{ error(); }

	for (int index_row = 0; index_row < s._num_of_sentences; index_row++)
	{
		s._data[index_row] = new(nothrow) char [MAX_STR_LEN];
		cin.getline(s._data[index_row], MAX_STR_LEN);
		if (s._data[index_row] == NULL)
		{ error(); }
	}
}
//-------------------------------------------------------------
char **split_to_words(struct Sentences &s, int &num_of_words)
{
	for (int row = 0; row < s._num_of_sentences; row++)
	{
		for (unsigned int col = 0; col < strlen(s._data[row]); col++)
		{
			char c = s._data[row][col];
			if (c == ' ')
			{ num_of_words++; }
		}
	}
	char **new_data = new(nothrow) char *[num_of_words];
	if (new_data == NULL)
	{ error(); }
	for (int row = 0; row < s._num_of_sentences; row++)
	{
		new_data[row] = new(nothrow) char[strlen(s._data[row])];
		{
			new_data[row][strlen(s._data[row])] = '\0';
			strcpy(new_data[row], s._data[row]);
			delete[] s._data[row];
			//cout << new_data[row] << endl;
		}
	}
	return new_data;
}
//-------------------------------------------------
void print(char **words, int num_of_words)
{
	for (int row = 0; row < num_of_words ; row++)
	{
		char *temp;
		temp = strtok(words[row], " ");
		while (temp != NULL)
		{
			cout << temp << endl;
			temp = strtok(NULL, " ");
		}
		delete[] temp;
	}
}
//----------------------------------------------------
void error()
{
	cerr << "Cannot allocate memory\n";
	exit(EXIT_FAILURE);
}
//-------------------------------------------
void free(char **words, int num_of_words)
{
	for (int row = 0; row < num_of_words; row++)
	{
		delete[] words[row];
	}
	delete[] words;
}
//------------------------------------------------
/*
aaaa iiib oop
bbb ffu jjjjjjjjj nn m
cc rrrrr thdy kk
dd hhhh v
eeee 887 fjj !!o{} 6g eeee

*/



