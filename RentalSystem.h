#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include "Vehicle.h"
#include "Car.h"
#include "Customer.h"
#include "Rental.h"
#include "FileManager.h"

class RentalSystem {
public:
    // Maximum number of records supported
    static const int CAPACITY = 100;

private:
    // Dynamically allocated arrays
    Vehicle** vehicles;
    Customer* customers;
    Rental* rentals;

    // Number of stored records
    int vehicleCount;
    int customerCount;
    int rentalCount;

    // IDs for new records
    int nextVehicleId;
    int nextCustomerId;
    int nextRentalId;

    // Allow FileManager to access records for saving/loading
    friend class FileManager;

    // Menu operation functions
    void addVehicle();
    void addCustomer();
    void displayRecords();
    void searchRecord();
    void updateRecord();
    void deleteRecord();
    void rentVehicle();
    void returnVehicle();
    void displayReport();

public:
    // Constructor and destructor
    RentalSystem();
    ~RentalSystem();

    // Run the application menu
    void run();

    // Save and load data
    void saveData();
    void loadData();
};

#endif