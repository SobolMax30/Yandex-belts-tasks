#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    auto nearest = numbers.lower_bound(border);

    if (nearest != begin(numbers)) {
        if (nearest == end(numbers)) {
            return prev(nearest);
        } else if (abs(*nearest - border) >= abs(border - *prev(nearest))) {
            return prev(nearest);
        } else {
            return nearest;
        }
    }

    return nearest;
}

int main() {
    set<int> numbers = {1, 4, 6};

    cout << *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

    return 0;
}
