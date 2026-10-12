#include "FileManager.h"
#include "RentalSystem.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Save all records to text files
void FileManager::save(const RentalSystem& system) {
    ofstream vehicleFile("vehicles.txt");
    ofstream customerFile("customers.txt");
    ofstream rentalFile("rentals.txt");

    if (!vehicleFile || !customerFile || !rentalFile) {
        throw ios_base::failure(
            "Unable to open data files for saving."
        );
    }

    // Save vehicles
    for (int i = 0; i < system.vehicleCount; ++i) {
        Vehicle* vehicle = system.vehicles[i];

        vehicleFile
            << vehicle->getVehicleId() << '|'
            << vehicle->getModel() << '|'
            << vehicle->getRate() << '|'
            << vehicle->getStatus() << '\n';
    }

    // Save customers
    for (int i = 0; i < system.customerCount; ++i) {
        const Customer& customer = system.customers[i];

        customerFile
            << customer.getCustomerId() << '|'
            << customer.getName() << '|'
            << customer.getPhone() << '\n';
    }

    // Save rentals
    for (int i = 0; i < system.rentalCount; ++i) {
        const Rental& rental = system.rentals[i];

        rentalFile
            << rental.getRentalId() << '|'
            << rental.getVehicleId() << '|'
            << rental.getCustomerId() << '|'
            << rental.getDays() << '|'
            << rental.getAmount() << '|'
            << rental.isActive() << '\n';
    }

    if (!vehicleFile || !customerFile || !rentalFile) {
        throw ios_base::failure(
            "An error occurred while saving records."
        );
    }

    cout << "All records saved successfully.\n";
}

// Load all records from text files
void FileManager::load(RentalSystem& system) {
    ifstream vehicleFile("vehicles.txt");
    ifstream customerFile("customers.txt");
    ifstream rentalFile("rentals.txt");

    // Start with empty records if no data files exist.
    if (!vehicleFile && !customerFile && !rentalFile) {
        cout << "No saved records found. Starting with empty records.\n";
        return;
    }

    // Clear existing vehicles.
    for (int i = 0; i < system.vehicleCount; ++i) {
        delete system.vehicles[i];
        system.vehicles[i] = nullptr;
    }

    system.vehicleCount = 0;
    system.customerCount = 0;
    system.rentalCount = 0;

    string line;

    // Load vehicles
    if (vehicleFile) {
        while (getline(vehicleFile, line)) {
            if (system.vehicleCount >= RentalSystem::CAPACITY) {
                break;
            }

            size_t p1 = line.find('|');
            size_t p2 = line.find('|',
                p1 == string::npos ? p1 : p1 + 1);
            size_t p3 = line.find('|',
                p2 == string::npos ? p2 : p2 + 1);

            if (p1 == string::npos ||
                p2 == string::npos ||
                p3 == string::npos) {
                continue;
            }

            try {
                int id = stoi(line.substr(0, p1));
                string model = line.substr(p1 + 1, p2 - p1 - 1);
                double rate = stod(line.substr(p2 + 1, p3 - p2 - 1));
                bool status = (stoi(line.substr(p3 + 1)) != 0);

                // Restore the saved vehicle as a Car.
                system.vehicles[system.vehicleCount] =
                    new Car(id, model, rate, 5, "Unknown");

                system.vehicles[system.vehicleCount]->setStatus(status);
                ++system.vehicleCount;

                if (id >= system.nextVehicleId) {
                    system.nextVehicleId = id + 1;
                }
            } catch (...) {
                cout << "Skipping an invalid vehicle record.\n";
            }
        }
    }

    // Load customers
    if (customerFile) {
        while (getline(customerFile, line)) {
            if (system.customerCount >= RentalSystem::CAPACITY) {
                break;
            }

            size_t p1 = line.find('|');
            size_t p2 = line.find('|',
                p1 == string::npos ? p1 : p1 + 1);

            if (p1 == string::npos || p2 == string::npos) {
                continue;
            }

            try {
                int id = stoi(line.substr(0, p1));
                string name = line.substr(p1 + 1, p2 - p1 - 1);
                string phone = line.substr(p2 + 1);

                system.customers[system.customerCount] =
                    Customer(id, name, phone);
                ++system.customerCount;

                if (id >= system.nextCustomerId) {
                    system.nextCustomerId = id + 1;
                }
            } catch (...) {
                cout << "Skipping an invalid customer record.\n";
            }
        }
    }

    // Load rentals
    if (rentalFile) {
        while (getline(rentalFile, line)) {
            if (system.rentalCount >= RentalSystem::CAPACITY) {
                break;
            }

            size_t positions[5];
            size_t start = 0;
            bool valid = true;

            for (int i = 0; i < 5; ++i) {
                positions[i] = line.find('|', start);

                if (positions[i] == string::npos) {
                    valid = false;
                    break;
                }

                start = positions[i] + 1;
            }

            if (!valid) {
                continue;
            }

            try {
                int id = stoi(line.substr(0, positions[0]));
                int vehicleId = stoi(line.substr(
                    positions[0] + 1,
                    positions[1] - positions[0] - 1));
                int customerId = stoi(line.substr(
                    positions[1] + 1,
                    positions[2] - positions[1] - 1));
                int days = stoi(line.substr(
                    positions[2] + 1,
                    positions[3] - positions[2] - 1));
                double amount = stod(line.substr(
                    positions[3] + 1,
                    positions[4] - positions[3] - 1));
                bool active =
                    (stoi(line.substr(positions[4] + 1)) != 0);

                Rental rental(id, vehicleId, customerId, days, amount);

                if (!active) {
                    rental.closeRental();
                }

                system.rentals[system.rentalCount] = rental;
                ++system.rentalCount;

                if (id >= system.nextRentalId) {
                    system.nextRentalId = id + 1;
                }
            } catch (...) {
                cout << "Skipping an invalid rental record.\n";
            }
        }
    }

    // Reconcile vehicle availability with active rentals.
    for (int i = 0; i < system.vehicleCount; ++i) {
        system.vehicles[i]->setStatus(true);
    }

    for (int i = 0; i < system.rentalCount; ++i) {
        if (system.rentals[i].isActive()) {
            for (int j = 0; j < system.vehicleCount; ++j) {
                if (system.vehicles[j]->getVehicleId() ==
                    system.rentals[i].getVehicleId()) {
                    system.vehicles[j]->setStatus(false);
                    break;
                }
            }
        }
    }

    cout << "Saved records loaded successfully.\n";
}