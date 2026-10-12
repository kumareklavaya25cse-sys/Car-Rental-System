#ifndef RENTAL_H
#define RENTAL_H

class Rental {
private:
    int rentalId;
    int vehicleId;
    int customerId;
    int days;
    double amount;
    bool active;

public:
    // Default constructor
    Rental();

    // Parameterized constructor
    Rental(int id, int vId, int cId,
           int rentalDays, double rentalAmount);

    // Destructor
    ~Rental();

    // Calculate rental bill
    double calculateBill(double dailyRate) const;

    // Close a rental
    void closeRental();

    // Display rental details
    void display() const;

    // Getters
    int getRentalId() const;
    int getVehicleId() const;
    int getCustomerId() const;
    int getDays() const;
    double getAmount() const;
    bool isActive() const;

    // Setters
    void setDays(int rentalDays);
    void setAmount(double rentalAmount);
};

#endif