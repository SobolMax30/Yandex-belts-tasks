#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& i : v) {
        cin >> i;
    }

    sort(begin(v), end(v), [](int a, int b) {
        return abs(a) < abs(b);
    });

    for (const auto& i : v) {
        cout << i << " ";
    }

    return 0;
}
