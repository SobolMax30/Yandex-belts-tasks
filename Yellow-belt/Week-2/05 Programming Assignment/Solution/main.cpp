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

bool IsPalindrom(const string& s) {
    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }

    return true;
}

void TestIsPalindrom() {
    Assert(IsPalindrom(""), "Empty string is a palindrom");
    Assert(IsPalindrom("a"), "One letter string is a palindrom");
    Assert(IsPalindrom("abba"), "abba is a palindrom");
    Assert(IsPalindrom("abXba"), "abXba is a palindrom");
    Assert(IsPalindrom("a b Z b a"), "`a b Z b a` is a palindrom");
    Assert(IsPalindrom(" BAAB "), "` BAAB ` is a palindrom");

    Assert(!IsPalindrom("ZabbaXC"), "ZabbaXC is not a palindrom");
    Assert(!IsPalindrom("abXYZba"), "abXYZba is not a palindrom");
    Assert(!IsPalindrom("XYZabba"), "XYZabba is not a palindrom");
    Assert(!IsPalindrom("abbaXYZ"), "abbaXYZ is not a palindrom");
    Assert(!IsPalindrom("BAAB   "), "`BAAB   ` is not a palindrom");
    Assert(!IsPalindrom("  BAAB"), "`  BAAB` is not a palindrom");
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
}

int main() {
    TestAll();

    return 0;
}
