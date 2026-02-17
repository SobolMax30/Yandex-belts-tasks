#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
    os << "[";
    bool first = true;
    for (const auto& x : v) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "]";
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

int GetDistinctRealRootCount(double a, double b, double c)
{
    double D = pow(b, 2) - 4 * a * c;

    if (a == 0) {
        if (b != 0) {
            cout << -c / b << endl;
            return 1;
        }
    } else if (D == 0) {
        cout << -b / (2 * a) << endl;
        return 1;
    } else if (D > 0) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        cout << x1 << " " << x2 << endl;
        return 2;
    }

    return 0;
}

void TestNoRoots() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "Test 1 - No roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "Test 2 - No roots");
}

void TestPositiveDiscriminant()
{
    AssertEqual(GetDistinctRealRootCount(1, 5, 4), 2, "Test 1 - Positive discriminant");
    AssertEqual(GetDistinctRealRootCount(4, 2, -1), 2, "Test 2 - Positive discriminant");
    AssertEqual(GetDistinctRealRootCount(-2, 4, -1), 2, "Test 3 - Positive discriminant");
}

void TestNegativeDiscriminant()
{
    AssertEqual(GetDistinctRealRootCount(9, 6, 2), 0, "Test 1 - Negative discriminant");
    AssertEqual(GetDistinctRealRootCount(-7, -3, -2), 0, "Test 2 - Negative discriminant");
    AssertEqual(GetDistinctRealRootCount(4, 4, 4), 0, "Test 3 - Negative discriminant");
}

void TestZeroDiscriminant()
{
    AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "Test 1 - Zero discriminant");
    AssertEqual(GetDistinctRealRootCount(2, 4, 2), 1, "Test 2 - Zero discriminant");
    AssertEqual(GetDistinctRealRootCount(16, 8, 1), 1, "Test 3 - Zero discriminant");
}

void TestLinear()
{
    AssertEqual(GetDistinctRealRootCount(0, -1, 12), 1, "Test 1 - Linear");
    AssertEqual(GetDistinctRealRootCount(0, 123, 44), 1, "Test 2 - Linear");
    AssertEqual(GetDistinctRealRootCount(0, 23, -12), 1, "Test 3- Linear");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestNoRoots, "TestNoRoots");
    runner.RunTest(TestPositiveDiscriminant, "TestPositiveDiscriminant");
    runner.RunTest(TestNegativeDiscriminant, "TestNegativeDiscriminant");
    runner.RunTest(TestZeroDiscriminant, "TestZeroDiscriminant");
    runner.RunTest(TestLinear, "TestLinear");

    return 0;
}
