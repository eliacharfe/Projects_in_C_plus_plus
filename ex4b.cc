/* ./ex4b.cc
 * Statistic data of students and courses
 * ==================================================
 * Written by: Eliachar Feig. ID: 302278338
 *==================================================
 * This program is reading into struct data of students (id, grades, height)
 * and data to another struct saving data about courses (id, c.points, hours)
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
struct Avarage {
	double _avr;
	int _index_max;
};
enum bool_t { END_C = -1, END_S = 0, OK };
//------------------------------------------------
void read_studs(struct Stud studs[]);
void read_a_student(struct Stud &stu, int &num);
void read_courses(struct Course courses[]);
void read_a_course(struct Course &cour, double &num);
struct Avarage func_ptr(void *p,
	double(*func_name)(void *, struct Avarage&),
	struct Avarage &avar);
double avr_studs_grades(void *p, struct Avarage &avar);
double avr_height_students(void *p, struct Avarage &avar);
double avr_credits_points(void *p, struct Avarage &avar);
double avr_hours_courses(void *p, struct Avarage &avar);
//-----------------------------------------------------
int main()
{
	struct Stud studs[CLASS_SIZE];
	struct Course courses[NUM_OF_COURSES];

    read_studs(studs);
	read_courses(courses);

	struct Avarage avar;
	avar = func_ptr(studs, avr_studs_grades, avar);// generic function
	cout << avar._avr << " ";
	avar = func_ptr(studs, avr_height_students, avar);// generic function
	cout << avar._avr << " ";
	avar = func_ptr(courses, avr_credits_points, avar);// generic function
	cout << avar._avr << " ";
	avar = func_ptr(courses, avr_hours_courses, avar);// generic function
	cout << avar._avr << " ";
	avar = func_ptr(studs, avr_studs_grades, avar);// generic function
	cout << avar._index_max << " ";
	avar = func_ptr(courses, avr_hours_courses, avar);// generic function
	cout << avar._index_max << endl;

	return EXIT_SUCCESS;
}
//--------------------------------------------------
struct Avarage func_ptr(void *p,
	double(*func_name)(void*, struct Avarage&),
	struct Avarage &avar)
{ // generic function that send with the correct data and return struct
	// by reference. Gets the arr of studs or of courses, the function of
	// calculation. struct by ref to save the correct data to print in main.
	double res = 0;
	res = func_name(p, avar);
	return avar;
}
//--------------------------------------------
double avr_studs_grades(void *p, struct Avarage &avar)
{// calculates avarage of students and save it in struct and save also
	// id of the student that received the highest avarage of grades.
	// return struct by reference
	struct Stud *studs = (struct Stud *)p;//cast
	struct Stud stu;
	double sum = 0, prev_max = 0, cur_max = 0;
	int  counter = 0,num = OK, num2 = OK,
			max_grades_stud = 0, j = 0,  num_of_stud = 0;
	for (int i = 0; i < CLASS_SIZE && num2 != END_S; i++)
	{
		stu = studs[i];//current student
		num2 = stu._stud_id;
		if (num2 == END_S)// if id = 0
		{break;}
		num_of_stud++;
		for (j = 0; j < NUM_OF_GRADES && num != END_C
			&& num2 != END_S; j++)
		{
			num = stu._grades[j];
			if (num != END_C)// if the grade is != -1
			{
				counter++;
				cur_max += stu._grades[j];
			}
		}
		cur_max /= counter;
		sum += cur_max;
		if (cur_max > prev_max)
		{
			max_grades_stud = stu._stud_id;
			prev_max = cur_max;
		}
		cur_max = 0;
		counter = 0;
		num = OK;
	}
	avar._avr = sum / num_of_stud; //save data
	avar._index_max = max_grades_stud;// save data
	return avar._avr;//return double
}
//------------------------------------------------------
double avr_height_students(void *p, struct Avarage &avar)
{ // calculates avarage of students. update struct by reference
	struct Stud *studs = (struct Stud*)p;//cast
	struct Stud stu;
	double sum = 0;
	int counter = 0,num = OK;
	for (int i = 0; i < CLASS_SIZE && num != END_S; i++)
	{
		stu = studs[i];
		num = stu._stud_id;
			if (num != END_S)// if id != 0
			{
				sum += stu._height;
				counter++;
			}
	}
	avar._avr = sum / counter; //save data
	return avar._avr;//return double
}
//--------------------------------------------------------------------
double avr_credits_points(void *p, struct Avarage &avar)
{ // calculates avarage of credit points. update struct Avarage by ref.
	// returns double
	struct Course *courses = (struct Course *)p; // casting
	struct Course cour;
	double sum = 0;
	int counter = 0; int num = OK;
	for (int i = 0; i < NUM_OF_COURSES && num != END_S; i++)
	{
		cour = courses[i];
		num = cour._course_id;
		if (num != END_S)
		{
			sum += cour._credit_points;
			counter++;
		}
	}
	avar._avr = sum / counter;// save data
	return avar._avr;//return double
}
//--------------------------------------------------------------
double avr_hours_courses(void *p, struct Avarage &avar)
{// calculates avarage of hours of courses. update struct Avarage by ref.
	// returns double
	struct Course *courses = (struct Course *)p;// casting
	struct Course cour;
	double sum = 0, prev_max_h = 0, curr_max_h = 0;
	int counter = 0, num = OK, max_hours = 0;
	for (int i = 0; i < NUM_OF_COURSES && num != END_S; i++)
	{
		cour = courses[i];
		num = cour._course_id;
		if (num != END_S)// if id != 0
		{
			sum += cour._hours_of_course;
			counter++;
			curr_max_h = cour._hours_of_course;
		}
		if (curr_max_h > prev_max_h)
		{
			max_hours = cour._course_id;
			prev_max_h = curr_max_h;
			curr_max_h = 0;
		}
	}
	avar._avr = sum / counter;// save data
	avar._index_max = max_hours;// save data
	return avar._avr;//returns double
}
//-------------------------------------------------------------
void read_studs(struct Stud studs[])
{// read students
	int num = OK;
	for (int i = 0; i < CLASS_SIZE && num != END_S; i++)
	{
		read_a_student(studs[i], num);
	}
}
//-----------------------------------------
void read_a_student(struct Stud &stu, int &num)
{// read a student // save it by reference
	cin >> stu._stud_id;
	num = stu._stud_id;
if (num != END_S) { // if id != 0
	for (int i = 0; i < NUM_OF_GRADES && (stu._grades[i-1] != END_C); i++)
			cin >> stu._grades[i];
		cin >> stu._height;
	}
}
//----------------------------------------------------------
void read_courses(struct Course courses[])
{// read courses
	double num = OK;
	for (int i = 0; i < NUM_OF_COURSES && num != END_S; i++)
	{
		read_a_course(courses[i], num);
	}
}
//-----------------------------------------
void read_a_course(struct Course &cour, double &num)
{// read a course // save data by reference
	cin >> cour._course_id;
	num = cour._course_id;
	if (num != 0) {
		cin >> cour._credit_points;
		cin >> cour._hours_of_course;
	}
}
