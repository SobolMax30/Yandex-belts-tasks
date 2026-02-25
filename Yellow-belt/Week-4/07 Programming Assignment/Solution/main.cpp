#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort1(RandomIt range_begin, RandomIt range_end) {
    int length = range_end - range_begin;
    if (length < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
      auto mid = begin(elements) + length / 2;

    MergeSort1(begin(elements), mid);
    MergeSort1(mid, end(elements));

    merge(begin(elements), mid, mid, end(elements), range_begin);
}

template <typename RandomIt>
void MergeSort2(RandomIt range_begin, RandomIt range_end) {
    int length = range_end - range_begin;
    if (length < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto f_third = begin(elements) + length / 3;
    auto s_third = begin(elements) + length * 2 / 3;

    MergeSort2(begin(elements), f_third);
    MergeSort2(f_third, s_third);
    MergeSort2(s_third, end(elements));

    vector<typename RandomIt::value_type> pre_result;
    merge(begin(elements), f_third, f_third, s_third, back_inserter(pre_result));

    merge(begin(pre_result), end(pre_result), s_third, end(elements), range_begin);
}

int main() {
    vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};

    MergeSort1(begin(v1), end(v1));

    for (int x : v1) {
        cout << x << " ";
    }
    cout << endl;

    vector<int> v2 = {6, 4, 7, 6, 4, 4, 0, 1, 5};

    MergeSort2(begin(v2), end(v2));

    for (int x : v2) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
