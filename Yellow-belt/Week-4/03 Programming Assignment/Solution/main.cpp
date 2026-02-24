#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> words;

    auto begin_it = begin(s);
    auto end_it = end(s);

    while (true) {
        auto it = find(begin_it, end_it, ' ');

        words.push_back(string(begin_it, it));

        if (it == end_it) {
            break;
        } else {
            begin_it = it + 1;
        }
    }

    return words;
}

int main() {
    string s = "C Cpp Java Python";
    vector<string> words = SplitIntoWords(s);

    cout << words.size() << ;
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
