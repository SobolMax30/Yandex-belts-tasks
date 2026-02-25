#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    auto left = lower_bound(range_begin, range_end, string(1, prefix));

    char next_prefix = char(prefix + 1);

    auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

    return {left, right};
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto left = lower_bound(range_begin, range_end, prefix);

    string upper_bound = prefix;
    ++upper_bound[upper_bound.size() - 1];

    auto right = lower_bound(range_begin, range_end, upper_bound);

    return {left, right};
}

int main() {
    const vector<string> sorted_strings1 = {"moscow", "murmansk", "vologda"};
    const auto m_result = FindStartsWith(begin(sorted_strings1), end(sorted_strings1), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result = FindStartsWith(begin(sorted_strings1), end(sorted_strings1), 'p');
    cout << (p_result.first - begin(sorted_strings1)) << " " << (p_result.second - begin(sorted_strings1)) << endl;

    const auto z_result = FindStartsWith(begin(sorted_strings1), end(sorted_strings1), 'z');
    cout << (z_result.first - begin(sorted_strings1)) << " " << (z_result.second - begin(sorted_strings1)) << endl;

    const vector<string> sorted_strings2 = {"moscow", "motovilikha", "murmansk"};
    const auto mo_result = FindStartsWith(begin(sorted_strings2), end(sorted_strings2), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result = FindStartsWith(begin(sorted_strings2), end(sorted_strings2), "mt");
    cout << (mt_result.first - begin(sorted_strings2)) << " " << (mt_result.second - begin(sorted_strings2)) << endl;

    const auto na_result = FindStartsWith(begin(sorted_strings2), end(sorted_strings2), "na");
    cout << (na_result.first - begin(sorted_strings2)) << " " << (na_result.second - begin(sorted_strings2)) << endl;

    return 0;
}
