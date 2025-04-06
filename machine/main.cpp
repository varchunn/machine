#include <iostream>
#include <string>
using namespace std;

class Prototype {
public:
    virtual Prototype* clone() const = 0;
    virtual ~Prototype() = default;
};

class Engine : public Prototype {
public:
    string type;
    int horsepower;

    Engine(string t, int hp) : type(t), horsepower(hp) {}

    Prototype* clone() const override {
        return new Engine(*this);
    }

    void print() const {
        cout << "Engine: " << type << ", " << horsepower << " HP\n";
    }
};

class Transmission : public Prototype {
public:
    string type;
    int gears;

    Transmission(string t, int g) : type(t), gears(g) {}

    Prototype* clone() const override {
        return new Transmission(*this);
    }

    void print() const {
        cout << "Transmission: " << type << ", " << gears << " gears\n";
    }
};

class Manufacturer : public Prototype {
public:
    string name;
    string country;

    Manufacturer(string n, string c) : name(n), country(c) {}

    Prototype* clone() const override {
        return new Manufacturer(*this);
    }

    void print() const {
        cout << "Manufacturer: " << name << ", " << country << endl;
    }
};

class Chassis : public Prototype {
public:
    string material;

    Chassis(string m) : material(m) {}

    Prototype* clone() const override {
        return new Chassis(*this);
    }

    void print() const {
        cout << "Chassis: " << material << endl;
    }
};

class Interior : public Prototype {
public:
    string color;
    string seatMaterial;

    Interior(string c, string s) : color(c), seatMaterial(s) {}

    Prototype* clone() const override {
        return new Interior(*this);
    }

    void print() const {
        cout << "Interior: " << color << ", " << seatMaterial << endl;
    }
};

class Car : public Prototype 
{
public:
    Engine* engine;
    Transmission* transmission;
    Manufacturer* manufacturer;
    Chassis* chassis;
    Interior* interior;

    Car(Engine* e, Transmission* t, Manufacturer* m, Chassis* c, Interior* i)
        : engine(e), transmission(t), manufacturer(m), chassis(c), interior(i) {}

    // Копіювання (Прототип)
    Prototype* clone() const override {
        return new Car(
            dynamic_cast<Engine*>(engine->clone()),
            dynamic_cast<Transmission*>(transmission->clone()),
            dynamic_cast<Manufacturer*>(manufacturer->clone()),
            dynamic_cast<Chassis*>(chassis->clone()),
            dynamic_cast<Interior*>(interior->clone())
        );
    }

    void printDetails() const {
        cout << "Car Details:\n";
        engine->print();
        transmission->print();
        manufacturer->print();
        chassis->print();
        interior->print();
    }

    ~Car() {
        delete engine;
        delete transmission;
        delete manufacturer;
        delete chassis;
        delete interior;
    }
};

int main() {
    
    Car* originalCar = new Car(
        new Engine("V8", 450),
        new Transmission("Automatic", 8),
        new Manufacturer("Tesla", "USA"),
        new Chassis("Aluminum"),
        new Interior("Black", "Leather")
    );

    cout << "Original Car:\n";
    originalCar->printDetails();

    Car* clonedCar = dynamic_cast<Car*>(originalCar->clone());

    clonedCar->engine->horsepower = 500;
    clonedCar->manufacturer->name = "Lucid Motors";

    cout << "\n Cloned Car (Modified):\n";
    clonedCar->printDetails();

    cout << "\n Original Car (Unchanged):\n";
    originalCar->printDetails();

    delete originalCar;
    delete clonedCar;

    return 0;
}
