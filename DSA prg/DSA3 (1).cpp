#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    char name[20];
    Node* next;
    Node* down;
    int flag;

    Node() : next(nullptr), down(nullptr), flag(0) {
        name[0] = '\0';
    }
};

class Gll {
    Node* head = nullptr;

public:
    Node* create();
    void insertBook();
    void insertChapter();
    void insertSection();
    void insertSubsection();
    void displayBook();
};

Node* Gll::create() {
    Node* p = new Node;
    cout << "\nEnter the name: ";
    cin >> p->name;
    return p;
}

void Gll::insertBook() {
    if (head == nullptr) {
        head = create();
    } else {
        cout << "\nBook already exists.";
    }
}

void Gll::insertChapter() {
    if (head == nullptr) {
        cout << "\nThere is no book.";
    } else {
        cout << "\nHow many chapters do you want to insert? ";
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            Node* chapter = create();
            if (head->flag == 0) {
                head->down = chapter;
                head->flag = 1;
            } else {
                Node* temp = head->down;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = chapter;
            }
        }
    }
}

void Gll::insertSection() {
    if (head == nullptr) {
        cout << "\nThere is no book.";
    } else {
        cout << "\nEnter the name of the chapter where you want to insert the section: ";
        char ch[20];
        cin >> ch;

        Node* temp = head->down;
        while (temp != nullptr) {
            if (strcmp(ch, temp->name) == 0) {
                cout << "\nHow many sections do you want to insert? ";
                int n;
                cin >> n;
                for (int i = 0; i < n; ++i) {
                    Node* section = create();
                    if (temp->flag == 0) {
                        temp->down = section;
                        temp->flag = 1;
                    } else {
                        Node* t2 = temp->down;
                        while (t2->next != nullptr) {
                            t2 = t2->next;
                        }
                        t2->next = section;
                    }
                }
                return;
            }
            temp = temp->next;
        }
        cout << "\nChapter not found.";
    }
}

void Gll::insertSubsection() {
    if (head == nullptr) {
        cout << "\nThere is no book.";
    } else {
        cout << "\nEnter the name of the chapter where you want to insert the subsection: ";
        char ch[20];
        cin >> ch;

        Node* chapter = head->down;
        while (chapter != nullptr) {
            if (strcmp(ch, chapter->name) == 0) {
                cout << "\nEnter the name of the section where you want to insert the subsection: ";
                char sectionName[20];
                cin >> sectionName;

                if (chapter->flag == 0) {
                    cout << "\nThere are no sections.";
                } else {
                    Node* section = chapter->down;
                    while (section != nullptr) {
                        if (strcmp(sectionName, section->name) == 0) {
                            cout << "\nHow many subsections do you want to insert? ";
                            int n;
                            cin >> n;
                            for (int i = 0; i < n; ++i) {
                                Node* subsection = create();
                                if (section->flag == 0) {
                                    section->down = subsection;
                                    section->flag = 1;
                                } else {
                                    Node* t2 = section->down;
                                    while (t2->next != nullptr) {
                                        t2 = t2->next;
                                    }
                                    t2->next = subsection;
                                }
                            }
                            return;
                        }
                        section = section->next;
                    }
                    cout << "\nSection not found.";
                }
                return;
            }
            chapter = chapter->next;
        }
        cout << "\nChapter not found.";
    }
}

void Gll::displayBook() {
    if (head == nullptr) {
        cout << "\nBook does not exist.";
    } else {
        cout << "\nNAME OF BOOK: " << head->name;
        Node* temp = head->down;
        while (temp != nullptr) {
            cout << "\n\tNAME OF CHAPTER: " << temp->name;
            Node* section = temp->down;
            while (section != nullptr) {
                cout << "\n\t\tNAME OF SECTION: " << section->name;
                Node* subsection = section->down;
                while (subsection != nullptr) {
                    cout << "\n\t\t\tNAME OF SUBSECTION: " << subsection->name;
                    subsection = subsection->next;
                }
                section = section->next;
            }
            temp = temp->next;
        }
    }
}

int main() {
    Gll g;
    int choice;
    while (true) {
        cout << "\n\nEnter your choice:";
        cout << "\n1. Insert book";
        cout << "\n2. Insert chapter";
        cout << "\n3. Insert section";
        cout << "\n4. Insert subsection";
        cout << "\n5. Display book";
        cout << "\n6. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                g.insertBook();
                break;
            case 2:
                g.insertChapter();
                break;
            case 3:
                g.insertSection();
                break;
            case 4:
                g.insertSubsection();
                break;
            case 5:
                g.displayBook();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice, please try again.";
        }
    }
    return 0;
}
