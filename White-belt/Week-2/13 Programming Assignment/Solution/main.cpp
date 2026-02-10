#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_stops, stops_for_buses;

    for (int i = 0; i < q; ++i) {
        string command;
        cin >> command;

        if (command == "NEW_BUS") {
            string bus;
            cin >> bus;

            int stop_count;
            cin >> stop_count;

            vector<string>& stops = buses_stops[bus];
            stops.resize(stop_count);

            for (string& stop : stops) {
                cin >> stop;
                stops_for_buses[stop].push_back(bus);
            }
        } else if (command == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;

            if (stops_for_buses.count(stop) == 0) {
                cout << "No stop" << endl;
              } else {
                for (const string& bus : stops_for_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
              }
        } else if (command == "STOPS_FOR_BUS") {
            string bus;
            cin >> bus;

             if (buses_stops.count(bus) == 0) {
                cout << "No bus" << endl;
              } else {
                for (const string& stop : buses_stops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops_for_buses[stop].size() == 1) {
                        cout << "no interchange";
                    } else {
                        for (const string& other_bus : stops_for_buses[stop]) {
                          if (bus != other_bus) {
                            cout << other_bus << " ";
                          }
                        }
                    }
                    cout << endl;
                }
              }
        } else if (command == "ALL_BUSES") {
            if (buses_stops.empty()) {
                cout << "No buses" << endl;
              } else {
                for (const auto& bus_item : buses_stops) {
                  cout << "Bus " << bus_item.first << ": ";
                  for (const string& stop : bus_item.second) {
                    cout << stop << " ";
                  }
                  cout << endl;
                }
              }
        }
    }

    return 0;
}
