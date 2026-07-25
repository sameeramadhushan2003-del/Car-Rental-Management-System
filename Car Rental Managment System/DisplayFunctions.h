#ifndef DISPLAY_H
#define DISPLAY_H

#include "Models.h"
#include "DataStructures.h"
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;


// Display Functions

void line() {
    cout << "  " << string(68, '-') << "\n";
}

void title(string t) {
    line();
    cout << "  " << t << "\n";
    line();
}

void showCars(LinkedListCar& cars, bool availOnly = false) {
    title("CARS LIST");
    cout << "  ID       Brand + Model         Category   Rate/day       Status\n";
    line();
    for (int i = 0; i < cars.size; i++) {
        Car& c = cars.get(i);
        if (availOnly && !c.available) continue;
        printf("  %-8s %-21s %-10s LKR %-8.2f %-2s\n",
            c.id.c_str(),
            (c.Brand + " " + c.model).c_str(),
            c.category.c_str(),
            c.dailyRate,
            c.available ? "  [Available]" : "  [Rented]");
    }
    line();
}

void showCustomers(LinkedListCustomer& customers) {
    title("CUSTOMERS");
    cout << "  ID      Name                 Phone         License\n";
    line();
    for (int i = 0; i < customers.size; i++) {
        Customer& c = customers.get(i);
        printf("  %-7s %-21s %-14s %s\n",
            c.id.c_str(), c.name.c_str(),
            c.phone.c_str(), c.license.c_str());
    }
    line();
}

void showRentals(LinkedListRental& rentals, bool activeOnly = false) {
    title("RENTALS");
    cout << "  ID      Customer                  Car             Days  Cost          Status\n";
    line();
    for (int i = 0; i < rentals.size; i++) {
        Rental& r = rentals.get(i);
        if (activeOnly && !r.active) continue;
        string status = r.cancelled ? "[Cancelled]" : (r.active ? "[Active]" : "[Returned]");
        printf("  %-7s %-20s %-19s %-4d LKR %-10.2f %s\n",
            r.id.c_str(),
            r.customerName.c_str(),
            r.carName.c_str(),
            r.days,
            r.totalCost,
            status.c_str());
    }
    line();
}

void showMenu() {
    cout << "\n  ==============================================\n";
    cout << "  CAR RENTAL MANAGEMENT SYSTEM\n";
    cout << "  ==============================================\n";
    cout << "  Car Management\n";
    cout << "    1. View All Cars\n";
    cout << "    2. View Available Cars\n";
    cout << "    3. Add New Car\n";
    cout << "\n  Customer Management\n";
    cout << "    4. View All Customers\n";
    cout << "    5. Add New Customer\n";
    cout << "\n  Rental Operations\n";
    cout << "    6. Rent a Car\n";
    cout << "    7. Return a Car\n";
    cout << "    8. Cancel a Rental\n";
    cout << "    9. View All Rentals\n";
    cout << "    10. View Waiting List\n";
    cout << "\n  Reports\n";
    cout << "    11. Revenue Report\n";
    cout << "    12. Recent History\n";
    cout << "\n    0. Exit\n";
    cout << "  ==============================================\n";
    cout << "  Enter choice: ";
}

#endif
