#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nums;

    for (int i = n; i > 0; --i) {
        nums.push_back(i);
    }

    do {
        for(auto& x : nums) {
            cout << x << " ";
        }
        cout << endl;
    } while (prev_permutation(begin(nums), end(nums)));

    return 0;
}
