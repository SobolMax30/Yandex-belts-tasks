#include <iostream>
#include <string>
#include <map>

using namespace std;

string FindName(const map<int, string>& names, int year) {
    string name;

    for (const auto& item : names) {
        if (item.first <= year) {
            name = item.second;
        } else {
            break;
        }
    }

    return name;
}

class Person {
private:
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
      const string firstName = FindName(firstNames, year);
      const string lastName = FindName(lastNames, year);

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
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
