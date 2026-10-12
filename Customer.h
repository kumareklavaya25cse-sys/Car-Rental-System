#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    // Default constructor
    Customer();

    // Parameterized constructor
    Customer(int id, const string& customerName,
             const string& phoneNumber);

    // Destructor
    ~Customer();

    // Display customer details
    void display() const;

    // Update customer details
    void update(const string& newName,
                const string& newPhone);

    // Getters
    int getCustomerId() const;
    string getName() const;
    string getPhone() const;

    // Setters
    void setName(const string& newName);
    void setPhone(const string& newPhone);
};

#endif