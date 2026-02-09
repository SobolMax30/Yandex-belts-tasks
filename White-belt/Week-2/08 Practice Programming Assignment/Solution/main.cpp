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

int main () {
    int n = 0;
    cin >> n;
    vector<int> temperatures(n);
    int sum = 0;

    for (int& t : temperatures) {
        cin >> t;
        sum += t;
    }

    int average = sum / n;
    vector<int> result_indexes;
    for (int i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            result_indexes.push_back(i);
        }
    }

    cout << result_indexes.size() << endl;
    printVector(result_indexes);
    cout << endl;

    return 0;
}
