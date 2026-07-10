#include <iostream>
#include <string>
using namespace std;

// Base class
class Ride
{
public:
    virtual void startRide()
    {
        cout << "Starting ride..." << endl;
    }

    virtual void rideDetails(double distance)
    {
        cout << "Fare for ride: " << distance * 78 << " units." << endl;
    }

    virtual ~Ride() = default;
};

// Derived class for Car
class Car : public Ride
{
public:
    void startRide() override
    {
        cout << "Starting Car ride..." << endl;
    }

    void rideDetails(double distance) override
    {
        cout << "Car ride for " << distance << " km with fare: " << distance * 100 << " units." << endl;
    }
};

// Derived class for Cng
class Cng : public Ride
{
public:
    void startRide() override
    {
        cout << "Starting Cng ride..." << endl;
    }

    void rideDetails(double distance) override
    {
        cout << "Cng ride for " << distance << " km with fare: " << distance * 60 << " units." << endl;
    }
};

// Derived class for Bike
class Bike : public Ride
{
public:
    void startRide() override
    {
        cout << "Starting Bike ride..." << endl;
    }

    void rideDetails(double distance) override
    {
        cout << "Bike ride for " << distance << " km with fare: " << distance * 50 << " units." << endl;
    }
};

// Single manageRide function
void manageRide(Ride &ride, double distance)
{
    ride.startRide();
    ride.rideDetails(distance);
}

int main()
{
    int choice;
    double distance;

    // Prompt user to choose a type of vehicle
    cout << "Select a type of vehicle:\n";
    cout << "1. Car\n";
    cout << "2. Cng\n";
    cout << "3. Bike\n";
    cout << "Enter choice (1-3): ";
    cin >> choice;

    // Prompt for distance
    cout << "Enter distance for the ride (in km): ";
    cin >> distance;

    // Create and manage the selected ride using polymorphism
    switch (choice)
    {
    case 1:
    {
        Car car;
        cout << "=== Car Ride ===" << endl;
        manageRide(car, distance);
        break;
    }
    case 2:
    {
        Cng cng;
        cout << "=== Cng Ride ===" << endl;
        manageRide(cng, distance);
        break;
    }
    case 3:
    {
        Bike bike;
        cout << "=== Bike Ride ===" << endl;
        manageRide(bike, distance);
        break;
    }
    default:
        cout << "Invalid choice. Please select a valid type of vehicle." << endl;
        return 1; // Exit with error
    }

    return 0;
}
