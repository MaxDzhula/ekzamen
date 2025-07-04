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












void addTask(Task tasks[], int& count) {
    if (count >= MAX_TASKS) {
        cout << "Task limit reached.\n";
        return;
    }

    Task& t = tasks[count];

    cout << "Title: ";
    getline(cin >> ws, t.title);
    cout << "Deadline (YYYY-MM-DD): ";
    getline(cin, t.deadline);
    int pr, tp;
    cout << "Priority (1-Low, 2-Medium, 3-High): ";
    cin >> pr;
    t.priority = static_cast<Priority>(pr);
    cout << "Type (0-Personal, 1-Work, 2-Study): ";
    cin >> tp;
    t.type = static_cast<TaskType>(tp);
    t.done = false;

    cout << "User name: ";
    getline(cin >> ws, t.user.name);
    cout << "User forname: ";
    getline(cin, t.user.forname);
    cout << "User id: ";
    cin >> t.user.id;

    count++;
    cout << "Task added.\n";
}

void showUserTasks(Task tasks[], int count, const string& username) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (tasks[i].user.name == username) {
            cout << tasks[i].title << " "
                << tasks[i].deadline << " "
                << tasks[i].priority << " "
                << tasks[i].type << " "
                << tasks[i].user.name << " "
                << tasks[i].user.forname << " "
                << tasks[i].user.id << " "
                << (tasks[i].done ? "Done" : "NotDone") << endl;
            found = true;
        }
    }
    if (!found) cout << "No tasks found for this user.\n";
}

void deleteTask(Task tasks[], int& count, int index) {
    if (index < 0 || index >= count) {
        cout << "Invalid index.\n";
        return;
    }
    for (int i = index; i < count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    count--;
    cout << "Task deleted.\n";
}

void markDone(Task tasks[], int count, int index) {
    if (index < 0 || index >= count) {
        cout << "Invalid index.\n";
        return;
    }
    tasks[index].done = true;
    cout << "Task marked as done.\n";
}

void saveToAll(const Task tasks[], int count) {
    ofstream fout("tasks.txt");
    for (int i = 0; i < count; i++) {
        fout << tasks[i].title << " "
            << tasks[i].deadline << " "
            << tasks[i].priority << " "
            << tasks[i].type << " "
            << tasks[i].user.name << " "
            << tasks[i].user.forname << " "
            << tasks[i].user.id << " "
            << (tasks[i].done ? "Done" : "NotDone") << endl;
    }
    fout.close();
    cout << "Saved to tasks.txt\n";
}

void saveToPersonal(const Task tasks[], int count) {
    for (int i = 0; i < count; i++) {
        string filename = tasks[i].user.name + "_" + tasks[i].user.forname + ".txt";
        ofstream fout(filename, ios::app);
        fout << tasks[i].title << " "
            << tasks[i].deadline << " "
            << tasks[i].priority << " "
            << tasks[i].type << " "
            << tasks[i].user.name << " "
            << tasks[i].user.forname << " "
            << tasks[i].user.id << " "
            << (tasks[i].done ? "Done" : "NotDone") << endl;
        fout.close();
    }
    cout << "Saved to personal files.\n";
}

void saveByCategory(const Task tasks[], int count) {
    for (int cat = 0; cat <= 2; cat++) {
        string filename;
        if (cat == PERSONAL) filename = "personal.txt";
        else if (cat == WORK) filename = "work.txt";
        else filename = "study.txt";

        ofstream fout(filename);
        for (int i = 0; i < count; i++) {
            if (tasks[i].type == cat) {
                fout << tasks[i].title << " "
                    << tasks[i].deadline << " "
                    <<
                    tasks[i].priority << " "
                    << tasks[i].type << " "
                    << tasks[i].user.name << " "
                    << tasks[i].user.forname << " "
                    << tasks[i].user.id << " "
                    << (tasks[i].done ? "Done" : "NotDone") << endl;
            }
        }
        fout.close();
    }
    cout << "Saved to category files.\n";
}

void loadFromFile(Task tasks[], int& count, const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Cannot open file.\n";
        return;
    }

    Task temp;
    while (fin >> temp.title >> temp.deadline >> (int&)temp.priority >> (int&)temp.type
        >> temp.user.name >> temp.user.forname >> temp.user.id) {
        string doneStr;
        fin >> doneStr;
        temp.done = (doneStr == "Done");
        tasks[count++] = temp;
    }

    fin.close();
    cout << "Loaded tasks from file.\n";
}

void searchByPriority(const Task tasks[], int count, Priority p) {
    for (int i = 0; i < count; i++) {
        if (tasks[i].priority == p) {
            cout << tasks[i].title << " " << tasks[i].deadline << endl;
        }
    }
}

void searchByDeadline(const Task tasks[], int count, const string& deadline) {
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (tasks[i].deadline == deadline) {
            cout << tasks[i].title << " "
                << tasks[i].deadline << " "
                << tasks[i].priority << " "
                << tasks[i].type << " "
                << tasks[i].user.name << " "
                << tasks[i].user.forname << " "
                << tasks[i].user.id << " "
                << (tasks[i].done ? "Done" : "NotDone") << endl;
            found = true;
        }
    }
    if (!found) cout << "No tasks found with this deadline.\n";
}















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