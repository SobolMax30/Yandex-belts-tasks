#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.14;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c) : side_a(a), side_b(b), side_c(c) {}

    string Name() const override {
        return "TRIANGLE";
    }

    double Perimeter() const override {
        return side_a + side_b + side_c;
    }

    double Area() const override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - side_a) * (p - side_b) * (p - side_c));
    }

private:
    int side_a;
    int side_b;
    int side_c;
};

class Rect : public Figure {
public:
    Rect(int w, int h) : width(w), height(h) {}

    string Name() const override {
        return "RECT";
    }

    double Perimeter() const override {
        return 2 * (width + height);
    }

    double Area() const override {
        return width * height;
    }

private:
    int width;
    int height;
};

class Circle : public Figure {
public:
    Circle(double r) : radius(r) {}

    string Name() const override {
        return "CIRCLE";
    }

    double Perimeter() const override {
        return 2 * PI * radius;
    }

    double Area() const override {
        return PI * pow(radius, 2);
    }

private:
    double radius;
};

shared_ptr<Figure> CreateFigure(istream& input) {
    string type;
    input >> type;

    if (type == "RECT") {
        int width, height;
        input >> width >> height;
        return make_shared<Rect>(width, height);
    } else if (type == "TRIANGLE") {
        int side_one, side_two, side_three;
        input >> side_one >> side_two >> side_three;
        return make_shared<Triangle>(side_one, side_two, side_three);
    } else {
        int radius;
        input >> radius;

        return make_shared<Circle>(radius);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;

        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }

    return 0;
}
