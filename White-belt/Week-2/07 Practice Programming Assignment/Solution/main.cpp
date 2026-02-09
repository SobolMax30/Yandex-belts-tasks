#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функции для удобства (начало)
void printVector(const vector<string>& v) {
    for (const auto& w : v) {
        cout << w << " ";
    }
}

void printVector(const vector<int>& v) {
    for (const auto& n : v) {
        cout << n << " ";
    }
}
// Функции для удобства  (конец)

vector<int> reversed(const vector<int>& v) {
    vector<int> result;
    for (int i = v.size() - 1; i >= 0; --i) {
        result.push_back(v[i]);
    }
    return result;
}

int main () {
    vector<int> nums = {1, 5, 3, 4, 2};
    vector<int> reversed_nums = reversed(nums);

    printVector(reversed_nums);

    cout << endl;

    return 0;
}
