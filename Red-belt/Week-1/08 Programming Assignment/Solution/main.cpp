#include "test_runner.h"

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque {
private:
    vector<T> front;
    vector<T> back;
public:
    Deque() {}

    void PushFront(const T& value) {
        front.push_back(value);
    }

    void PushBack(const T& value) {
        back.push_back(value);
    }

    bool Empty() const {
        return (front.empty() && back.empty());
    }

    size_t Size() const {
        return (front.size() + back.size());
    }

    T& operator[](size_t index) {
        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }

        return back[index - front.size()];
    }

    const T& operator[](size_t index) const {
        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }

        return back[index - front.size()];
    }

    T& At(size_t index) {
        size_t total_size = front.size() + back.size();
        if (index >= total_size) {
            throw out_of_range("Index is out of range");
        }

        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }

        return back[index - front.size()];
    }

    const T& At(size_t index) const {
        size_t total_size = front.size() + back.size();
        if (index >= total_size) {
            throw out_of_range("Index is out of range");
        }

        if (index < front.size()) {
            return front[front.size() - 1 - index];
        }

        return back[index - front.size()];
    }

    T& Front() {
        if (!front.empty()) {
            return front.back();
        } else {
            return back.front();
        }
    }

    const T& Front() const {
        if (!front.empty()) {
            return front.back();
        } else {
            return back.front();
        }
    }

    T& Back() {
        if (!back.empty()) {
            return back.back();
        } else {
            return front.front();
        }
    }

    const T& Back() const {
        if (!back.empty()) {
            return back.back();
        } else {
            return front.front();
        }
    }
};

void TestDeque() {
    {
        Deque<int> test;
        try {
            test.PushFront(1);
            ASSERT_EQUAL(test.At(0), 1);
        } catch (const out_of_range& err) {
             cerr << err.what() <<  endl;
        }
        test.PushFront(2);
        ASSERT_EQUAL(test.At(0), 2);
        ASSERT_EQUAL(test.At(1), 1);
        test.PushBack(3);
        ASSERT_EQUAL(test.At(2), 3);
    }
    {
        Deque<int> test;
        try {
            test.PushFront(1);
            ASSERT_EQUAL(test[0], 1);
        } catch (const out_of_range& err) {
             cerr << err.what() <<  endl;
        }
        test.PushFront(2);
        ASSERT_EQUAL(test[0], 2);
        ASSERT_EQUAL(test[1], 1);
        test.PushBack(3);
        ASSERT_EQUAL(test[2], 3);
    }
    {
        Deque<int> test;
        try {
            test.PushFront(1);
            ASSERT_EQUAL(test.Back(), 1);
            ASSERT_EQUAL(test.Front(), 1);
        } catch (const out_of_range& err) {
             cerr << err.what() <<  endl;
        }
        test.PushFront(2);
        ASSERT_EQUAL(test.Back(), 1);
        ASSERT_EQUAL(test.Front(), 2);
        test.PushBack(3);
        ASSERT_EQUAL(test.Back(), 3);
        ASSERT_EQUAL(test.Front(), 2);
        test.PushBack(4);
        ASSERT_EQUAL(test.Back(), 4);
        ASSERT_EQUAL(test.Front(), 2);
    }
    {
        Deque<int> test;
        try {
            test.PushFront(1);
            test[0] = 1;
            ASSERT_EQUAL(test[0], 1);
            ASSERT_EQUAL(test.Front(), 1);
        } catch (const out_of_range& err) {
             cerr << err.what() <<  endl;
        }
        test.PushFront(2);
        ASSERT_EQUAL(test.Back(), 1);
        ASSERT_EQUAL(test.Front(), 2);
        test.PushBack(3);
        ASSERT_EQUAL(test.Back(), 3);
        ASSERT_EQUAL(test.Front(), 2);
        test.PushBack(4);
        ASSERT_EQUAL(test.Back(), 4);
        ASSERT_EQUAL(test.Front(), 2);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestDeque);

    return 0;
}
