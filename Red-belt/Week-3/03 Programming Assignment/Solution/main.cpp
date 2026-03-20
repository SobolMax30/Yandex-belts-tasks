#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size) {}

    ~SimpleVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    void PushBack(const T& value) {
        if (size >= capacity) {
            size_t new_cap;
            if (capacity == 0) {
                new_cap = 1;
            } else {
                new_cap = 2 * capacity;
            }
            T* new_data = new T[new_cap];
            copy(begin(), end(), new_data);
            delete[] data;
            data = new_data;
            capacity = new_cap;
        }
        data[size] = value;
        size++;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

void TestConstruction() {
    SimpleVector<int> empty;
    ASSERT_EQUAL(empty.Size(), 0u);
    ASSERT_EQUAL(empty.Capacity(), 0u);
    ASSERT(empty.begin() == empty.end());

    SimpleVector<string> five_strings(5);
    ASSERT_EQUAL(five_strings.Size(), 5u);
    ASSERT(five_strings.Size() <= five_strings.Capacity());
    for (auto& item : five_strings) {
        ASSERT(item.empty());
    }
    five_strings[2] = "Hello";
    ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
    SimpleVector<int> v;
    for (int i = 10; i >= 1; --i) {
        v.PushBack(i);
        ASSERT(v.Size() <= v.Capacity());
    }
    sort(begin(v), end(v));

    const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQUAL(v.Size(), expected.size());
    ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestConstruction);
    RUN_TEST(tr, TestPushBack);

    return 0;
}
