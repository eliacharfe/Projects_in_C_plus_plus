/* ./ex4c.cc
 * Statistic data of students and courses
 * ==================================================
 * Written by: Eliachar Feig. ID: 302278338
 *==================================================
 * This program is reading into struct data of students (id, grades, height)
 * and data to another struct saving data about courses (id, c.points, hours)
 * It saving in a sorted binary tree sorted by id.
 * Then send from the main a generic function 6 times with the correct datas
 * and calculates avarage according to the instructions of the exercise.
 * Input : stud id, grades, height(until id 0) then course id, cred.points,
 * hours of the course.
 * Output : avarage of all stud grades, avarage of the height of studs,
 * avarage of credit points, avarage of hours per course, id of the student
 * that received the highest avarage of grades, the id of the course
 * that have the most numbers of hours.
 */
#include <iostream>
#include <cstdlib>
#include <new>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::nothrow;

const int CLASS_SIZE = 10;
const int NUM_OF_GRADES = 7;
const int NUM_OF_COURSES = 10;
//--------------------------------------------------------
enum bool_t { END_C = -1, END_S = 0, OK = 2, F1, F2 };
//-----------------------------------------------------------
struct Stud {
	int _stud_id;                      // מזהה התלמיד
	int _grades[NUM_OF_GRADES];        // ציוניו של התלמיד
	double _height;                    // גובהו של התלמיד
};
struct Course {
	int _course_id;                             // מזהה הקורס
	double _credit_points;                      //  כמה נ"ז מקנה הקורס
	unsigned int _hours_of_course;              // כמה שעות כולל הקורס
};
struct Node {
	void *_data;
	struct Node *_left, *_right;
};
struct Avarage {
	double _avr;
	int _index_max;
};
struct Variables {
	double _sum;
	double _prev_max  ;
	double _cur_max  ;
	int  _counter , _num , _num2 ,
		_max_grades_stud , _num_of_stud  , _max_hours ;
};
//------------------------------------------------
struct Node *build_bst(void *new_item, bool(*camp_funcc)(void *, void *),
	void(*read_item) (void *, int&), int e_num);
void insert_into_bst(struct Node *&root, void *new_item,
	bool(*camp_funcc)(void *, void *));
void *allocate_stud();
void *allocate_course();
void read_stud(void *p, int &num);
void read_course(void *p, int &num);
bool compare_stud(void *p1, void *p2);
bool compare_course(void *p1, void *p2);
struct Avarage func_ptr(struct Node *root,
	double(*func_name)(void *, struct Avarage&, struct Variables &),
	struct Avarage &avar,
	struct Variables &var);
double avr_studs_grades(void *p, struct Avarage &avar,
	struct Variables &var);
double avr_height_students(void *p, struct Avarage &avar,
	struct Variables &var);
double avr_credits_points(void *p, struct Avarage &avar,
	struct Variables &var);
double avr_hours_courses(void *p, struct Avarage &avar,
	struct Variables &var);
void reset_var(struct Variables &var);
void free_root_stud(struct Node *root_stud);
void free_root_course(struct Node *root_course);
//-----------------------------------------------------------------
int main()
{
	struct Node *root_stud = NULL;
	struct Node *root_course = NULL;

	bool(*camp_funcc)(void *, void *) = &compare_stud;
	void *new_item = allocate_stud();
	void(*read_item) (void *, int&) = &read_stud;
	root_stud = build_bst(new_item, camp_funcc, read_item, F1);

	camp_funcc = &compare_course;
	new_item = allocate_course();
	read_item = &read_course;
	root_course = build_bst(new_item, camp_funcc, read_item, F2);

	struct Avarage avar;
	struct Variables var;
	reset_var(var);
	avar = func_ptr(root_stud, avr_studs_grades, avar, var);
	cout << avar._avr << " ";
	reset_var(var);
	avar = func_ptr(root_stud, avr_height_students, avar, var);
	cout << avar._avr << " ";
	reset_var(var);
	avar = func_ptr(root_course, avr_credits_points, avar, var);
	cout << avar._avr << " ";
	reset_var(var);
	avar = func_ptr(root_course, avr_hours_courses, avar, var);
	cout << avar._avr << " ";
	reset_var(var);
	avar = func_ptr(root_stud, avr_studs_grades, avar, var);
	cout << avar._index_max << " ";
	reset_var(var);
	avar = func_ptr(root_course, avr_hours_courses, avar, var);
	cout << avar._index_max << endl;

    free_root_stud(root_stud);
    free_root_course(root_course);

	return EXIT_SUCCESS;
}
//---------------------------------------------------------------
struct Avarage func_ptr(struct Node *root,
	double(*func_name)(void*, struct Avarage&, struct Variables&),
	struct Avarage &avar,
	struct Variables &var)
{// generic function that send recursively with the correct data and
	//return struct  by reference.
	// Gets the arr of studs or of courses, the function of
	// calculation. struct by ref to save the correct data to print in main.
	if (root != NULL)
	{
		double res;
		avar = func_ptr(root->_left, func_name, avar, var);
		res = func_name(root->_data, avar, var);
		avar = func_ptr(root->_right, func_name, avar, var);
	}
	return avar;
}
//------------------------------------------------------------
double avr_studs_grades(void *root, struct Avarage &avar,
		struct Variables &var)
{//calculates avarage of students and save it in struct and save also
	// id of the student that received the highest avarage of grades.
	// return 2 structs by reference
	struct Stud stu = *(struct Stud*)root;//casting
	var._num2 = stu._stud_id;
	if (var._num2 != END_S)// if id != 0
	{
		var._num_of_stud++;
		for (int j = 0; j < NUM_OF_GRADES
			&& var._num != END_C && var._num2 != END_S; j++)
		{
			var._num = stu._grades[j];
			if (var._num != END_C)// if grade != -1
			{
				var._counter++;
				var._cur_max += stu._grades[j];
			}
		}
		var._cur_max /= var._counter;
		var._sum += var._cur_max;
		if (var._cur_max > var._prev_max)
		{
			var._max_grades_stud = stu._stud_id;
			var._prev_max = var._cur_max;
		}
		var._cur_max = 0;
		var._counter = 0;
		var._num = OK;
		avar._avr = var._sum / var._num_of_stud;//save data
		avar._index_max = var._max_grades_stud;// save data
	}
	return avar._avr;// return double
}
//------------------------------------------------------
double avr_height_students(void *root, struct Avarage &avar,
	struct Variables &var)
{// calculates avarage of students. update 2 structs by reference
	// return double
	struct Stud stu = *(struct Stud*)root;
	var._num = stu._stud_id;
	if (var._num != END_S)
	{
		var._sum += stu._height;
		var._counter++;
	}
	avar._avr = var._sum / var._counter;
	return avar._avr;
}
//--------------------------------------------------------------------
double avr_credits_points(void *root, struct Avarage &avar,
	struct Variables &var)
{// calculates avarage of credit points. update 2 structs Avarage by ref.
	// returns double
	struct Course cour = *(struct Course*)root;//cast
	var._num = cour._course_id;
	if (var._num != END_S)// if id != 0
	{
		var._sum += cour._credit_points;
		var._counter++;

	}
	avar._avr = var._sum / var._counter;// save data
	return avar._avr;//return double
}
//--------------------------------------------------------------
double avr_hours_courses(void *root, struct Avarage &avar,
	struct Variables &var)
{// calculates avarage of hours of courses. update 2 structs Avarage by ref.
	// returns double
	struct Course cour = *(struct Course*)root;//casting
	{
		var._num = cour._course_id;
		if (var._num != END_S)// if id != 0
		{
			var._sum += cour._hours_of_course;
			var._counter++;
			var._cur_max = cour._hours_of_course;
		}
		if (var._cur_max > var._prev_max)
		{
			var._max_hours = cour._course_id;
			var._prev_max = var._cur_max;
			var._cur_max = 0;
		}
	}
	avar._avr = var._sum / var._counter;//save data
	avar._index_max = var._max_hours;//save data
	return avar._avr;//returns  double
}
//-------------------------------------------------------------
struct Node *build_bst(void *new_item, bool(*camp_funcc)(void *, void *),
	void(*read_item) (void *, int&), int e_num)
{// generic function. receive correct data and building a sorted binary tree
	// sorted by id (stud id or course id)
	struct Node *root = NULL;
	int num;
	cin >> num;
	while (num != 0)
	{
		if (e_num == F1)
			new_item = allocate_stud();
		else if (e_num == F2)
			new_item = allocate_course();
		read_item(new_item, num);
		insert_into_bst(root, new_item, camp_funcc);//insert
		cin >> num;
	}
	return root;
}
//---------------------------------------------------
void insert_into_bst(struct Node *&root, void *new_item,
		bool(*camp_funcc)(void *, void *))
{
	if (root == NULL)
	{
		struct Node *temp = new(nothrow) struct Node;
		if (temp == NULL)
		{
			cout << "Cannot allocate memory...";
			exit(EXIT_FAILURE);
		}
		root = temp;
		root->_data = new_item;
		root->_left = root->_right = NULL;
	}
	else {
		if (camp_funcc(new_item, root->_data))//if new_item <= root->_data
		{
			insert_into_bst(root->_left, new_item, camp_funcc);
		}
		else { insert_into_bst(root->_right, new_item, camp_funcc); }
	}
}
//---------------------------------------------------
void *allocate_stud()
{ // allocation a pointer to a struct of student. return pointer
	struct Stud *stu = new(nothrow) struct Stud;//cast
	if (stu == NULL)
	{
		cerr << "Cannot allocate memory...\n";
		exit(EXIT_FAILURE);
	}
	return stu;
}
//---------------------------------------------------
void *allocate_course()
{ // allocation a pointer to a struct of course. return pointer
	struct Course *cour = new(nothrow) struct Course;
	if (cour == NULL)
	{
		cerr << "Cannot allocate memory...\n";
		exit(EXIT_FAILURE);
	}
	return cour;
}
//------------------------------------------------------
void read_stud(void *p, int &num)
{ // reads a students data
	int num2 = OK;
	struct Stud *stu = (struct Stud*)p;// casting
	stu->_stud_id = num;
	for (int i = 0; i < NUM_OF_GRADES && num2 != END_C; i++)
	{
		cin >> num2;
		stu->_grades[i] = num2;
	}
	cin >> stu->_height;
}
//------------------------------------------------------
void read_course(void *p, int &num)
{// read data of a course.
	struct Course *cour = (struct Course*)p;// casting
	cour->_course_id = num;
	if (num != 0) {
		cin >> cour->_credit_points;
		cin >> cour->_hours_of_course;
	}
}
//--------------------------------------------------
bool compare_stud(void *p1, void *p2)
{// compare current data of id stud with previous data of id stud
	struct Stud *s1 = (struct Stud *)p1;//cast
	struct Stud *s2 = (struct Stud *)p2;//cast
	return s1->_stud_id <= s2->_stud_id;
}
//--------------------------------------------------
bool compare_course(void *p1, void *p2)
{// compare current data of id course with previous data of id course
	struct Course *s1 = (struct Course *)p1;//cast
	struct Course *s2 = (struct Course *)p2;//cast
	return s1->_course_id <= s2->_course_id;
}
//-----------------------------------------------------------
void reset_var(struct Variables &var)
{// reset members of the struct Variables
	var._sum = 0; var._prev_max = 0; var._cur_max = 0;
	var._counter = 0; var._num = OK; var._num2 = OK;
	var._max_grades_stud = 0; var._num_of_stud = 0;
	var._max_hours = 0;
}
//--------------------------------------------------------
void free_root_stud(struct Node *root_stud)
{// free memory of root
	if (root_stud != NULL)
	{
		free_root_stud(root_stud->_left);
		free_root_stud(root_stud->_right);
		delete root_stud;
	}
}
//--------------------------------------------------------
void free_root_course(struct Node *root_course)
{ // free memory of root2
	if (root_course != NULL)
	{
		free_root_course(root_course->_left);
		free_root_course(root_course->_right);
		delete root_course;
	}
}
//------------------------------------------------



