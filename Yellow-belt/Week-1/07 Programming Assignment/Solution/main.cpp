#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& map, Key key) {
    if (map.count(key) == 0) {
        throw runtime_error("The key doesn't exist");
    }

    return map[key];
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;

    return 0;
}

