#include "Customer.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Default constructor
Customer::Customer()
    : customerId(0), name(""), phone("") {
}

// Parameterized constructor
Customer::Customer(int id, const string& customerName,
                   const string& phoneNumber)
    : customerId(id), name(customerName), phone(phoneNumber) {

    if (customerName.empty()) {
        throw invalid_argument("Customer name cannot be empty.");
    }

    if (phoneNumber.empty()) {
        throw invalid_argument("Phone number cannot be empty.");
    }
}

// Destructor
Customer::~Customer() {
}

// Display customer details
void Customer::display() const {
    cout << "Customer ID: " << customerId
         << " | Name: " << name
         << " | Phone: " << phone
         << '\n';
}

// Update customer details
void Customer::update(const string& newName,
                      const string& newPhone) {
    if (newName.empty()) {
        throw invalid_argument("Customer name cannot be empty.");
    }

    if (newPhone.empty()) {
        throw invalid_argument("Phone number cannot be empty.");
    }

    name = newName;
    phone = newPhone;
}

// Getters
int Customer::getCustomerId() const {
    return customerId;
}

string Customer::getName() const {
    return name;
}

string Customer::getPhone() const {
    return phone;
}

// Setters
void Customer::setName(const string& newName) {
    if (newName.empty()) {
        throw invalid_argument("Customer name cannot be empty.");
    }

    name = newName;
}

void Customer::setPhone(const string& newPhone) {
    if (newPhone.empty()) {
        throw invalid_argument("Customer phone cannot be empty.");
    }

    phone = newPhone;
}