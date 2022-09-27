#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Course
{
public:
	Course(int courseID, string courseAbbv, string courseName);

	~Course();
	int m_CourseID;
	string courseAbbv;
	string m_CourseName;


	
};

