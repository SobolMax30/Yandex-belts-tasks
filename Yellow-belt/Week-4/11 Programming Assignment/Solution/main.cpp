#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct Operation {
    char type = 0;
    int number = 0;
};

bool NeedBrackets(char last, char current) {
    return (last == '+' || last == '-') && (current == '*' || current == '/');
}

int main() {
    int number;
    cin >> number;

    int operations_count;
    cin >> operations_count;

    vector<Operation> operations(operations_count);
    for (int i = 0; i < operations_count; ++i) {
        cin >> operations[i].type;
        cin >> operations[i].number;
    }

    deque<string> expression;
    expression.push_back(to_string(number));

    char last_type = '*';
    for (const auto& operation : operations) {
        if (NeedBrackets(last_type, operation.type)) {
            expression.push_front("(");
            expression.push_back(")");
        }

        expression.push_back(" ");
        expression.push_back(string(1, operation.type));
        expression.push_back(" ");
        expression.push_back(to_string(operation.number));

        last_type = operation.type;
    }

    for (const string& s : expression) {
        cout << s;
    }
    cout << endl;

    return 0;
}
