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

void reverse (vector<int>& nums) {
    int size = nums.size();
    for (int i = 0; i < size / 2; ++i) {
        int temp = nums[i];
        nums[i] = nums[size - i - 1];
        nums[size - i - 1] = temp;
    }
}

int main () {
    vector<int> numbers = {1, 5, 3, 4, 2};
    reverse(numbers);

    printVector(numbers);

    cout << endl;

    return 0;
}
