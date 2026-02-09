#include <iostream>

using namespace std;

void updateIfGreater(int first, int& second) {
    if (first > second) {
        second = first;
    }
}

int main () {
    int a = 8;
    int b = 2;
    updateIfGreater(a, b);

    cout << "a = " << a << endl << "b = " << b << endl;

    return 0;
}
