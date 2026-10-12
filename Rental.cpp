#include "Rental.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Default constructor
Rental::Rental()
    : rentalId(0), vehicleId(0), customerId(0),
      days(0), amount(0.0), active(false) {
}

// Parameterized constructor
Rental::Rental(int id, int vId, int cId,
               int rentalDays, double rentalAmount)
    : rentalId(id), vehicleId(vId), customerId(cId),
      days(rentalDays), amount(rentalAmount), active(true) {

    if (rentalDays <= 0) {
        throw invalid_argument("Rental days must be greater than zero.");
    }

    if (rentalAmount < 0) {
        throw invalid_argument("Rental amount cannot be negative.");
    }
}

// Destructor
Rental::~Rental() {
}

// Calculate rental bill
double Rental::calculateBill(double dailyRate) const {
    if (days <= 0) {
        throw invalid_argument("Rental days must be greater than zero.");
    }

    if (dailyRate < 0) {
        throw invalid_argument("Daily rate cannot be negative.");
    }

    return dailyRate * days;
}

// Close a rental
void Rental::closeRental() {
    active = false;
}

// Display rental details
void Rental::display() const {
    cout << "Rental ID: " << rentalId
         << " | Vehicle ID: " << vehicleId
         << " | Customer ID: " << customerId
         << " | Days: " << days
         << " | Amount: " << amount
         << " | Status: " << (active ? "Active" : "Returned")
         << '\n';
}

// Getters
int Rental::getRentalId() const {
    return rentalId;
}

int Rental::getVehicleId() const {
    return vehicleId;
}

int Rental::getCustomerId() const {
    return customerId;
}

int Rental::getDays() const {
    return days;
}

double Rental::getAmount() const {
    return amount;
}

bool Rental::isActive() const {
    return active;
}

// Setters
void Rental::setDays(int rentalDays) {
    if (rentalDays <= 0) {
        throw invalid_argument("Rental days must be greater than zero.");
    }

    days = rentalDays;
}

void Rental::setAmount(double rentalAmount) {
    if (rentalAmount < 0) {
        throw invalid_argument("Rental amount cannot be negative.");
    }

    amount = rentalAmount;
}