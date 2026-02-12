#include <iostream>
#include <exception>
#include <string>

using namespace std;

string AskTimeServer()
{
    //throw runtime_error("error");
    throw system_error(error_code());
    return "12:00:30";
}

class TimeServer
{
public:
    string GetCurrentTime()
    {
        try {
            LastFetchedTime = AskTimeServer();
        } catch (const system_error& system_err) {
            cout << system_err.what();
        }

        return LastFetchedTime;
    }
private:
    string LastFetchedTime = "00:00:00";
};

int main()
{
    TimeServer ts;
    try
    {
        cout << ts.GetCurrentTime() << endl;
    }
    catch (exception& e)
    {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
