#include <iostream>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& occupation) : Name(name), Occupation(occupation) {}

    string Get_Name() const {
        return Name;
    }

    string Get_Occupation() const {
        return Occupation;
    }

    virtual void Walk(const string& destination) const = 0;

private:
    string Name;
    string Occupation;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << "Student: " << Get_Name() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << Get_Name() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Get_Name() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << "Teacher: " << Get_Name() << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Teacher: " << Get_Name() << " walks to: " << destination << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(const Person& person) const {
        cout << "Policeman: " << Get_Name() << " checks " << person.Get_Occupation()<< ". "
             << person.Get_Occupation() << "'s name is: " << person.Get_Name() << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << Get_Name() << " walks to: " << destination << endl;
    }

};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
