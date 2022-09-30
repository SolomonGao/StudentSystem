#include "person.h"

//int &Person::getID()
//{
//	return this->m_ID;
//}
//
//string &Person::getName()
//{
//	return this->m_Name;
//}
//
//int &Person::getAge()
//{
//	return this->m_Age;
//}

//int Person::getTitleID()
//{
//	return this->titleID;
//}
//
//vector<Course> Person::getCourses()
//{
//	return this->m_Courses;
//}


ostream& operator <<(ostream& os, Person& p)
{
	if (p.titleID == 1)
		os << "Identity: Student ";
	else
		os << "Identity: Instructor ";
	os << "ID: " << p.m_ID << "  Name: " << p.m_Name << "  Age: " << p.m_Age << endl;
	return os;
}