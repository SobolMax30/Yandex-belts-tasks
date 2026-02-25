#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }

    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );

    return middle->age;
}

void PrintStats(vector<Person> persons) {
    auto females = partition(begin(persons), end(persons), [](const Person& person) {
        return person.gender == Gender::FEMALE;
    });

    auto employed_females = partition(begin(persons), females, [](const Person& person) {
        return person.is_employed;
    });

    auto employed_males = partition(females, end(persons), [](const Person& person) {
        return person.is_employed;
    });

    cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
    cout << "Median age for females = " << ComputeMedianAge(begin(persons), females) << endl;
    cout << "Median age for males = " << ComputeMedianAge(females, end(persons)) << endl;
    cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), employed_females) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(employed_females, females) << endl;
    cout << "Median age for employed males = " << ComputeMedianAge(females, employed_males) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(employed_males, end(persons)) << endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };

    PrintStats(persons);

    return 0;
}
