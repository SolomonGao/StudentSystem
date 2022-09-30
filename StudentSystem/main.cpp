#include "system.h"

int main()
{   
    int choice;
    System m_Sys;

    while (true)
    {
        m_Sys.showMenu();
        cout << "Please enter your choice:  ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        default:
            cout << "Invalid command." << endl;
            break;
        case 0:
            m_Sys.quit();
            break;
        case 1:
            m_Sys.addPerson();
            break;
        case 2:
            m_Sys.showPeople();
            break;
        case 3:
            m_Sys.deletePerson();
            break;
        case 4:
            m_Sys.editPerson();
            break;
        case 5:
            m_Sys.showAllCourses();
            break;
        case 6:
            m_Sys.searchPerson();
            break;
        case 7:
            m_Sys.SortByID();
            break;
        case 8:
            m_Sys.addCourseTo();
            break;
        case 9:
            m_Sys.dropCourseFrom();
            break;
        case 10:
            m_Sys.format();
            break;
        }
        system("pause");
        system("cls");
    }

    system("pause");
    return 0;
}

