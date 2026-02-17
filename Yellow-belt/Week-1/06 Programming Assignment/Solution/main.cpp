#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

template<typename T>
T Sqr(T x);

template<typename T>
vector<T> Sqr(const vector<T>& x);

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& x);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& x);

template <typename T>
T Sqr(T x) {
    return x * x;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
    vector<T> result;

    for (const T& x : value) {
        result.push_back(Sqr(x));
    }

    return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& x) {
    return {Sqr(x.first), Sqr(x.second)};
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& x) {
    map<Key, Value> result;

    for (const auto& element : x) {
        result[element.first] = Sqr(element.second);
    }

    return result;
}

int main() {
    vector<int> v = {1, 2, 3};

    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };

    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}

