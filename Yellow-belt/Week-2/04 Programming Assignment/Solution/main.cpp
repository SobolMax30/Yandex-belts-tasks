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

class Rational {
private:
    int gcd(int numerator, int denominator) {
        return !denominator ? abs(numerator) : gcd(denominator, numerator % denominator);
    }

    int numer;
    int denomin;
public:
    Rational() : numer(0), denomin(1) {}

    Rational(int numerator, int denominator) : numer(0), denomin(1) {
        if (denominator < 0) {
            if (numerator < 0) {
                denominator = abs(denominator);
                numerator = abs(numerator);
            } else {
                denominator = abs(denominator);
                numerator = numerator - 2 * numerator;
            }
        }

        if (numerator == 0) {
            denominator = 1;
        }

        int gcd_value = gcd(numerator, denominator);
        numer = numerator / gcd_value;
        denomin = denominator / gcd_value;
    }

    int Numerator() const {
        return numer;
    }

    int Denominator() const {
        return denomin;
    }
};

void TestDefaultConstructor() {
    AssertEqual(Rational().Numerator(), 0, "Test Numerator == 0");
    AssertEqual(Rational().Denominator(), 1, "Test Denominator == 1");
}

void TestIrreducibleFraction() {
    AssertEqual(Rational(1, 1).Numerator(), 1, "Test 1/1 -> 1/1");
    AssertEqual(Rational(1, 1).Denominator(), 1, "Test 1/1 -> 1/1");
    AssertEqual(Rational(3, 5).Numerator(), 3, "Test 3/5 -> 3/5");
    AssertEqual(Rational(3, 5).Denominator(), 5, "Test 3/5 -> 3/5");
}

void TestNegativeNumerator() {
    AssertEqual(Rational(-2, 6).Numerator(), -1, "Test -2/6 -> -1/3");
    AssertEqual(Rational(-2, 6).Denominator(), 3, "Test -2/6 -> -1/3");
}

void TestNegativeDenominator() {
    AssertEqual(Rational(3, -6).Numerator(), -1, "Test 3/-6 -> -1/2");
    AssertEqual(Rational(3, -6).Denominator(), 2, "Test 3/-6 -> -1/2");
}

void TestBothNegative()
{
    AssertEqual(Rational(-3, -4).Numerator(), 3, "Test -3/-4 -> 3/4");
    AssertEqual(Rational(-3, -4).Denominator(), 4, "Test -3/-4 -> 3/4");
    AssertEqual(Rational(-6, -18).Numerator(), 1, "Test -6/-18 -> 1/3");
    AssertEqual(Rational(-6, -18).Denominator(), 3, "Test -6/-18 -> 1/3");
}

void TestFractionReduction()
{
    AssertEqual(Rational(24, 90).Numerator(), 4, "Test 24/90 -> 4/15");
    AssertEqual(Rational(24, 90).Denominator(), 15, "Test 24/90 -> 4/15");
    AssertEqual(Rational(3, 9).Numerator(), 1, "Test 3/9 -> 1/3");
    AssertEqual(Rational(3, 9).Denominator(), 3, "Test 3/9 -> 1/3");
}

void TestZeroNumerator()
{
    AssertEqual(Rational(0, 20).Numerator(), 0, "Test 0/20 -> 0/1");
    AssertEqual(Rational(0, 20).Denominator(), 1, "Test 0/20 -> 0/1");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestIrreducibleFraction, "TestIrreducibleFraction");
    runner.RunTest(TestNegativeNumerator, "TestNegativeNumerator");
    runner.RunTest(TestNegativeDenominator, "TestNegativeDenominator");
    runner.RunTest(TestBothNegative, "TestBothNegative");
    runner.RunTest(TestFractionReduction, "TestFractionReduction");
    runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
}

int main() {
    TestAll();

    return 0;
}
