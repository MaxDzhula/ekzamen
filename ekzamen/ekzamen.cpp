#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_TASKS = 100;

enum Priority {
    LOW = 1,
    MEDIUM,
    HIGH
};
enum TaskType {
    PERSONAL = 0,
    WORK,
    STUDY
};

struct User {
    string name;
    string forname;
    int id;
};

struct Task {
    string title;
    string deadline;
    Priority priority;
    TaskType type;
    bool done;
    User user;
};

struct Category {
    TaskType type;
    Task tasks[MAX_TASKS];
    int count = 0;
};












void main() {
    Task tasks[MAX_TASKS];
    int count = 0;

    while (true) {
        cout << endl << "1 Add Task\n";
        cout << "2 Show Tasks by User\n";
        cout << "3 Delete Task\n";
        cout << "4 Mark Done\n";
        cout << "5 Save All\n";
        cout << "6 Save Personal\n";
        cout << "7 Save by Category\n";
        cout << "8 Load from File\n";
        cout << "9 Search by Priority\n";
        cout << "10 Search by Deadline\n";
        cout << "0 Exit\n";

        int choice;
        cin >> choice;

        if (choice == 1) addTask(tasks, count);
        else if (choice == 2) {
            string user;
            cout << "Enter username: ";
            cin >> user;
            showUserTasks(tasks, count, user);
        }
        else if (choice == 3) {
            int idx;
            cout << "Enter task index to delete: ";
            cin >> idx;
            deleteTask(tasks, count, idx - 1);
        }
        else if (choice == 4) {
            int idx;
            cout << "Enter task index to mark done: ";
            cin >> idx;
            markDone(tasks, count, idx - 1);
        }
        else if (choice == 5) saveToAll(tasks, count);
        else if (choice == 6) saveToPersonal(tasks, count);
        else if (choice == 7) saveByCategory(tasks, count);
        else if (choice == 8) {
            string file;
            cout << "Enter filename: ";
            cin >> file;
            loadFromFile(tasks, count, file);
        }
        else if (choice == 9) {
            int p;
            cout << "Priority to search (1-Low, 2-Medium, 3-High): ";
            cin >> p;
            searchByPriority(tasks, count, static_cast<Priority>(p));
        }
        else if (choice == 10) {
            string dl;
            cout << "Enter deadline (YYYY-MM-DD): ";
            cin >> dl;
            searchByDeadline(tasks, count, dl);
        }
        else if (choice == 0) break;
    }
}