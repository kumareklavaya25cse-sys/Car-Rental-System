#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <string>
using namespace std;

class Car : public Vehicle {
private:
    int seats;
    string fuelType;

public:
    // Default constructor
    Car();

    // Parameterized constructor
    Car(int id, const string& modelName,
        double dailyRate, int numberOfSeats,
        const string& fuel);

    // Destructor
    ~Car() override;

    // Override base-class functions
    double calculateRent(int days) const override;
    void display() const override;

    // Getters
    int getSeats() const;
    string getFuelType() const;

    // Setters
    void setSeats(int numberOfSeats);
    void setFuelType(const string& fuel);
};

#endif