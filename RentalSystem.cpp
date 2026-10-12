#include "RentalSystem.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

// Constructor
RentalSystem::RentalSystem()
    : vehicles(new Vehicle*[CAPACITY]()),
      customers(new Customer[CAPACITY]),
      rentals(new Rental[CAPACITY]),
      vehicleCount(0),
      customerCount(0),
      rentalCount(0),
      nextVehicleId(1),
      nextCustomerId(1),
      nextRentalId(1) {
}

// Destructor
RentalSystem::~RentalSystem() {
    for (int i = 0; i < vehicleCount; ++i) {
        delete vehicles[i];
    }

    delete[] vehicles;
    delete[] customers;
    delete[] rentals;
}

// Main menu
void RentalSystem::run() {
    loadData();

    int choice = 0;

    do {
        cout << "\n========== CAR RENTAL SYSTEM ==========\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Main Transaction / Process\n";
        cout << "7. Report\n";
        cout << "8. Save / Load\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from 1 to 9.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: {
                    int type;
                    cout << "1. Add Vehicle\n";
                    cout << "2. Add Customer\n";
                    cout << "Choose record type: ";

                    if (!(cin >> type)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid record type.\n";
                        break;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (type == 1) {
                        addVehicle();
                    } else if (type == 2) {
                        addCustomer();
                    } else {
                        cout << "Invalid record type.\n";
                    }
                    break;
                }

                case 2:
                    displayRecords();
                    break;

                case 3:
                    searchRecord();
                    break;

                case 4:
                    updateRecord();
                    break;

                case 5:
                    deleteRecord();
                    break;

                case 6: {
                    int transactionChoice;

                    cout << "\n1. Rent Vehicle\n";
                    cout << "2. Return Vehicle\n";
                    cout << "Choose transaction: ";

                    if (!(cin >> transactionChoice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid transaction choice.\n";
                        break;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (transactionChoice == 1) {
                        rentVehicle();
                    } else if (transactionChoice == 2) {
                        returnVehicle();
                    } else {
                        cout << "Invalid transaction choice.\n";
                    }
                    break;
                }

                case 7:
                    displayReport();
                    break;

                case 8: {
                    int fileChoice;

                    cout << "\n1. Save Records\n";
                    cout << "2. Load Records\n";
                    cout << "Choose option: ";

                    if (!(cin >> fileChoice)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid file option.\n";
                        break;
                    }

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (fileChoice == 1) {
                        saveData();
                    } else if (fileChoice == 2) {
                        loadData();
                    } else {
                        cout << "Invalid file option.\n";
                    }
                    break;
                }

                case 9:
                    saveData();
                    cout << "Records saved. Exiting program.\n";
                    break;

                default:
                    cout << "Please choose a number from 1 to 9.\n";
            }
        } catch (const exception& e) {
            cout << "Operation failed: " << e.what() << '\n';
        }

    } while (choice != 9);
}

// Add a vehicle
void RentalSystem::addVehicle() {
    if (vehicleCount >= CAPACITY) {
        cout << "Vehicle storage is full.\n";
        return;
    }

    string modelName;
    string fuel;
    int seats;
    double dailyRate;

    cout << "Enter vehicle model: ";
    getline(cin, modelName);

    if (modelName.empty()) {
        cout << "Model cannot be empty.\n";
        return;
    }

    cout << "Enter daily rental rate: ";

    if (!(cin >> dailyRate) || dailyRate < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid rental rate.\n";
        return;
    }

    cout << "Enter number of seats: ";

    if (!(cin >> seats) || seats <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of seats.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter fuel type: ";
    getline(cin, fuel);

    if (fuel.empty()) {
        cout << "Fuel type cannot be empty.\n";
        return;
    }

    vehicles[vehicleCount] =
        new Car(nextVehicleId, modelName, dailyRate, seats, fuel);

    cout << "Vehicle added successfully. Vehicle ID: "
         << nextVehicleId << '\n';

    ++vehicleCount;
    ++nextVehicleId;
}

// Add a customer
void RentalSystem::addCustomer() {
    if (customerCount >= CAPACITY) {
        cout << "Customer storage is full.\n";
        return;
    }

    string name;
    string phone;

    cout << "Enter customer name: ";
    getline(cin, name);

    cout << "Enter customer phone: ";
    getline(cin, phone);

    customers[customerCount] =
        Customer(nextCustomerId, name, phone);

    cout << "Customer added successfully. Customer ID: "
         << nextCustomerId << '\n';

    ++customerCount;
    ++nextCustomerId;
}

// Display all records
void RentalSystem::displayRecords() {
    cout << "\n--- Vehicles ---\n";

    if (vehicleCount == 0) {
        cout << "No vehicles recorded.\n";
    }

    for (int i = 0; i < vehicleCount; ++i) {
        vehicles[i]->display();
    }

    cout << "\n--- Customers ---\n";

    if (customerCount == 0) {
        cout << "No customers recorded.\n";
    }

    for (int i = 0; i < customerCount; ++i) {
        customers[i].display();
    }

    cout << "\n--- Rentals ---\n";

    if (rentalCount == 0) {
        cout << "No rentals recorded.\n";
    }

    for (int i = 0; i < rentalCount; ++i) {
        rentals[i].display();
    }
}

// Search records
void RentalSystem::searchRecord() {
    int type;
    int id;

    cout << "Search: 1. Vehicle  2. Customer  3. Rental\n";
    cout << "Choose record type: ";

    if (!(cin >> type)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid record type.\n";
        return;
    }

    cout << "Enter record ID: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (type == 1) {
        for (int i = 0; i < vehicleCount; ++i) {
            if (vehicles[i]->getVehicleId() == id) {
                vehicles[i]->display();
                return;
            }
        }
    } else if (type == 2) {
        for (int i = 0; i < customerCount; ++i) {
            if (customers[i].getCustomerId() == id) {
                customers[i].display();
                return;
            }
        }
    } else if (type == 3) {
        for (int i = 0; i < rentalCount; ++i) {
            if (rentals[i].getRentalId() == id) {
                rentals[i].display();
                return;
            }
        }
    } else {
        cout << "Invalid record type.\n";
        return;
    }

    cout << "Record not found.\n";
}

// Update a customer
void RentalSystem::updateRecord() {
    int id;

    cout << "Enter customer ID to update: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].getCustomerId() == id) {
            string name;
            string phone;

            cout << "Enter new customer name: ";
            getline(cin, name);

            cout << "Enter new phone number: ";
            getline(cin, phone);

            customers[i].update(name, phone);
            cout << "Customer updated successfully.\n";
            return;
        }
    }

    cout << "Customer not found.\n";
}

// Delete a vehicle
void RentalSystem::deleteRecord() {
    int id;

    cout << "Enter vehicle ID to delete: ";

    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicles[i]->getVehicleId() == id) {
            for (int j = 0; j < rentalCount; ++j) {
                if (rentals[j].getVehicleId() == id &&
                    rentals[j].isActive()) {
                    cout << "Cannot delete a vehicle with an active rental.\n";
                    return;
                }
            }

            delete vehicles[i];

            for (int j = i; j < vehicleCount - 1; ++j) {
                vehicles[j] = vehicles[j + 1];
            }

            vehicles[vehicleCount - 1] = nullptr;
            --vehicleCount;

            cout << "Vehicle deleted successfully.\n";
            return;
        }
    }

    cout << "Vehicle not found.\n";
}

// Rent a vehicle
void RentalSystem::rentVehicle() {
    if (rentalCount >= CAPACITY) {
        cout << "Rental storage is full.\n";
        return;
    }

    int vehicleId;
    int customerId;
    int days;

    cout << "Enter vehicle ID: ";

    if (!(cin >> vehicleId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid vehicle ID.\n";
        return;
    }

    cout << "Enter customer ID: ";

    if (!(cin >> customerId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid customer ID.\n";
        return;
    }

    cout << "Enter number of rental days: ";

    if (!(cin >> days) || days <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Rental days must be greater than zero.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Vehicle* selectedVehicle = nullptr;
    bool customerFound = false;

    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicles[i]->getVehicleId() == vehicleId) {
            selectedVehicle = vehicles[i];
            break;
        }
    }

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].getCustomerId() == customerId) {
            customerFound = true;
            break;
        }
    }

    if (selectedVehicle == nullptr) {
        cout << "Vehicle not found.\n";
        return;
    }

    if (!customerFound) {
        cout << "Customer not found. Add the customer first.\n";
        return;
    }

    if (!selectedVehicle->getStatus()) {
        cout << "Vehicle is already rented.\n";
        return;
    }

    double bill = selectedVehicle->calculateRent(days);

    rentals[rentalCount] =
        Rental(nextRentalId, vehicleId, customerId, days, bill);

    selectedVehicle->setStatus(false);

    cout << "Rental successful. Rental ID: " << nextRentalId
         << " | Total bill: " << bill << '\n';

    ++rentalCount;
    ++nextRentalId;
}

// Return a vehicle
void RentalSystem::returnVehicle() {
    int rentalId;

    cout << "Enter rental ID to return: ";

    if (!(cin >> rentalId)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid rental ID.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < rentalCount; ++i) {
        if (rentals[i].getRentalId() == rentalId &&
            rentals[i].isActive()) {

            rentals[i].closeRental();

            for (int j = 0; j < vehicleCount; ++j) {
                if (vehicles[j]->getVehicleId() ==
                    rentals[i].getVehicleId()) {
                    vehicles[j]->setStatus(true);
                    break;
                }
            }

            cout << "Vehicle returned successfully.\n";
            return;
        }
    }

    cout << "Active rental not found.\n";
}

// Display rental report
void RentalSystem::displayReport() {
    cout << "\n========== RENTAL REPORT ==========\n";
    cout << "Total vehicles: " << vehicleCount << '\n';
    cout << "Total customers: " << customerCount << '\n';
    cout << "Total rentals: " << rentalCount << '\n';

    int activeRentals = 0;
    double totalRevenue = 0.0;

    for (int i = 0; i < rentalCount; ++i) {
        totalRevenue += rentals[i].getAmount();

        if (rentals[i].isActive()) {
            ++activeRentals;
        }
    }

    cout << "Active rentals: " << activeRentals << '\n';
    cout << "Total recorded rental revenue: " << totalRevenue << '\n';
}

// Save records
void RentalSystem::saveData() {
    FileManager manager;
    manager.save(*this);
}

// Load records
void RentalSystem::loadData() {
    FileManager manager;
    manager.load(*this);
}