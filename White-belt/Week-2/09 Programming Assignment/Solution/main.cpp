#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    int q;
    cin >> q;
    vector<bool> is_nerv;

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;

        if (command == "WORRY_COUNT") {
            cout << count(begin(is_nerv), end(is_nerv), true) << endl;
        }
        else {
            if (command == "WORRY" || command == "QUIET") {
                int index;
                cin >> index;

                if (command == "WORRY") {
                    is_nerv[index] = true;
                } else {
                    is_nerv[index] = false;
                }
            }
            else if (command == "COME") {
                int people_count;
                cin >> people_count;

                is_nerv.resize(is_nerv.size() + people_count, false);
            }
        }
    }

    return 0;
}
