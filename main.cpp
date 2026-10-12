#include <iostream>
#include <exception>
#include "RentalSystem.h"

using namespace std;

int main() {
    try {
        // Create the rental system object
        RentalSystem system;

        // Start the application
        system.run();
    }
    catch (const exception& e) {
        cerr << "Fatal program error: "
             << e.what() << '\n';

        return 1;
    }

    return 0;
}