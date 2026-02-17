#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    vector<int> temps(n);

    int sum = 0;
    for (int& t : temps) {
        cin >> t;
        sum += t;
    }

    int avg = sum / n;

    vector<int> above_avg;
    for (size_t i = 0; i < temps.size(); ++i) {
        if (temps[i] > avg) {
            above_avg.push_back(i);
        }
    }

    cout << above_avg.size() << endl;
    for (const int& x : above_avg) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
