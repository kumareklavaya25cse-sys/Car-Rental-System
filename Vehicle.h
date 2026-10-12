#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
protected:
    int vehicleId;
    string model;
    double rate;
    bool status;

public:
    // Default constructor
    Vehicle();

    // Parameterized constructor
    Vehicle(int id, const string& modelName,
            double dailyRate, bool isAvailable = true);

    // Virtual destructor
    virtual ~Vehicle();

    // Supports runtime polymorphism
    virtual double calculateRent(int days) const;

    // Display vehicle details
    virtual void display() const;

    // Getters
    int getVehicleId() const;
    string getModel() const;
    double getRate() const;
    bool getStatus() const;

    // Setters
    void setModel(const string& modelName);
    void setRate(double dailyRate);
    void setStatus(bool isAvailable);
};

#endif