#include <iostream>
#include <string>
#include <map>

using namespace std;

int main () {
    int q;
    cin >> q;

    map<string, string> country_to_capital;

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;

        if (command == "CHANGE_CAPITAL") {
            string country;
            cin >> country;

            string new_capital;
            cin >> new_capital;

            if (country_to_capital.count(country) == 0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            } else {
                const string& old_capital = country_to_capital[country];
                if (old_capital == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
                }
            }
            country_to_capital[country] = new_capital;
        }
        else if (command == "RENAME") {
            string old_country_name, new_country_name;
            cin >> old_country_name >> new_country_name;
            if (old_country_name == new_country_name || country_to_capital.count(old_country_name) == 0
                        || country_to_capital.count(new_country_name) == 1) {
                cout << "Incorrect rename, skip" << endl;
            } else {
                cout << "Country " << old_country_name << " with capital " << country_to_capital[old_country_name]
                        << " has been renamed to " << new_country_name << endl;
                country_to_capital[new_country_name] = country_to_capital[old_country_name];
                country_to_capital.erase(old_country_name);
            }
        }
        else if (command == "ABOUT") {
            string country;
            cin >> country;

            if (country_to_capital.count(country) == 0) {
                cout << "Country " << country << " doesn't exist" << endl;
            } else {
                cout << "Country " << country << " has capital " << country_to_capital[country] << endl;
            }
        }
        else if (command == "DUMP") {
            if (country_to_capital.empty()) {
                cout << "There are no countries in the world" << endl;
            } else {
                for (const auto& [key, value] : country_to_capital) {
                    cout << key << "/" << value << " ";
                }
                cout << endl;
            }
        }
    }

    return 0;
}
