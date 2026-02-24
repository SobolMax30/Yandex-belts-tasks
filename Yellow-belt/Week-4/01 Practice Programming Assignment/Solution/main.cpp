#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
    auto neg_it = find_if(begin(numbers), end(numbers), [](const int& num) {
        return num < 0;
    });

    for (auto it = neg_it; it != numbers.begin(); ) {
        cout << *(--it) << " ";
    }
    cout << endl;
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    PrintVectorPart({-6, 1, 8, -5, 4});
    PrintVectorPart({6, 1, 8, 5, 4});

    return 0;
}
