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

void moveStrings(vector<string>& source, vector<string>& destination) {
    for (auto w : source) {
        destination.push_back(w);
    }
    source.clear();
}

int main () {
    vector<string> source = {"a", "b", "c"};
    vector<string> destination = {"z"};
    moveStrings(source, destination);

    printVector(destination);

    cout << endl;
    cout << "source.size() = " << source.size() << endl;
    cout << "destination.size() = " << destination.size() << endl;

    return 0;
}
