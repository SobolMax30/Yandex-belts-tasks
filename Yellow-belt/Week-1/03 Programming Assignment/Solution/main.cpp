#include <iostream>
#include <cstdint>

using namespace std;

int main() {
    int n, r;
    cin >> n >> r;

    uint64_t answer = 0;

    for (int i = 0; i < n; ++i) {
        int w, h, d;
        cin >> w >> h >> d;

        answer += static_cast<uint64_t>(w) * h * d;
    }

    answer *= r;
    cout << answer << endl;

    return 0;
}
