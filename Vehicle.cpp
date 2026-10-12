#include "Vehicle.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Default constructor
Vehicle::Vehicle()
    : vehicleId(0), model(""), rate(0.0), status(true) {
}

// Parameterized constructor
Vehicle::Vehicle(int id, const string& modelName,
                 double dailyRate, bool isAvailable)
    : vehicleId(id), model(modelName),
      rate(dailyRate), status(isAvailable) {
    if (dailyRate < 0) {
        throw invalid_argument("Daily rate cannot be negative.");
    }
}

// Virtual destructor
Vehicle::~Vehicle() {
}

// Calculate rent
double Vehicle::calculateRent(int days) const {
    if (days <= 0) {
        throw invalid_argument("Rental days must be greater than zero.");
    }

    return rate * days;
}

// Display vehicle details
void Vehicle::display() const {
    cout << "Vehicle ID: " << vehicleId
         << " | Model: " << model
         << " | Daily Rate: " << rate
         << " | Status: "
         << (status ? "Available" : "Rented")
         << '\n';
}

// Getters
int Vehicle::getVehicleId() const {
    return vehicleId;
}

string Vehicle::getModel() const {
    return model;
}

double Vehicle::getRate() const {
    return rate;
}

bool Vehicle::getStatus() const {
    return status;
}

// Setters
void Vehicle::setModel(const string& modelName) {
    model = modelName;
}

void Vehicle::setRate(double dailyRate) {
    if (dailyRate < 0) {
        throw invalid_argument("Daily rate cannot be negative.");
    }

    rate = dailyRate;
}

void Vehicle::setStatus(bool isAvailable) {
    status = isAvailable;
}