#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> FindHistory(const map<int, string>& names_by_year, int year) {
    vector<string> names;

    for (const auto& item : names_by_year) {
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

    string joinedName = names[0];

    for (int i = 1; i < names.size(); ++i) {
        if (i == 1) {
            joinedName += " (";
        } else {
            joinedName += ", ";
        }
        joinedName += names[i];
    }

    if (names.size() > 1) {
        joinedName += ")";
    }

    return joinedName;
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
    vector<string> FindFirstNamesHistory(int year) {
        return FindHistory(firstNames, year);
    }
    vector<string> FindLastNamesHistory(int year) {
        return FindHistory(lastNames, year);
    }
    map<int, string> firstNames;
    map<int, string> lastNames;
public:
    void ChangeFirstName(int year, const string& firstName) {
        firstNames[year] = firstName;
    }
    void ChangeLastName(int year, const string& lastName) {
        lastNames[year] = lastName;
    }
    string GetFullName(int year) {
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
    }
    string GetFullNameWithHistory(int year) {
        const string firstName = BuildHistory(FindFirstNamesHistory(year));
        const string lastName = BuildHistory(FindLastNamesHistory(year));

        return FullName(firstName, lastName);
    }
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
