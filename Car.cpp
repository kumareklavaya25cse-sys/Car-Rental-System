#include "Car.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Default constructor
Car::Car()
    : Vehicle(), seats(5), fuelType("Petrol") {
}

// Parameterized constructor
Car::Car(int id, const string& modelName,
         double dailyRate, int numberOfSeats,
         const string& fuel)
    : Vehicle(id, modelName, dailyRate),
      seats(numberOfSeats), fuelType(fuel) {

    if (numberOfSeats <= 0) {
        throw invalid_argument("Number of seats must be positive.");
    }

    if (fuel.empty()) {
        throw invalid_argument("Fuel type cannot be empty.");
    }
}

// Destructor
Car::~Car() {
}

// Calculate rental cost
double Car::calculateRent(int days) const {
    return Vehicle::calculateRent(days);
}

// Display car details
void Car::display() const {
    Vehicle::display();

    cout << "Seats: " << seats
         << " | Fuel Type: " << fuelType
         << '\n';
}

// Getters
int Car::getSeats() const {
    return seats;
}

string Car::getFuelType() const {
    return fuelType;
}

// Setters
void Car::setSeats(int numberOfSeats) {
    if (numberOfSeats <= 0) {
        throw invalid_argument("Number of seats must be positive.");
    }

    seats = numberOfSeats;
}

void Car::setFuelType(const string& fuel) {
    if (fuel.empty()) {
        throw invalid_argument("Fuel type cannot be empty.");
    }

    fuelType = fuel;
}