#include "Functions.h"

int main() {
    seedData();
    cout << "\n  System ready. Cars: " << cars.size
         << "  Customers: " << customers.size << "\n";

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
            case 1:  showCars(cars);          break;
            case 2:  showCars(cars, true);    break;
            case 3:  addCar();                break;
            case 4:  showCustomers(customers); break;
            case 5:  addCustomer();           break;
            case 6:  rentCar();               break;
            case 7:  returnCar();             break;
            case 8:  cancelRental();          break;
            case 9:  showRentals(rentals);    break;
            case 10:
                title("WAITING LIST");
                waitingList.display();
                break;
            case 11: revenueReport();         break;
            case 12:
                title("RECENT HISTORY (last 5)");
                history.displayTop5();
                break;
            case 0:
                cout << "  Goodbye!\n";
                break;
            default:
                cout << "  Invalid choice. Try again.\n";
        }

        if (choice != 0) {
            cout << "\n  Press Enter to continue...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
