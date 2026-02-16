#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date(int year, int month, int day) {
		this->year = year;
		if (month > 12 || month < 1) {
			throw logic_error("Month value is invalid: " + to_string(month));
		}
		this->month = month;
		if (day > 31 || day < 1) {
			throw logic_error("Day value is invalid: " + to_string(day));
		}
		this->day = day;
	}
	int getYear() const {
		return year;
	}
	int getMonth() const {
		return month;
	}
	int getDay() const {
		return day;
	}
};

bool operator < (const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.getYear(), lhs.getMonth(), lhs.getDay()} < vector<int>{rhs.getYear(), rhs.getMonth(), rhs.getDay()};
}

ostream& operator << (ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.getYear() << "-" << setw(2) << setfill('0') << date.getMonth() <<
      "-" << setw(2) << setfill('0') << date.getDay();
  return stream;
}

class Database {
private:
	map<Date, set<string>> storage;
public:
	void addEvent(const Date& date, const string& event) {
		storage[date].insert(event);
	}
	bool deleteEvent(const Date& date, const string& event) {
		if (storage.count(date) > 0 && storage[date].count(event) > 0) {
			storage[date].erase(event);
			return true;
		}
		return false;
	}
	int deleteDate(const Date& date) {
		if (storage.count(date) == 0) {
			return 0;
		} else {
			int eventCount = storage[date].size();
			storage.erase(date);
			return eventCount;
		}
	}
	set<string> find(const Date& date) const {
		if (storage.count(date) > 0) {
			return storage.at(date);
		} else {
			return {};
		}
	}
	void print() const {
		for (const auto& item : storage) {
			for (const string& event : item.second) {
				cout << item.first << " " << event << endl;
			}
		}
	}
};

Date parseDate(const string& date) {
    stringstream stream(date);
    int year, month, day;
    char sep1, sep2;

    if (!(stream >> year >> sep1 >> month >> sep2 >> day) || sep1 != '-' || sep2 != '-') {
        throw logic_error("Wrong date format: " + date);
    }

	return Date(year, month, day);
}

int main()
{
	try {
		Database db;

		string commandLine;
		while (getline(cin, commandLine))
		{
			stringstream ss(commandLine);

			string command;
			ss >> command;

			if (command == "Add") {
				string str_date, event;
				ss >> str_date >> event;
				Date date = parseDate(str_date);
				db.addEvent(date, event);
			} else if (command == "Del") {
				string str_date, event;
				ss >> str_date;
				Date date = parseDate(str_date);

				if(!ss.eof()) {
					ss >> event;
				}

				if (event.empty()) {
					const int count = db.deleteDate(date);
					cout << "Deleted " << count << " events" << endl;
				} else {
					if (db.deleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					} else {
						cout << "Event not found" << endl;
					}
				}
			} else if (command == "Print") {
				db.print();
			} else if (command == "Find") {
				string str_date;
				ss >> str_date;
				Date date = parseDate(str_date);
				for (const string& event : db.find(date)) {
				  cout << event << endl;
				}
			} else if (!command.empty()) {
				throw logic_error("Unknown command: " + command);
			}
		}
	} catch (exception& e) {
	    cout << e.what() << endl;
	}

	return 0;
}
