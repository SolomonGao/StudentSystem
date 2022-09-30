#include "course.h"

Course::Course(int courseID, string courseAbbv, string courseName)
{
	this->m_CourseID = courseID;
	this->courseAbbv = courseAbbv;
	this->m_CourseName = courseName;
}

Course::~Course()
{

}