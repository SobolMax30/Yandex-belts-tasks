#include <string>
#include <vector>

using namespace std;

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
#define UNIQUE_ID CONCAT(var_, __LINE__)

int main() {
    int UNIQUE_ID = 0;
    string UNIQUE_ID = "hello";
    vector<string> UNIQUE_ID = {"hello", "world"};
    vector<int> UNIQUE_ID = {1, 2, 3, 4};

    return 0;
}
