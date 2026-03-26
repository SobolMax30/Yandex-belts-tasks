#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

// Interface

template <class K, class V>
std::ostream& operator<<(std::ostream& out, const std::map<K, V>& m);

template <class T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s);

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& s);

template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint);

void Assert(bool b, const std::string& hint);

class TestRunner {
private:
    int fail_count = 0;
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name);

    ~TestRunner();
};

// Implemetation

template <class K, class V>
std::ostream& operator<<(std::ostream& out, const std::map<K, V>& m) {
    out << "{";
    bool first = true;

    for (const auto& kv : m) {
        if (!first) {
            out << ", ";
        }
        first = false;
        out << kv.first << ": " << kv.second;
    }

    return out << "}";
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& s) {
    out << "{";
    bool first = true;

    for (const auto& x : s) {
        if (!first) {
            out << ", ";
        }
        first = false;
        out << x;
    }

    return out << "}";
}

template <class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << "{";
    bool first = true;

    for (const auto& x : v) {
        if (!first) {
            out << ", ";
        }
        first = false;
        out << x;
    }

    return out << "}";
}


template <class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;

        throw std::runtime_error(os.str());
    }
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const std::string& test_name) {
    try {
        func();
        std::cerr << test_name << " OK" << std::endl;
    } catch (std::runtime_error& e) {
        ++fail_count;
        std::cerr << test_name << " fail: " << e.what() << std::endl;
    }
}

#define ASSERT_EQUAL(x, y) {                             \
    ostringstream assert_equal_os;                       \
    assert_equal_os << #x << " != " << #y << ", "        \
        << __FILE__ << ":" << __LINE__;                  \
    AssertEqual(x, y, assert_equal_os.str());            \
}

#define ASSERT(x) {                         \
    ostringstream os;                       \
    os << #x << " is false, "               \
        << __FILE__ << ":" << __LINE__;     \
    Assert(x, os.str());                    \
}

#define RUN_TEST(tr, func)                  \
    tr.RunTest(func, #func)
