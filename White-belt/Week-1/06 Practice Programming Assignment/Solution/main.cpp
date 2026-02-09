#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    if (a > b || a < 1 || b > 30000)
        return 0;

    for (int i = a; i < b + 1; i++) {
        if (i % 2 == 0) {
            cout << i << " ";
        }
    }

    cout << endl;

    return 0;
}
