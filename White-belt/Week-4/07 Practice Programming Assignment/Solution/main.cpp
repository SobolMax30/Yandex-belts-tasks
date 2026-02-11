#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;
    int day;
    int month;
    int year;
};

int main() {
    int n;
    cin >> n;
    vector<Student> students;

    for (int i = 0; i < n; ++i) {
        string name, surname;
        int day, month, year;

        cin >> name >> surname >> day >> month >> year;

        students.push_back({name, surname, day, month, year});
    }

    int m;
    cin >> m;
    string command;
    int k;

    for (int i = 0; i < m; ++i) {
        cin >> command >> k;
        --k;

        if (command == "name" && k >= 0 && k < n) {
            cout << students[k].name << ' ' << students[k].surname << endl;
        } else if (command == "date" && k >= 0 && k < n) {
            cout << students[k].day << '.' << students[k].month
                            << '.' << students[k].year << endl;
        } else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}
