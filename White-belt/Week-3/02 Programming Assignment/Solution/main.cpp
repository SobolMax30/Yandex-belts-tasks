#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<string> s(n);

    for (auto& i : s) {
        cin >> i;
    }

    sort(begin(s), end(s),
        [](string& a, string& b) {
            return lexicographical_compare(
                begin(a), end(a),
                begin(b), end(b),
                [](char c1, char c2) { return tolower(c1) < tolower(c2); }
            );
        }
    );

    for (auto& i : s) {
        cout << i << " ";
    }

    return 0;
}
