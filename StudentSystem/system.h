#pragma once
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include <vector>
#include <sstream>
#include "student.h"
#include "instructor.h"


#define PEOPLEFILE "peopleFile.txt"
#define COURSEFILE "courseFile.txt"


class System
{
public:
	System();
	void showMenu();
	void addPerson();
	void showPeople();
	void saveFile();
	int getPeopleNum();
	void initSystem();
	void deletePerson();
	int isExist(int ID);
	void openCourse();
	void editPerson();
	void showAllCourses();
	void searchPerson();
	void addCourseTo();
	void dropCourseFrom();
	void SortByID();
	void quickSort(Person** arr, int left, int right);
	void format();
	void quit();
	~System();
	Person** m_PeopleArr;
	int people_Num;
	bool m_fileEmpty;
	vector<Course> m_coursesVec;
};

