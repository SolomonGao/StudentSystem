#include "system.h"


System::System()
{
	this->openCourse();

	ifstream ifs;
	ifs.open(PEOPLEFILE, ios::in);
	if (!ifs.is_open())
	{
		//cout << "File does not exist" << endl;
		this->m_fileEmpty = true;
		this->m_PeopleArr = NULL;
		this->people_Num = 0;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "Empty file" << endl;
		this->m_fileEmpty = true;
		this->m_PeopleArr = NULL;
		this->people_Num = 0;
		ifs.close();
		return;
	}

	int num = this->getPeopleNum();
	this->people_Num = num;
	
	this->m_PeopleArr = new Person * [this->people_Num];
	this->initSystem();

	this->m_fileEmpty = false;



	
}

void System::initSystem()
{
	ifstream ifs;
	ifs.open(PEOPLEFILE, ios::in);

	int ID;
	string name;
	int age;
	int titleID;
	string courses;

	int count;
	int i = 0;
	string line;
	Person* person = NULL;

	while (getline(ifs, line))
	{
		stringstream ss(line);

		string tmp;
		count = 0;
		while (getline(ss, tmp, ','))
		{
			if (count == 0)
			{
				ID = stoi(tmp);
			}

			if (count == 1)
			{
				name = tmp;
			}

			if (count == 2)
			{
				age = stoi(tmp);
			}

			if (count == 3)
			{
				titleID = stoi(tmp);
			}

			if (count == 4)
			{
				courses = tmp;
			}
			count++;
		}

		istringstream ss2(courses);
		vector<Course> m_courses;
		string course;
		while (ss2 >> course)
		{
			m_courses.push_back(this->m_coursesVec[stoi(course) - 1]);
		}

 		if (titleID == 2)
		{
			person = new Instructor(ID, name, age, titleID, m_courses);
		}

		else
		{
			person = new Student(ID, name, age, titleID, m_courses);
		}

		this->m_PeopleArr[i] = person;

		i++;
		


	}

	ifs.close();


}

int System::getPeopleNum()
{
	ifstream ifs;
	ifs.open(PEOPLEFILE, ios::in);

	int num = 0;
	string line;
	while (getline(ifs, line))
	{
		num++;
	}

	ifs.close();
	return num;

	 
}

void System::addPerson()
{
	int ID;
	int age;
	string name;
	int choice;

	int new_Size = this->people_Num + 1;

	Person** new_Space = new Person*[new_Size];

	if (this->m_PeopleArr != NULL)
	{
		for (int i = 0; i < this->people_Num; i++)
		{
			new_Space[i] = this->m_PeopleArr[i];
		}
	}
	cout << "Are you adding a student or a instructor? " << endl;
	cout << "1. Student" << endl;
	cout << "2. Instructor" << endl;
	cin >> choice;
		if (choice == 1 || choice == 2)
		{
			cout << "ID: ";
			cin >> ID;
			int check = this->isExist(ID);
			if (check == -1)
			{
				cout << "Name: ";
				cin.ignore();
				getline(cin, name);

				cout << "age: ";
				cin >> age;

				Person* person = NULL;

				if (choice == 2)
				{
					person = new Instructor(ID, name, age, choice);

					new_Space[new_Size - 1] = person;
				}

				else if (choice == 1)
				{
					person = new Student(ID, name, age, choice);

					new_Space[new_Size - 1] = person;
				}
			}
			else
			{
				cout << "This ID already exists" << endl;
				return;
			}
		}
		else
		{
			cout << "Invalid command" << endl;
			return;
		}
		delete[] this->m_PeopleArr;
		this->m_PeopleArr = new_Space;
		this->people_Num = new_Size;

		this->saveFile();

		cout << "Added successfully" << endl;
}

void System::showPeople()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	for (int i = 0; i < this->people_Num; i++)
	{
		this->m_PeopleArr[i]->showInfo();
		cout << endl;
	}

}

int System::isExist(int ID)
{
	int index = -1;
	for (int i = 0; i < this->people_Num; i++)
	{
		if (ID == this->m_PeopleArr[i]->m_ID)
		{
			index = i;
			break;
		}
	}

	return index;
}

void System::deletePerson()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	int ID;
	int choice;
	int index;

	cout << "Please enter the ID of the person you want to delete from the system: ";
	cin >> ID;
	index = this->isExist(ID);
	if (index != -1)
	{
		cout << "Found this person:" << endl;
		cout << *this->m_PeopleArr[index] << endl;
		cout << endl;
		cout << "Do you want to delete this person? " << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> choice;
		if (choice == 1)
		{
			for (int i = index; i < this->people_Num - 1; i++)
			{
				this->m_PeopleArr[i] = this->m_PeopleArr[i + 1];
			}
			if (this->people_Num-- == 0)
			{
				this->m_fileEmpty = true;
			}
			this->saveFile();
			cout << "Delete successfully" << endl;

		}
		else
			cout << "Return to menu." << endl;
			return;
	}
	else
	{
		cout << "Didn't find this person." << endl;
	}

	return;
}

void System::editPerson()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	int ID;
	int index = -1;

	cout << "Please enter the ID of the person you want to edit from the system : ";
	cin >> ID;
	index = this->isExist(ID);
	if (index != -1)
	{
		cout << "Found this person:" << endl;
		cout << *this->m_PeopleArr[index] << endl;
		cout << endl;
		cout << "Which information do you want to edit? " << endl;
		cout << "1. Name" << endl;
		cout << "2. Age" << endl;

		int choice;
		cin >> choice;
		if (choice == 1)
		{
			string name;
			cin.ignore();
			cout << "New name: ";
			getline(cin, name);
			this->m_PeopleArr[index]->m_Name = name;
		}
		else if (choice == 2)
		{
			int age;
			cout << "New age: ";
			cin >> age;
			this->m_PeopleArr[index]->m_Age = age;
		}
		else
			cout << "Invalid command" << endl;

		this->saveFile();
		cout << "Edited successfully" << endl;
	}

	else
		cout << "Did not found this ID." << endl;

}

void System:: showMenu()
{
	cout << "*****************************" << endl;
	cout << "Welcome to use our Management" << endl;
	cout << "0.Quit" << endl;
	cout << "1.Add people" << endl;
	cout << "2.Show current people" << endl;
	cout << "3.Delete people" << endl;
	cout << "4.Edit people" << endl;
	cout << "5.Show all courses" << endl;
	cout << "6.Search person" << endl;
	cout << "7.Sort by ID" << endl;
	cout << "8.Add course to a student" << endl;
	cout << "9.Drop course from a student" << endl;
	cout << "10.Format file" << endl;
	cout << "*****************************" << endl;
	cout << endl;
}

void System::openCourse()
{
	ifstream ifs;
	ifs.open(COURSEFILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "Did not find the storage of courses information. " << endl;
	}

	int courseID;
	string courseAbbv;
	string name;
	string line;
	int count;


	while (getline(ifs, line))
	{
		stringstream ss(line);

		string tmp;
		count = 0;
		while (getline(ss, tmp, ','))
		{
			if (count == 0)
				courseID = stoi(tmp);
			else if (count == 1)
				courseAbbv = tmp;
			else if (count == 2)
				name = tmp;
			count++;
		}
		Course course (courseID, courseAbbv, name);
		this->m_coursesVec.push_back(course);
	}
	ifs.close();

}

void System::saveFile()
{
	ofstream ofs;
	ofs.open(PEOPLEFILE, ios::out);

	for (int i = 0; i < this->people_Num; i++)
	{
		ofs << this->m_PeopleArr[i]->m_ID << ","
			<< this->m_PeopleArr[i]->m_Name << ","
			<< this->m_PeopleArr[i]->m_Age << ","
			<< this->m_PeopleArr[i]->titleID << ", ";
		for (vector<Course>::iterator it = this->m_PeopleArr[i]->m_Courses.begin(); it < this->m_PeopleArr[i]->m_Courses.end(); it++)
		{
			ofs << (*it).m_CourseID << " ";
		}
		ofs << endl;
	}
	ofs.close();
}

void System::searchPerson()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	int choice;
	cout << "Search by ID or by name? " << endl;
	cout << "1. ID" << endl;
	cout << "2. name" << endl;
	cin >> choice;
	if (choice == 1)
	{ 
		bool found = false;
		int ID;
		cout << "ID: ";
		cin >> ID;

		for (int i = 0; i < this->people_Num; i++)
		{
			if (ID == this->m_PeopleArr[i]->m_ID)
			{
				cout << "Found this person: " << endl;
				cout << *this->m_PeopleArr[i] << endl;

				found = true;
			}
		}
		if (!found)
		{
			cout << "Did not find a person with this ID" << endl;
		}
	}
	else if (choice == 2)
	{
		string name;
		int num = 0; // number of people found
		cout << "Name: ";
		cin.ignore();
		getline(cin, name);
		for (int i = 0; i < this->people_Num; i++)
		{
			if (name == this->m_PeopleArr[i]->m_Name)
			{
				num++;
				cout << *this->m_PeopleArr[i] << endl;
			}
		}
		cout << "Total people found: " << num << endl;
	}
}

void System::addCourseTo()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	int ID;
	int index = -1;

	cout << "Please enter the person's ID: ";
	cin >> ID;
	index = this->isExist(ID);
	if (index != -1)
	{
		cout << "Found this person:" << endl;
		cout << "\t";
		this->m_PeopleArr[index]->showInfo();
		cout << endl;
	}
	else
	{
		cout << "Did not found this ID" << endl;
		return;
	}

	int choice;
	cout << "Please select the course you want to add to this person." << endl;
	this->showAllCourses();
	cin >> choice;

	for (vector<Course>::iterator it = m_PeopleArr[index]->m_Courses.begin();it < m_PeopleArr[index]->m_Courses.end(); it++)
	{
		if ((*it).m_CourseID == this->m_coursesVec[choice - 1].m_CourseID)
		{
			cout << "The course had already chosen by this person." << endl;
			return;
		}
	}

	this->m_PeopleArr[index]->m_Courses.push_back(this->m_coursesVec[choice - 1]);
	cout << "Added successfully. " << endl;

	this->saveFile();

}

void System::dropCourseFrom()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	int ID;
	int index = -1;

	cout << "Please enter the person's ID: ";
	cin >> ID;
	index = this->isExist(ID);
	if (index != -1)
	{
		cout << "Found this person:" << endl;
		cout << *this->m_PeopleArr[index] << endl;
	}
	else
	{
		cout << "Did not found this ID" << endl;
		return;
	}

	cout << "The courses this person take: " << endl;
	int i = 0;
	for (vector<Course>::iterator it = this->m_PeopleArr[index]->m_Courses.begin(); it < m_PeopleArr[index]->m_Courses.end(); it++)
	{
		cout << ++i << ". " << (*it).courseAbbv << " " << (*it).m_CourseName << endl;
	}
	int choice;
	cout << "Please select the course you want to drop from this person." << endl;
	cin >> choice;
	if (choice <= i && choice > 0)
	{
		cout << "Are you sure you want to drop "<< this->m_PeopleArr[index]->m_Courses[choice - 1].m_CourseName << "?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		int choice2;
		cin >> choice2;
		if (choice2 == 1)
		{
			this->m_PeopleArr[index]->m_Courses.erase(this->m_PeopleArr[index]->m_Courses.begin() + choice - 1);
			cout << "Drop successfully" << endl;
			this->saveFile();
			return;
		}
		else if (choice2 == 2)
		{
			return;
		}
		else
		{
			cout << "Invalid command" << endl;
			return;
		}
	}
	else
		cout << "Out of range" << endl;

}

void System::SortByID()
{
	if (this->m_fileEmpty)
	{
		cout << "No data in the file" << endl;
		return;
	}
	quickSort(this->m_PeopleArr, 0, this->people_Num - 1);
	cout << "Sort successfully" << endl;
	this->saveFile();
}

void System::quickSort(Person** arr, int left, int right)
{
	if (left < right)
	{
		int i = left;
		int j = right;
		Person* pivot = arr[left];
		while (i < j)
		{
			while (i < j && arr[j]->m_ID >= pivot->m_ID)
				j--;
			if (i < j)
				arr[i++] = arr[j];
			while (i < j && arr[i]->m_ID < pivot->m_ID)
				i++;
			if (i < j)
				arr[j--] = arr[i];
		}
		arr[i] = pivot;
		quickSort(arr, left, i - 1);
		quickSort(arr, i + 1, right);
	}
}

void System::showAllCourses()
{	
	for (vector<Course>::iterator it = this->m_coursesVec.begin(); it < this->m_coursesVec.end(); it++)
	{
		cout << (*it).m_CourseID << ". " << (*it).courseAbbv << " " << (*it).m_CourseName << endl;
	}
}

void System::format()
{
	cout << "Are you sure you want to format the file? " << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;

	int choice;
	cin >> choice;

	if (choice == 1)
	{
		ofstream ofs(PEOPLEFILE, ios::trunc);
		ofs.close();

		if (this->m_PeopleArr != NULL)
		{
			for (int i = 0; i < this->people_Num; i++)
			{
				delete this->m_PeopleArr[i];
			}

			this->people_Num = 0;
			delete[] this->m_PeopleArr;
			this->m_PeopleArr = NULL;
			this->m_fileEmpty = true;
		}

		cout << "Format successfully" << endl;

	}
}

void System::quit()
{	
	cout << "Thanks for using." << endl;
	exit(0);
	system("pause");
}

System::~System()
{
	if (this->m_PeopleArr != NULL)
	{
		for (int i = 0; i < this->people_Num; i++)
		{
			delete this->m_PeopleArr[i];
		}
		delete[] this->m_PeopleArr;
		this->m_PeopleArr = NULL;
	}

}

