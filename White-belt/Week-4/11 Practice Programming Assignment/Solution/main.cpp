#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int GCD(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}

class Rational
{
public:
    Rational()
    {
        numerator = 0;
        denominator = 1;
    }

    Rational(int new_numerator, int new_denominator)
    {
        if (new_denominator == 0) {
            throw invalid_argument("Invalid argument");
        }
        const int gcd = GCD(new_numerator, new_denominator);
        numerator = new_numerator / gcd;
        denominator = new_denominator / gcd;
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

    int Numerator() const
    {
        return numerator;
    }

    int Denominator() const
    {
        return denominator;
    }
private:
    int numerator;
    int denominator;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return {
        lhs.Numerator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& stream, Rational& rational) {
    int num, denum;
    char c;

    if (stream) {
        stream >> num >> c >> denum;

        if (stream && c == '/') {
            rational = Rational(num, denum);
        }
    }

    return stream;
}

ostream& operator << (ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();

    return stream;
}

int main() {
    Rational r1, r2;
    char operation;
    try {
        cin >> r1 >> operation >> r2;
        if (operation == '+') {
            cout << r1 + r2 << endl;
        } else if (operation == '-') {
            cout << r1 - r2 << endl;
        } else if (operation == '*') {
            cout << r1 * r2 << endl;
        } else if (operation == '/') {
            try {
                cout << r1 / r2 << endl;
            } catch (domain_error& derr) {
                cout << derr.what();
            }
        }
    } catch (invalid_argument& iarg) {
        cout << iarg.what();
    }

    return 0;
}
