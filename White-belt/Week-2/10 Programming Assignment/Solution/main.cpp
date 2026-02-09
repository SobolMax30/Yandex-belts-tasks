#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int month_count = days_in_months.size();
    int month = 0;

    int q;
    cin >> q;

    vector<vector<string>> days_con(days_in_months[month]);

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;

        if (command == "ADD") {
            int day = 0;
            cin >> day;

            string con;
            cin >> con;

            days_con[--day].push_back(con);
        }
        else if (command == "NEXT") {
            const int old_month_length = days_in_months[month];
            month = (month + 1) % month_count;
            const int new_month_length = days_in_months[month];
            if (new_month_length < old_month_length) {
                vector<string>& last_day_con = days_con[new_month_length - 1];

                for (int i = new_month_length; i < old_month_length; ++i) {
                    last_day_con.insert(end(last_day_con), begin(days_con[i]), end(days_con[i]));
                }
            }
            days_con.resize(new_month_length);
        }
        else if (command == "DUMP") {
            int day_num;
            cin >> day_num;

            cout << days_con[--day_num].size() << " ";

            for (const string& con : days_con[day_num]) {
                cout << con << " ";
            }

            cout << endl;
        }
    }

    return 0;
}
