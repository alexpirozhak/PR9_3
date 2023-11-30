#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

struct Student
{
    string surname;
    string initials;
    int marks[5];
};

void AddStudent(Student*& students, int& N, Student newStudent);
void RemoveStudent(Student*& students, int& N, int removeIndex);
void ReplaceStudent(Student* students, int N, int replaceIndex, Student newStudent);
void Create(Student* group, const int N);
void Print(Student* students, const int N);
void GetAll5(Student* students, const int N, Student*& studentsAll5, int& countAll5);
void GetSome3(Student* students, const int N, Student*& studentsSome3, int& countSome3);
void GetSome2(Student* students, const int N, Student*& studentsSome2, int& countSome2);
void RemoveBadStudents(Student*& students, int& N);
void SaveToFile(Student* p, const int N, const char* filename);
void LoadFromFile(Student*& p, int& N, const char* filename);

int main()
{
    int N;
    cout << "Enter number of students in a group N: "; cin >> N;
    Student* group = new Student[N];
    Student* selectedStudents = nullptr;
    Student newStudent;
    int selectedCount = 0;
    char filename[256];
    int index;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose action:" << endl << endl;
        cout << " [1] - enter data of students" << endl;
        cout << " [2] - show all students" << endl;
        cout << " [3] - show students, that have only \"5\" marks" << endl;
        cout << " [4] - show students, that have some \"3\" marks" << endl;
        cout << " [5] - show students, that have some \"2\" marks" << endl
            << " Remove a student if he has more than 1 \"2\" mark" << endl;
        cout << " [6] - add new student" << endl;
        cout << " [7] - remove student" << endl;
        cout << " [8] - replace student" << endl;
        cout << " [9] - save to file" << endl;
        cout << " [10] - load from name" << endl;
        cout << " [0] - exit" << endl;
        cout << "Enter your choice: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        //case 1:
            /*cin.get();
            cin.sync();
            cout << "enter file name: "; cin.getline(filename, 255);
            LoadFromFile(group, N, filename);
            break;*/
        case 1:
            cin.get();
            cin.sync();
            cout << "enter data of students: ";
            Create(group, N);

        case 2:
            Print(group, N);
            break;
        case 3:
            GetAll5(group, N, selectedStudents, selectedCount);
            Print(selectedStudents, selectedCount);

            delete[] selectedStudents;
            selectedStudents = nullptr;
            selectedCount = 0;
            break;
        case 4:
            GetSome3(group, N, selectedStudents, selectedCount);
            Print(selectedStudents, selectedCount);

            delete[] selectedStudents;
            selectedStudents = nullptr;
            selectedCount = 0;
            break;
        case 5:
            RemoveBadStudents(group, N);
            GetSome2(group, N, selectedStudents, selectedCount);
            Print(selectedStudents, selectedCount);

            delete[] selectedStudents;
            selectedStudents = nullptr;
            selectedCount = 0;
            break;
        case 6:
            cout << "Enter new student info:" << endl;
            cin.get();
            cin.sync();
            cout << " surname: "; getline(cin, newStudent.surname);
            cout << " initials: "; getline(cin, newStudent.initials);
            for (int j = 0; j < 5; j++)
            {
                cout << " mark " << j + 1 << ": ";
                cin >> newStudent.marks[j];
            }
            AddStudent(group, N, newStudent);
            cout << endl;
        case 7:
            cout << "Enter remove index: "; cin >> index;
            RemoveStudent(group, N, index);
            cout << endl;
        case 8:
            cout << "Enter replace index: "; cin >> index;
            cout << "Enter changed student info:" << endl;
            cin.get();
            cin.sync();
            cout << " surname: "; getline(cin, newStudent.surname);
            cout << " initials: "; getline(cin, newStudent.initials);
            for (int j = 0; j < 5; j++)
            {
                cout << " mark " << j + 1 << ": ";
                cin >> newStudent.marks[j];
            }
            ReplaceStudent(group, N, index, newStudent);
            cout << endl;
        case 9:
            cin.get();
            cin.sync();
            cout << "enter file name: "; cin.getline(filename, 255);
            SaveToFile(group, N, filename);
            break;

        case 10:
            cin.get();
            cin.sync();
            cout << "enter file name: "; cin.getline(filename, 255);
            LoadFromFile(group, N, filename);
            break;

        case 0:
            break;
        default:
            cout << "Error input! Choose a correct option" << endl;
        }
    } while (menuItem != 0);

    delete[] group;
    return 0;
}

void AddStudent(Student*& students, int& N, Student newStudent)
{
    Student* newStudents = new Student[N + 1];
    for (int i = 0; i < N; i++)
    {
        newStudents[i].surname = students[i].surname;
        newStudents[i].initials = students[i].initials;
        for (int j = 0; j < 5; j++)
            newStudents[i].marks[j] = students[i].marks[j];
    }

    newStudents[N].surname = newStudent.surname;
    newStudents[N].initials = newStudent.initials;
    for (int j = 0; j < 5; j++)
        newStudents[N].marks[j] = newStudent.marks[j];
    N++;

    delete[] students;
    students = newStudents;
}

void RemoveStudent(Student*& students, int& N, int removeIndex)
{
    if (removeIndex < 0 || removeIndex >= N)
        return;
    Student* newStudents = new Student[N - 1];
    for (int i = 0; i < removeIndex; i++)
    {
        newStudents[i].surname = students[i].surname;
        newStudents[i].initials = students[i].initials;
        for (int j = 0; j < 5; j++)
            newStudents[i].marks[j] = students[i].marks[j];
    }
    for (int i = removeIndex + 1; i < N; i++)
    {
        newStudents[i - 1].surname = students[i].surname;
        newStudents[i - 1].initials = students[i].initials;
        for (int j = 0; j < 5; j++)
            newStudents[i - 1].marks[j] = students[i].marks[j];
    }
    N--;

    delete[] students;
    students = newStudents;
}

void ReplaceStudent(Student* students, int N, int replaceIndex, Student newStudent)
{
    if (replaceIndex < 0 || replaceIndex >= N)
        return;
    students[replaceIndex].surname = newStudent.surname;
    students[replaceIndex].initials = newStudent.initials;
    for (int j = 0; j < 5; j++)
        students[replaceIndex].marks[j] = newStudent.marks[j];
}

void Create(Student* students, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Student №" << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " surname: "; getline(cin, students[i].surname);
        cout << " initials: "; getline(cin, students[i].initials);
        for (int j = 0; j < 5; j++)
        {
            cout << " mark " << j + 1 << ": ";
            cin >> students[i].marks[j];
        }
        cout << endl;
    }
}

void Print(Student* students, const int N)
{
    cout << "=============================================" << endl;
    cout << "| №  |    Surname    | Initials | Marks     |" << endl;
    cout << "---------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(3) << right << i + 1 << " "
            << "| " << setw(14) << left << students[i].surname
            << "| " << setw(6) << right << students[i].initials << "   ";
        cout << "| ";
        for (int j = 0; j < 5; j++)
            cout << students[i].marks[j] << " ";
        cout << "|" << endl;
    }
    cout << "=============================================" << endl;
    cout << endl;
}

void GetAll5(Student* students, const int N, Student*& studentsAll5, int& countAll5)
{
    for (int i = 0; i < N; i++)
    {
        bool isAll5 = true;
        for (int j = 0; j < 5; j++)
            if (students[i].marks[j] != 5)
                isAll5 = false;

        if (isAll5)
            AddStudent(studentsAll5, countAll5, students[i]);
    }
}

void GetSome3(Student* students, const int N, Student*& studentsSome3, int& countSome3)
{
    for (int i = 0; i < N; i++)
    {
        bool isSome3 = false;
        for (int j = 0; j < 5; j++)
            if (students[i].marks[j] == 3)
                isSome3 = true;

        if (isSome3)
            AddStudent(studentsSome3, countSome3, students[i]);
    }
}

void GetSome2(Student* students, const int N, Student*& studentsSome2, int& countSome2)
{
    for (int i = 0; i < N; i++)
    {
        bool isSome3 = false;
        for (int j = 0; j < 5; j++)
            if (students[i].marks[j] == 2)
                isSome3 = true;

        if (isSome3)
            AddStudent(studentsSome2, countSome2, students[i]);
    }
}

void RemoveBadStudents(Student*& students, int& N)
{
    for (int i = 0; i < N; i++)
    {
        int count2 = 0;
        for (int j = 0; j < 5; j++)
            if (students[i].marks[j] == 2)
                count2++;

        if (count2 > 1)
        {
            RemoveStudent(students, N, i);
            i--;
        }
    }
}

void SaveToFile(Student* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary); 
    fout.write((char*)&N, sizeof(N)); 
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Student)); 
    fout.close(); 
}

void LoadFromFile(Student*& p, int& N, const char* filename)
{
    delete[] p; 
    ifstream fin(filename, ios::binary); 
    fin.read((char*)&N, sizeof(N)); 
    p = new Student[N]; 
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Student)); 
    fin.close(); 
}