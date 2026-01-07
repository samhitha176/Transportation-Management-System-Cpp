#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- Classes --------------------

class Person {
protected:
    string name;
    int age;
public:
    void setDetails(const string& n, int a) {
        name = n;
        age = a;
    }
    string getName() const { return name; }
    int getAge() const { return age; }
};

class Driver : public Person {
    string licenseNumber;
public:
    void setDriverDetails(const string& n, int a, const string& lic) {
        setDetails(n, a);
        licenseNumber = lic;
    }
    string getLicense() const { return licenseNumber; }
    void displayDriver() const {
        cout << "Driver Name: " << name 
             << ", Age: " << age 
             << ", License: " << licenseNumber << endl;
    }
};

class Passenger : public Person {
public:
    void displayPassenger() const {
        cout << "Passenger Name: " << name << ", Age: " << age << endl;
    }
};

class Ride {
    static int idCounter;
    int rideID;
    string source;
    string destination;
    string driverName;
    string passengerName;
public:
    Ride() { rideID = ++idCounter; }
    void setRideDetails(const string& src, const string& dest, const string& dName, const string& pName) {
        source = src;
        destination = dest;
        driverName = dName;
        passengerName = pName;
    }
    int getRideID() const { return rideID; }
    void displayRide() const {
        cout << "Ride ID: " << rideID
             << ", Source: " << source
             << ", Destination: " << destination
             << ", Driver: " << driverName
             << ", Passenger: " << passengerName << endl;
    }
};

int Ride::idCounter = 0;

// -------------------- Main Management --------------------

class TransportSystem {
    vector<Driver> drivers;
    vector<Passenger> passengers;
    vector<Ride> rides;
public:
    void addDriver() {
        string name, license;
        int age;
        cout << "Enter Driver Name: ";
        cin.ignore(); getline(cin, name);
        cout << "Enter Age: "; cin >> age;
        cin.ignore();
        cout << "Enter License Number: ";
        getline(cin, license);

        Driver d;
        d.setDriverDetails(name, age, license);
        drivers.push_back(d);
        cout << "Driver added successfully!\n";
    }

    void addPassenger() {
        string name;
        int age;
        cout << "Enter Passenger Name: ";
        cin.ignore(); getline(cin, name);
        cout << "Enter Age: "; cin >> age;

        Passenger p;
        p.setDetails(name, age);
        passengers.push_back(p);
        cout << "Passenger added successfully!\n";
    }

    void addRide() {
        if (drivers.empty() || passengers.empty()) {
            cout << "Please add at least one driver and one passenger first.\n";
            return;
        }
        string src, dest;
        int driverIndex, passengerIndex;
        cout << "Enter Source: ";
        cin.ignore(); getline(cin, src);
        cout << "Enter Destination: ";
        getline(cin, dest);

        cout << "Select Driver by index:\n";
        for (size_t i = 0; i < drivers.size(); ++i) {
            cout << i+1 << ". "; drivers[i].displayDriver();
        }
        cin >> driverIndex;
        cout << "Select Passenger by index:\n";
        for (size_t i = 0; i < passengers.size(); ++i) {
            cout << i+1 << ". "; passengers[i].displayPassenger();
        }
        cin >> passengerIndex;

        Ride r;
        r.setRideDetails(src, dest, drivers[driverIndex-1].getName(), passengers[passengerIndex-1].getName());
        rides.push_back(r);
        cout << "Ride added successfully!\n";
    }

    void displayDrivers() const {
        cout << "\n--- Drivers List ---\n";
        for (const auto& d : drivers) d.displayDriver();
    }

    void displayPassengers() const {
        cout << "\n--- Passengers List ---\n";
        for (const auto& p : passengers) p.displayPassenger();
    }

    void displayRides() const {
        cout << "\n--- Rides List ---\n";
        for (const auto& r : rides) r.displayRide();
    }
};

// -------------------- Main --------------------

int main() {
    TransportSystem ts;
    int choice;

    do {
        cout << "\n--- Transportation Management System ---\n";
        cout << "1. Add Driver\n2. Add Passenger\n3. Add Ride\n4. Display Drivers\n5. Display Passengers\n6. Display Rides\n0. Exit\n";
        cout << "Enter your choice: "; cin >> choice;

        switch(choice) {
            case 1: ts.addDriver(); break;
            case 2: ts.addPassenger(); break;
            case 3: ts.addRide(); break;
            case 4: ts.displayDrivers(); break;
            case 5: ts.displayPassengers(); break;
            case 6: ts.displayRides(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    return 0;
}

