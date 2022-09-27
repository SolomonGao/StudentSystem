#pragma once
#include "person.h"

class Instructor : public Person
{
public:
	Instructor(int ID, string name, int age, int titleID);
	Instructor(int ID, string name, int age, int titleID, vector<Course> courses);
	Instructor(const Person& p);
	void showInfo();
	~Instructor();

};

