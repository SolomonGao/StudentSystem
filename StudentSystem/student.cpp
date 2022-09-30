#include "student.h"


Student::Student(int ID, string name, int age, int titleID)
{
	this->m_Name = name;
	this->m_Age = age;
	this->m_ID = ID;
	this->titleID = titleID;
}

Student::Student(int ID, string name, int age, int titleID, vector<Course> m_courses)
{
	this->m_Name = name;
	this->m_Age = age;
	this->m_ID = ID;
	this->titleID = titleID;
	this->m_Courses = m_courses;
}

Student::Student(const Person& p)
{
	this->m_Age = p.m_Age;
	this->m_ID = p.m_ID;
	this->m_Courses = p.m_Courses;
	this->m_Name = p.m_Name;
	this->titleID = p.titleID;
}

void Student::showInfo()
{
	cout << "Identity: Students " << "ID: " << this->m_ID << "  Name: " << this->m_Name << "  Age: " << this->m_Age << endl;
	cout << "Courses this student is taking: [ ";
	for (vector<Course>::iterator it = this->m_Courses.begin(); it < this->m_Courses.end(); it++)
	{
		cout << (*it).m_CourseName << ", ";
	}
	cout << " ]" << endl;
}

Student::~Student()
{

}

