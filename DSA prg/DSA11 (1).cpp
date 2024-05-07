#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Student {
public:
    int rollNo;
    char name[10];
    char div;
    char address[20];

    void accept() {
        cout << "\n\tEnter Roll Number: ";
        cin >> rollNo;
        cout << "\n\tEnter the Name: ";
        cin >> name;
        cout << "\n\tEnter the Division: ";
        cin >> div;
        cout << "\n\tEnter the Address: ";
        cin >> address;
    }

    void acceptRollNo() {
        cout << "\n\tEnter the Roll No. to modify: ";
        cin >> rollNo;
    }

    void acceptName() {
        cout << "\n\tEnter the name to modify: ";
        cin >> name;
    }

    int getRollNo() {
        return rollNo;
    }

    void display() {
        cout << "\n\t" << rollNo << "\t\t" << name << "\t\t" << div << "\t\t" << address;
    }
};

int main() {
    Student student;
    fstream file, tempFile;
    int choice;

    do {
        cout << "\n>>>>>>>>>>>>>>>>>>>>>>MENU<<<<<<<<<<<<<<<<<<<<";
        cout << "\n1. Insert and overwrite\n2. Show\n3. Search & Edit (by Roll No.)";
        cout << "\n4. Search & Edit (by Name)\n5. Delete a Student Record\n6. Exit";
        cout << "\nEnter the Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                file.open("StuRecord.txt", ios::out | ios::binary);
                if (!file.is_open()) {
                    cout << "Error opening file for writing." << endl;
                    break;
                }

                do {
                    student.accept();
                    file.write(reinterpret_cast<char*>(&student), sizeof(student));

                    cout << "\nDo you want to enter more records? (1: Yes, 2: No): ";
                    cin >> choice;
                } while (choice == 1);

                file.close();
                break;

            case 2:
                file.open("StuRecord.txt", ios::in | ios::binary);
                if (!file.is_open()) {
                    cout << "Error opening file for reading." << endl;
                    break;
                }

                cout << "\n\tRoll No.\t\tName \t\t Division \t\t Address";
                while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
                    student.display();
                }

                file.close();
                break;

            case 3:
                int rollNoToSearch;
                cout << "\nEnter the roll number you want to find and edit: ";
                cin >> rollNoToSearch;

                file.open("StuRecord.txt", ios::in | ios::out | ios::binary);
                if (!file.is_open()) {
                    cout << "Error opening file for reading and writing." << endl;
                    break;
                }

                while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
                    if (student.getRollNo() == rollNoToSearch) {
                        cout << "\nRecord found";
                        file.seekp(-static_cast<int>(sizeof(student)), ios::cur);
                        student.accept();
                        file.write(reinterpret_cast<char*>(&student), sizeof(student));
                        file.close();
                        break;
                    }
                }

                if (file.eof()) {
                    cout << "\nRecord not found";
                }

                file.close();
                break;

            case 4:
                char nameToSearch[10];
                cout << "\nEnter the name you want to find and edit: ";
                cin >> nameToSearch;

                file.open("StuRecord.txt", ios::in | ios::out | ios::binary);
                if (!file.is_open()) {
                    cout << "Error opening file for reading and writing." << endl;
                    break;
                }

                while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
                    if (strcmp(student.name, nameToSearch) == 0) {
                        cout << "\nName found";
                        file.seekp(-static_cast<int>(sizeof(student)), ios::cur);
                        student.accept();
                        file.write(reinterpret_cast<char*>(&student), sizeof(student));
                        file.close();
                        break;
                    }
                }

                if (file.eof()) {
                    cout << "\nName not found";
                }

                file.close();
                break;

            case 5:
                int rollToDelete;
                cout << "Please Enter the Roll No. of Student Whose Info You Want to Delete: ";
                cin >> rollToDelete;

                file.open("StuRecord.txt", ios::in | ios::binary);
                tempFile.open("temp.txt", ios::out | ios::binary);

                if (!file.is_open() || !tempFile.is_open()) {
                    cout << "Error opening file for deletion." << endl;
                    break;
                }

                while (file.read(reinterpret_cast<char*>(&student), sizeof(student))) {
                    if (student.getRollNo() != rollToDelete) {
                        tempFile.write(reinterpret_cast<char*>(&student), sizeof(student));
                    }
                }

                cout << "The record with the roll no. " << rollToDelete << " has been deleted." << endl;

                file.close();
                tempFile.close();

                remove("StuRecord.txt");
                rename("temp.txt", "StuRecord.txt");
                break;

            case 6:
                cout << "\nThank you!" << endl;
                break;

            default:
                cout << "\nUnknown choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}
