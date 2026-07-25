#ifndef MODELS_H
#define MODELS_H

#include <string>
using namespace std;


// Data Models


struct Car {
    string id, Brand, model, category;
    double dailyRate;
    bool available;
    int year;
};

struct Customer {
    string id, name, phone, license;
};

struct Rental {
    string id, customerID, carID, customerName, carName;
    int days;
    double totalCost;
    bool active;
    bool cancelled;
};

struct WaitEntry {
    string customerName;
    string Brand;
    string model;
};

#endif
