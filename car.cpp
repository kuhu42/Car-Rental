

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Car {
private:
    string make;
    string model;
    int year;
    double rental_price;
    bool available;

public:
    Car(string make, string model, int year, double rental_price) {
        this->make = make;
        this->model = model;
        this->year = year;
        this->rental_price = rental_price;
        this->available = true;
    }

    string get_make() const {
        return make;
    }

    string get_model() const {
        return model;
    }

    int get_year() const {
        return year;
    }

    double get_rental_price() const {
        return rental_price;
    }

    bool is_available() const {
        return available;
    }

    void rent_out() {
        available = false;
    }

    void return_car() {
        available = true;
    }

    void display() const {
        cout << make << " " << model << " (" << year << ") - Rental Price: Rs" << rental_price;
        if (available) {
            cout << " - Available" << endl;
        } else {
            cout << " - Not Available" << endl;
        }
    }
};

class RentalSystem {
private:
    vector<Car*> cars;

public:
    RentalSystem() {
        cars.push_back(new Car("Honda", "Civic", 2018, 50000.0));
        cars.push_back(new Car("Toyota", "Camry", 2019, 60000.0));
        cars.push_back(new Car("Ford", "Mustang", 2020, 70000.0));
    }

    ~RentalSystem() {
        for (Car* car : cars) {
            delete car;
        }
    }

    void rent_car() {
        int index, duration;
        cout << "Enter car index and rental duration (in days): ";
        cin >> index >> duration;
        if (index < 0 || index >= cars.size()) {
            cout << "Invalid car index." << endl;
            return;
        }
        Car* car = cars[index];
        if (!car->is_available()) {
            cout << "Car not available." << endl;
            return;
        }
        car->rent_out();
        double price = duration * car->get_rental_price();
        string model= car->get_model();
        string make= car->get_make();
        int year= car->get_year();
        cout << "Rental successful." << endl;
        cout << "Invoice:" << endl;
        cout << "Make and model: " << make << " " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Your total price is: Rs" << price << endl;
        cout << "----------------------" << endl;
    }

    void return_car() {
        string make, model;
        int year, duration;
        cout << "Enter car make, model, and year: ";
        cin >> make >> model >> year;
        cout << "Enter rental duration (in days): ";
        cin >> duration;
        bool car_found = false;
        for (Car* car : cars) {
            if (car->get_make() == make && car->get_model() == model && car->get_year() == year) {
                car_found = true;
                if (car->is_available()) {
                    cout << "Car not rented." << endl;
                    return;
                }
                car->return_car();
                double refund = duration * car->get_rental_price();
                cout << "Return successful." << endl;
                cout << "Your total refund is: Rs" << refund << endl;
                return;
            }
        }
        if (!car_found) {
            cout << "Car not found." << endl;
        }
    }

    void display_available_cars() const {
        cout << "Available cars:" << endl;
        bool found = false;
    for (Car* car : cars) {
        if (car->is_available()) {
            car->display();
            found = true;
        }
    }
    if (!found) {
        cout << "No available cars." << endl;
    }
}

void display_rented_cars() const {
    cout << "Rented cars:" << endl;
    bool found = false;
    for (Car* car : cars) {
        if (!car->is_available()) {
            car->display();
            found = true;
        }
    }
    if (!found) {
        cout << "No rented cars." << endl;
    }
}

void cancel_rental() {
    string make, model;
    int year, duration;
    cout << "Enter car make, model, and year: ";
    cin >> make >> model >> year;
    cout << "Enter rental duration (in days): ";
    cin >> duration;
    bool car_found = false;
    for (Car* car : cars) {
        if (car->get_make() == make && car->get_model() == model && car->get_year() == year) {
            car_found = true;
            if (car->is_available()) {
                cout << "Car not rented." << endl;
                return;
            }
            car->return_car();
            double refund = duration * car->get_rental_price();
            cout << "Cancellation successful." << endl;
            cout << "Your total refund is: Rs" << refund << endl;
            return;
        }
    }
    if (!car_found) {
        cout << "Car not found." << endl;
    }
}};

int main() {
RentalSystem rental_system;
int choice;
do {
    cout << "Welcome to the car rental system." << endl;
    cout << "1. Rent a car" << endl;
    cout << "2. Return a car" << endl;
    cout << "3. Display available cars" << endl;
    cout << "4. Display rented cars" << endl;
    cout << "5. Cancel rental" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case 1:
            rental_system.rent_car();
            break;
        case 2:
            rental_system.return_car();
            break;
        case 3:
            rental_system.display_available_cars();
            break;
        case 4:
            rental_system.display_rented_cars();
            break;
        case 5:
            rental_system.cancel_rental();
            break;
        case 6:
            cout << "Thank you for using the car rental system." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
    }
} while (choice != 6);

return 0;
}