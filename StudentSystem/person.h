#pragma once
#include "course.h"
using namespace std;



class Person
{	friend ostream& operator <<(ostream& os, Person& p);
public:
	virtual void showInfo() = 0;
	int m_ID;
	string m_Name;
	int m_Age;
	int titleID;
	vector<Course> m_Courses;
};

ostream& operator <<(ostream& os, Person& p);