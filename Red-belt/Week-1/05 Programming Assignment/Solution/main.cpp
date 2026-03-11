#include "test_runner.h"

#include <ostream>

using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, "yellow belt\n", "red belt");
        ASSERT_EQUAL(output.str(), "yellow belt\n\nred belt\n");
    }, "PRINT_VALUES usage example");

    return 0;
}
