#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> FindHistory(const map<int, string>& namesByYear, int year) {
    vector<string> names;

    for (const auto& item : namesByYear) {
        if (item.first <= year && (names.empty() || names.back() != item.second)) {
            names.push_back(item.second);
        }
    }

    return names;
}

string BuildHistory(vector<string> names) {
    if (names.empty()) {
        return "";
    }

    reverse(begin(names), end(names));

    string history = names[0];

    for (int i = 1; i < names.size(); ++i) {
        if (i == 1) {
            history += " (";
        } else {
            history += ", ";
        }
        history += names[i];
    }

    if (names.size() > 1) {
        history += ")";
    }

    return history;
}

string FullName(const string& firstName, const string& lastName) {
    if (firstName.empty() && lastName.empty()) {
        return "Incognito";
    } else if (firstName.empty()) {
        return lastName + " with unknown first name";
    } else if (lastName.empty()) {
        return firstName + " with unknown last name";
    } else {
        return firstName + " " + lastName;
    }
}

class Person {
private:
    vector<string> FindFirstNamesHistory(int year) const {
        return FindHistory(firstNames, year);
    }
    vector<string> FindLastNamesHistory(int year) const {
        return FindHistory(lastNames, year);
    }
    map<int, string> firstNames;
    map<int, string> lastNames;
    int birthYear;
public:
    Person(const string& firstName, const string& lastName, int newBirthYear) {
        birthYear = newBirthYear;
        firstNames[newBirthYear] = firstName;
        lastNames[newBirthYear] = lastName;
    }
    void ChangeFirstName(int year, const string& firstName) {
        if (year >= birthYear) {
            firstNames[year] = firstName;
        }
    }
    void ChangeLastName(int year, const string& lastName) {
        if (year >= birthYear) {
            lastNames[year] = lastName;
        }
    }
    string GetFullName(int year) const {
        if (year >= birthYear) {
            const vector<string> firstNamesHistory = FindFirstNamesHistory(year);
            const vector<string> lastNamesHistory = FindLastNamesHistory(year);

            string firstName;
            string lastName;
            if (!firstNamesHistory.empty()) {
                firstName = firstNamesHistory.back();
            }
            if (!lastNamesHistory.empty()) {
                lastName = lastNamesHistory.back();
            }

            return FullName(firstName, lastName);
        } else {
            return "No person";
        }
    }
    string GetFullNameWithHistory(int year) const {
        if (year >= birthYear) {
            const string firstName = BuildHistory(FindFirstNamesHistory(year));
            const string lastName = BuildHistory(FindLastNamesHistory(year));

            return FullName(firstName, lastName);
        } else {
            return "No person";
        }
    }
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
