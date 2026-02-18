#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
private:
    int fail_count = 0;
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }
};

class Person {
private:
    string GetFirstName(int year, map<int, string>& firstname) {
        while (firstname.count(year) == 0 && year > 0) {
            --year;
        }
        string first = firstname[year];
        return first;
    }

    string GetLastName(int year, map<int, string>& lastname) {
        while (lastname.count(year) == 0 && year > 0) {
            --year;
        }
        string last = lastname[year];
        return last;
    }

    map<int, string> first_names;
    map<int, string> last_names;
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }

    string GetFullName(int year) {
        const string first_name = GetFirstName(year, first_names);
        const string last_name = GetLastName(year, last_names);
        string full_name = first_name + " " + last_name;

        if (first_name.size() == 0 && last_name.size() == 0) {
            full_name = "Incognito";
            return full_name;
        } else if (first_name.size() == 0) {
            full_name = last_name + " with unknown first name";
            return full_name;
        } else if (last_name.size() == 0) {
            full_name = first_name + " with unknown last name";
            return full_name;
        }
        return full_name;
    }
};

void TestIncognito() {
    Person person_incognito;
    person_incognito.ChangeFirstName(1975, "first_name_1");
    person_incognito.ChangeLastName(1987, "last_name_1");
    AssertEqual(person_incognito.GetFullName(1900), "Incognito", "incognito_1");
}

void TestUnknownFirstName() {
    Person person_unknown_first;
    person_unknown_first.ChangeFirstName(1980, "first_name_1");
    person_unknown_first.ChangeLastName(1967, "last_name_1");
    AssertEqual(person_unknown_first.GetFullName(1970), "last_name_1 with unknown first name", "unknown_first_name_1");
}

void TestUnknownLastName() {
    Person person_unknown_last;
    person_unknown_last.ChangeFirstName(1967, "first_name_1");
    person_unknown_last.ChangeLastName(1980, "last_name_1");
    AssertEqual(person_unknown_last.GetFullName(1970), "first_name_1 with unknown last name", "unknown_last_name_1");
}

void TestBothNames()
{
    Person person_both_names;
    person_both_names.ChangeFirstName(1920, "first_name_1");
    person_both_names.ChangeLastName(1922, "last_name_1");

    AssertEqual(person_both_names.GetFullName(1923),"first_name_1 last_name_1", "both_names_1");
}

void TestChangeFirstName()
{
    Person person_change_first;
    person_change_first.ChangeFirstName(1920, "first_name_1");
    person_change_first.ChangeFirstName(1922, "first_name_2");

    AssertEqual(person_change_first.GetFullName(1899),"Incognito", "change_first_name_1");
    AssertEqual(person_change_first.GetFullName(1920),"first_name_1 with unknown last name", "change_first_name_2");
    AssertEqual(person_change_first.GetFullName(1921),"first_name_1 with unknown last name", "change_first_name_3");
    AssertEqual(person_change_first.GetFullName(1922),"first_name_2 with unknown last name", "change_first_name_4");
}

void TestChangeLastName()
{
    Person person_change_last;
    person_change_last.ChangeLastName(1920, "last_name_1");
    person_change_last.ChangeLastName(1922, "last_name_2");

    AssertEqual(person_change_last.GetFullName(1899),"Incognito", "change_last_name_1");
    AssertEqual(person_change_last.GetFullName(1920),"last_name_1 with unknown first name", "change_last_name_2");
    AssertEqual(person_change_last.GetFullName(1921),"last_name_1 with unknown first name", "change_last_name_3");
    AssertEqual(person_change_last.GetFullName(1922),"last_name_2 with unknown first name", "change_last_name_4");
}

void TestChangeBothNames()
{
    Person person_change_both;
    person_change_both.ChangeFirstName(1920, "first_name_1");
    person_change_both.ChangeLastName(1922, "last_name_1");
    person_change_both.ChangeFirstName(1924, "first_name_2");
    person_change_both.ChangeLastName(1925, "last_name_2");

    AssertEqual(person_change_both.GetFullName(1926),"first_name_2 last_name_2", "change_both_1");
}

void TestSaveFirst()
{
    Person person_save_first;
    person_save_first.ChangeFirstName(1920, "first_name_1");
    person_save_first.ChangeLastName(1922, "last_name_1");
    person_save_first.ChangeFirstName(1925, "first_name_2");

    AssertEqual(person_save_first.GetFullName(1923),"first_name_1 last_name_1", "save_first_1");
}

void TestSaveLast()
{
    Person person_save_last;
    person_save_last.ChangeLastName(1920, "last_name_1");
    person_save_last.ChangeFirstName(1922, "first_name_1");
    person_save_last.ChangeLastName(1925, "last_name_2");

    AssertEqual(person_save_last.GetFullName(1923),"first_name_1 last_name_1", "save_last_1");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestUnknownFirstName, "TestUnknownFirstName");
    runner.RunTest(TestUnknownLastName, "TestUnknownLastName");
    runner.RunTest(TestBothNames, "TestBothNames");
    runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
    runner.RunTest(TestChangeLastName, "TestChangeLastName");
    runner.RunTest(TestChangeBothNames, "TestChangeBothNames");
    runner.RunTest(TestSaveFirst, "TestSaveFirst");
    runner.RunTest(TestSaveLast, "TestSaveLast");
}

int main() {
    TestAll();

    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
