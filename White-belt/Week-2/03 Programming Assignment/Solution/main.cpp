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

vector<string> palindromFilter(vector<string> words, int minLength) {
    vector<string> filtered;
    for (auto w : words) {
        if (isPalindrom(w) && w.size() >= minLength) {
            filtered.push_back(w);
        }
        else {
            continue;
        }
    }
    return filtered;
}

int main () {
    vector<string> words = {"weew", "bro", "code"};
    vector<string> filtered = palindromFilter(words, 4);

    printVector(filtered);

    cout << endl;

    return 0;
}
