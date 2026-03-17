#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
private:
    map<int, set<int>> reachable_lists_;
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);

        auto it = reachable_lists_.find(start);
        if (it == reachable_lists_.end()) {
            return result;
        }

        const set<int>& stations = it->second;
        auto lower = stations.lower_bound(finish);
        if (lower != stations.end()) {
            result = min(result, abs(*lower - finish));
        }

        if (lower != stations.begin()) {
            auto prev_lower = prev(lower);
            result = min(result, abs(*prev_lower - finish));
        }

        return result;
    }
};

int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;

        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
