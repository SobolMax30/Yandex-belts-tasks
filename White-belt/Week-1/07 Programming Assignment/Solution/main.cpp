#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int res = -2;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'f') {
            if (res == -2) {
                res = -1;
            }
            else if (res == -1) {
                res = i;
                break;
            }
        }
    }

    cout << res << endl;

    return 0;
}
