#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Models.h"
#include "DataStructures.h"
#include "DisplayFunctions.h"
#include <iostream>
#include <string>
using namespace std;


// GLOBAL DATA

LinkedListCar      cars;
LinkedListCustomer customers;
LinkedListRental   rentals;
Queue                waitingList;
Stack                history;

int carCount  = 1;
int custCount = 1;
int rentCount = 1;

string newCarID()  { return "CAR" + to_string(carCount++); }
string newCustID() { return "C"   + to_string(custCount++); }
string newRentID() { return "R"   + to_string(rentCount++); }


// SEED DATA

void seedData() {
    auto addCar = [&](string mk, string mdl, int yr, string cat, double rate) {
        Car c;
        c.id = newCarID(); c.Brand = mk; c.model = mdl;
        c.year = yr; c.category = cat; c.dailyRate = rate;
        c.available = true;
        cars.add(c);
    };
    addCar("Toyota",   "Prius",    2019, "Economy", 15000.00);
    addCar("Honda",    "Civic",    2023, "Economy", 20000.00);
    addCar("Suzuki",     "Wagon R", 2022, "Economy", 12000.00);
    addCar("Honda",     "Vezel", 2023, "SUV",     20000.00);
    addCar("BMW",      "X5",       2023, "Luxury",  30000.00);
    addCar("Mercedes", "E-Class",  2023, "Luxury",  35000.00);

    auto addCust = [&](string nm, string ph, string lic) {
        Customer c;
        c.id = newCustID(); c.name = nm;
        c.phone = ph; c.license = lic;
        customers.add(c);
    };
    addCust("Pathum Sameera", "077-1234567", "200334610952");
    addCust("Sameera Madhushan",     "077-9876543", "200326912638");
    addCust("Vinuja Wijesinghe",   "076-2345678", "200325486325");
}

// Add Car Function

void addCar() {
    Car c;
    c.id = newCarID();
    cout << "  Brand: ";     getline(cin, c.Brand);
    cout << "  Model: ";    getline(cin, c.model);
    cout << "  Year: ";     cin >> c.year; cin.ignore();
    cout << "  Category (Economy / SUV / Luxury): ";
    getline(cin, c.category);
    cout << "  Daily Rate (LKR): "; cin >> c.dailyRate; cin.ignore();
    c.available = true;
    cars.add(c);
    cout << "  Car added! ID: " << c.id << "\n";
    history.push("Added car: " + c.Brand + " " + c.model + " [" + c.id + "]");
}


// Add Customer Function

void addCustomer() {
    Customer c;
    c.id = newCustID();
    cout << "  Name: ";    getline(cin, c.name);
    cout << "  Phone: ";   getline(cin, c.phone);
    cout << "  License: "; getline(cin, c.license);
    customers.add(c);
    cout << "  Customer added! ID: " << c.id << "\n";
    history.push("Added customer: " + c.name + " [" + c.id + "]");
}


// Rent Car Function

void rentCar() {
    cout << "\n  Enter Customer ID: ";
    string cid; cin >> cid; cin.ignore();

    Customer* cust = nullptr;
    for (int i = 0; i < customers.size; i++)
        if (customers.get(i).id == cid) { cust = &customers.get(i); break; }
    if (!cust) { cout << "  Customer not found!\n"; return; }

    showCars(cars, true);
    cout << "  Enter Car ID to rent: ";
    string carId; cin >> carId; cin.ignore();

    Car* car = nullptr;
    for (int i = 0; i < cars.size; i++)
        if (cars.get(i).id == carId) { car = &cars.get(i); break; }

    if (!car) { cout << "  Car not found!\n"; return; }

    if (!car->available) {
        cout << "  Car is currently rented.\n";
        cout << "  Add to waiting list? (y/n): ";
        char ch; cin >> ch; cin.ignore();
        if (ch == 'y' || ch == 'Y') {
            waitingList.enqueue({cust->name, car->Brand, car->model});
            cout << "  Added to waiting list!\n";
        }
        return;
    }

    cout << "  Number of days: ";
    int days; cin >> days; cin.ignore();

    Rental r;
    r.id           = newRentID();
    r.customerID   = cust->id;
    r.carID        = car->id;
    r.customerName = cust->name;
    r.carName      = car->Brand + " " + car->model;
    r.days         = days;
    r.totalCost    = car->dailyRate * days;
    r.active       = true;
    r.cancelled    = false;

    car->available = false;
    rentals.add(r);

    cout << "\n  Rental confirmed!\n";
    cout << "  Rental ID  : " << r.id << "\n";
    printf("  Total Cost : LKR %.2f\n", r.totalCost);
    history.push("Rented " + car->Brand + " " + car->model + " to " + cust->name);
}

// Return Car Function

void returnCar() {
    cout << "\n  Enter Rental ID: ";
    string rid; cin >> rid; cin.ignore();

    for (int i = 0; i < rentals.size; i++) {
        Rental& r = rentals.get(i);
        if (r.id == rid) {
            if (r.cancelled)    { cout << "  This rental was cancelled.\n"; return; }
            if (!r.active)      { cout << "  Car already returned.\n"; return; }

            r.active = false;

            for (int j = 0; j < cars.size; j++) {
                if (cars.get(j).id == r.carID) {
                    cars.get(j).available = true;
                    if (!waitingList.isEmpty()) {
                        WaitEntry next = waitingList.dequeue();
                        cout << "  [WAITING LIST] Notifying " << next.customerName
                             << " - a " << cars.get(j).Brand << " " << cars.get(j).model << " is now free!\n";
                    }
                    break;
                }
            }

            cout << "  Car returned successfully!\n";
            history.push("Returned rental " + rid + " (" + r.carName + ")");
            return;
        }
    }
    cout << "  Rental ID not found!\n";
}

// Cancel Rental Function

void cancelRental() {
    cout << "\n  Enter Rental ID to cancel: ";
    string rid; cin >> rid; cin.ignore();

    for (int i = 0; i < rentals.size; i++) {
        Rental& r = rentals.get(i);
        if (r.id == rid) {
            if (r.cancelled) { cout << "  Rental is already cancelled.\n"; return; }
            if (!r.active)   { cout << "  Cannot cancel a returned rental.\n"; return; }

            r.active    = false;
            r.cancelled = true;

            // Brand the car available again
            for (int j = 0; j < cars.size; j++) {
                if (cars.get(j).id == r.carID) {
                    cars.get(j).available = true;
                    cout << "  Car " << r.carName << " is now available again.\n";

                    // Notify waiting list
                    if (!waitingList.isEmpty()) {
                        WaitEntry next = waitingList.dequeue();
                        cout << "  [WAITING LIST] Notifying " << next.customerName
                             << " - a " << cars.get(j).Brand << " " << cars.get(j).model << " is now free!\n";
                    }
                    break;
                }
            }

            printf("  Rental %s cancelled. Refund: LKR %.2f\n", rid.c_str(), r.totalCost);
            history.push("Cancelled rental " + rid + " (" + r.carName + ")");
            return;
        }
    }
    cout << "  Rental ID not found!\n";
}


// Revenue Report Function

void revenueReport() {
    double total = 0;
    int active = 0, returned = 0, cancelled = 0;
    for (int i = 0; i < rentals.size; i++) {
        Rental& r = rentals.get(i);
        if (r.cancelled)     cancelled++;
        else if (r.active)   active++;
        else                { returned++; total += r.totalCost; }
    }
    title("REVENUE REPORT");
    cout << "  Active Rentals    : " << active    << "\n";
    cout << "  Returned Rentals  : " << returned  << "\n";
    cout << "  Cancelled Rentals : " << cancelled << "\n";
    printf("  Total Revenue     : LKR %.2f\n", total);
    line();
}

#endif
