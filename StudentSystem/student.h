#pragma once
#include "person.h"

class Student : public Person
{
public:
	Student(int ID, string name, int age, int titleID);
	Student(int ID, string name, int age, int titleID, vector<Course> m_course);
	Student(const Person& p);
	void showInfo();	
	~Student();


};

