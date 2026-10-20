#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Student details
struct Student
{
    int id;
    string name;
    int age;
    string course;
    float marks;
};

Student s[100];
int total = 0;

// Read old records from file when program starts
void loadData()
{
    ifstream fin("students.txt");

    total = 0;
    while (total < 100 && fin >> s[total].id)
    {
        fin.ignore();
        getline(fin, s[total].name);
        fin >> s[total].age;
        fin.ignore();
        getline(fin, s[total].course);
        fin >> s[total].marks;
        fin.ignore();
        total++;
    }

    fin.close();
}

// Save all records in file
void saveData()
{
    ofstream fout("students.txt");

    for (int i = 0; i < total; i++)
    {
        fout << s[i].id << endl;
        fout << s[i].name << endl;
        fout << s[i].age << endl;
        fout << s[i].course << endl;
        fout << s[i].marks << endl;
    }

    fout.close();
}

// Find student using ID
int search(int id)
{
    for (int i = 0; i < total; i++)
    {
        if (s[i].id == id)
            return i;
    }

    return -1;
}

void addStudent()
{
    if (total >= 100)
    {
        cout << "Student list is full.\n";
        return;
    }

    Student temp;

    cout << "\nEnter student ID: ";
    cin >> temp.id;

    if (search(temp.id) != -1)
    {
        cout << "ID already exists.\n";
        return;
    }

    cin.ignore();

    cout << "Enter name: ";
    getline(cin, temp.name);

    cout << "Enter age: ";
    cin >> temp.age;
    cin.ignore();

    cout << "Enter course: ";
    getline(cin, temp.course);

    cout << "Enter marks: ";
    cin >> temp.marks;

    s[total] = temp;
    total++;

    saveData();
    cout << "Record added successfully.\n";
}

void showStudents()
{
    if (total == 0)
    {
        cout << "\nNo records available.\n";
        return;
    }

    cout << "\n--- Student Details ---\n";

    for (int i = 0; i < total; i++)
    {
        cout << "\nStudent " << i + 1 << endl;
        cout << "ID: " << s[i].id << endl;
        cout << "Name: " << s[i].name << endl;
        cout << "Age: " << s[i].age << endl;
        cout << "Course: " << s[i].course << endl;
        cout << "Marks: " << s[i].marks << endl;
    }
}

void searchStudent()
{
    int id;

    cout << "\nEnter ID to search: ";
    cin >> id;

    int pos = search(id);

    if (pos == -1)
    {
        cout << "Student not found.\n";
    }
    else
    {
        cout << "\nStudent details:\n";
        cout << "ID: " << s[pos].id << endl;
        cout << "Name: " << s[pos].name << endl;
        cout << "Age: " << s[pos].age << endl;
        cout << "Course: " << s[pos].course << endl;
        cout << "Marks: " << s[pos].marks << endl;
    }
}

void updateStudent()
{
    int id;

    cout << "\nEnter ID to update: ";
    cin >> id;

    int pos = search(id);

    if (pos == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    cin.ignore();

    cout << "Enter new name: ";
    getline(cin, s[pos].name);

    cout << "Enter new age: ";
    cin >> s[pos].age;
    cin.ignore();

    cout << "Enter new course: ";
    getline(cin, s[pos].course);

    cout << "Enter new marks: ";
    cin >> s[pos].marks;

    saveData();
    cout << "Record updated successfully.\n";
}

void deleteStudent()
{
    int id;

    cout << "\nEnter ID to delete: ";
    cin >> id;

    int pos = search(id);

    if (pos == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    for (int i = pos; i < total - 1; i++)
    {
        s[i] = s[i + 1];
    }

    total--;
    saveData();

    cout << "Record deleted successfully.\n";
}

int main()
{
    loadData();

    int choice;

    do
    {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                showStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                saveData();
                cout << "Thank you.\n";
                break;
            default:
                cout << "Wrong choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
