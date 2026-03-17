#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class ReadingManager {
private:
    const int MAX_USER_COUNT_ = 100'000;
    const int MAX_PAGE_COUNT_ = 1'000;

    vector<int> people;
    vector<int> pages;
public:
    ReadingManager() :
    people(MAX_USER_COUNT_ + 1, -1),
    pages(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count) {
        for (int i = people[user_id] + 1; i <= page_count; i++) {
            ++pages[i];
        }
        people[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if (people[user_id] == -1) {
            return 0;
        }

        if (pages[0] == 1) {
            return 1;
        }

        return static_cast<double>(pages[0] - pages[people[user_id]]) / static_cast<double>(pages[0] - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int i = 0; i < query_count; ++i) {
        string query_type;
        int user_id;
        cin >> query_type >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << fixed << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
