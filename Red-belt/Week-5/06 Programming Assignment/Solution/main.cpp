#include "test_runner.h"

#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int length = range_end - range_begin;
    if (length < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto one_third = begin(elements) + length / 3;
    auto two_third = begin(elements) + length * 2 / 3;

    MergeSort(begin(elements), one_third);
    MergeSort(one_third, two_third);
    MergeSort(two_third, end(elements));

    vector<typename RandomIt::value_type> pre_res;
    merge(begin(elements), one_third, one_third, two_third, back_inserter(pre_res));
    merge(begin(pre_res), end(pre_res), two_third, end(elements), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);

    return 0;
}
