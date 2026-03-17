#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

struct BookingInfo {
    int64_t time;
    string hotel;
    int client_id;
    int rooms;
};

class BookingSystem {
private:
    queue<BookingInfo> all_bookings;

    map<string, int> hotel_rooms;
    map<string, map<int, int>> hotel_clients;

    int64_t current_time = 0;

    void removeOldBookings() {
        while (!all_bookings.empty()) {
            BookingInfo oldest = all_bookings.front();

            if (oldest.time > current_time - 86400) {
                break;
            }

            hotel_rooms[oldest.hotel] -= oldest.rooms;

            hotel_clients[oldest.hotel][oldest.client_id]--;

            if (hotel_clients[oldest.hotel][oldest.client_id] == 0) {
                hotel_clients[oldest.hotel].erase(oldest.client_id);
            }

            all_bookings.pop();
        }
    }

public:
    void addBooking(int64_t time, string hotel, int client_id, int rooms) {
        current_time = time;

        all_bookings.push({time, hotel, client_id, rooms});

        hotel_rooms[hotel] += rooms;
        hotel_clients[hotel][client_id]++;

        removeOldBookings();
    }

    int getUniqueClients(string hotel) {
        removeOldBookings();

        if (hotel_clients.count(hotel)) {
            return hotel_clients[hotel].size();
        }

        return 0;
    }

    int getTotalRooms(string hotel) {
        removeOldBookings();

        if (hotel_rooms.count(hotel)) {
            return hotel_rooms[hotel];
        }

        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingSystem system;

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string command;
        cin >> command;

        if (command == "BOOK") {
            int64_t time;
            string hotel;
            int client_id, rooms;

            cin >> time >> hotel >> client_id >> rooms;
            system.addBooking(time, hotel, client_id, rooms);
        }
        else if (command == "CLIENTS") {
            string hotel;
            cin >> hotel;
            cout << system.getUniqueClients(hotel) << "\n";
        }
        else if (command == "ROOMS") {
            string hotel;
            cin >> hotel;
            cout << system.getTotalRooms(hotel) << "\n";
        }
    }

    return 0;
}
