#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void printMap(const map<char, int>& m) {
    for (const auto& [key, value] : m) {
        cout << key << ": " << value << endl;
    }
}

map<char, int> BuildCharCounters(const string& word) {
    map<char, int> counters;
    for (auto& c : word) {
        ++counters[c];
    }
    return counters;
}

int main () {
    int n;
    cin >> n;

    vector<pair<string, string>> pairs;
    pairs.reserve(n);
    for (int i = 0; i < n; ++i) {
        string s1, s2;
        cin >> s1 >> s2;

        pairs.emplace_back(s1, s2);
    }

    for (const auto& [first, second] : pairs) {
        map<char, int> first_cnt = BuildCharCounters(first);
        map<char, int> second_cnt = BuildCharCounters(second);
        if (first_cnt == second_cnt) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
