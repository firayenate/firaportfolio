#include <iostream>
#include <cstring>
#include <fstream>  
#include <string>   
using namespace std;

const int MAX_CUSTOMERS = 5;
const int MAX_CARS = 5;
const int MAX_LENGTH = 50;

class Customer {
public:
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char name[MAX_LENGTH];

    Customer() {}

    Customer(const char* usr, const char* pass, const char* n) {
        strcpy(username, usr);
        strcpy(password, pass);
        strcpy(name, n);
    }
};

class Car {
public:
    int id;
    char name[MAX_LENGTH];
    char model[MAX_LENGTH];
    double pricePerDay;
    bool available;

    Car() : id(0), pricePerDay(0.0), available(false) {}

    Car(int i, const char* n, const char* m, double p, bool a) {
        id = i;
        strcpy(name, n);
        strcpy(model, m);
        pricePerDay = p;
        available = a;
    }
};

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

Car cars[MAX_CARS];
int carCount = 0;

const string CBE_ACCOUNT = "123456789";  
const string TELEBIRR_PHONE = "0912345678"; 

void registerCustomer();
bool loginCustomer();
void addCar();
void showAvailableCars();
void showRentedCars();  
void bookCar();
void mainMenu();
void initializeCars();
void loadCustomerData();
void loadCarData();
void saveCustomerData();
void saveCarData();
void processPayment(double totalCost);

bool isValidPIN(const string& pin);

int main() {
    cout << "===========================================\n";
    cout << "   Welcome to the Car Rental System! 🚗    \n";
    cout << "===========================================\n";

    loadCustomerData();
    loadCarData();

    initializeCars();

    mainMenu();

    saveCustomerData();
    saveCarData();

    return 0;
}

void mainMenu() {
    int choice;
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Admin Add Car\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerCustomer();
                break;
            case 2:
                if (loginCustomer()) {
                    int customerChoice;
                    while (true) {
                        cout << "\n1. Search Cars\n2. Book Car\n3. Show Rented Cars\n4. Logout\nEnter your choice: ";
                        cin >> customerChoice;

                        if (customerChoice == 1) {
                            showAvailableCars();
                        } else if (customerChoice == 2) {
                            bookCar();
                        } else if (customerChoice == 3) {
                            showRentedCars();  // Show rented cars for the logged-in customer
                        } else if (customerChoice == 4) {
                            saveCustomerData();
                            cout << "Logging out...\n";
                            break;
                        } else {
                            cout << "Invalid choice. Try again.\n";
                        }
                    }
                }
                break;
            case 3:
                addCar();
                break;
            case 4:
                cout << "Exiting the program... Thank you for using the Car Rental System!\n";
                saveCustomerData();
                saveCarData();
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

void registerCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        cout << "Customer limit reached. Cannot register more customers.\n";
        return;
    }

    cout << "Enter username: ";
    cin >> customers[customerCount].username;
    cout << "Enter password: ";
    cin >> customers[customerCount].password;
    cout << "Enter name: ";
    cin >> customers[customerCount].name;

    customerCount++;

    cout << "\n=========================================\n";
    cout << "   Registration Successful! Welcome, " << customers[customerCount - 1].name << "!\n";
    cout << "=========================================\n";
    cout << " You can now log in and explore our cars.\n";
    cout << "=========================================\n";
}

bool loginCustomer() {
    char username[MAX_LENGTH], password[MAX_LENGTH];

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, password) == 0) {
            cout << "\nWelcome, " << customers[i].name << "! You have successfully logged in.\n";
            customerCount = i + 1;
            return true;
        }
    }

    cout << "Invalid username or password.\n";
    return false;
}

void addCar() {
    if (carCount >= MAX_CARS) {
        cout << "Car inventory is full.\n";
        return;
    }

    cout << "Enter car ID: ";
    cin >> cars[carCount].id;
    cin.ignore();
    cout << "Enter car name: ";
    cin.getline(cars[carCount].name, MAX_LENGTH);
    cout << "Enter car model: ";
    cin.getline(cars[carCount].model, MAX_LENGTH);
    cout << "Enter price per day: ";
    cin >> cars[carCount].pricePerDay;
    cars[carCount].available = true;

    carCount++;
    cout << "\nCar added successfully!\n";
}

void showAvailableCars() {
    cout << "\n=========================================\n";
    cout << "           Available Cars                \n";
    cout << "=========================================\n";
    for (int i = 0; i < carCount; i++) {
        if (cars[i].available) {
            cout << "ID: " << cars[i].id << ", Name: " << cars[i].name
                 << ", Model: " << cars[i].model << ", Price: " << cars[i].pricePerDay << " birr/day\n";
        }
    }
    cout << "=========================================\n";
}

void showRentedCars() {
    cout << "\n=========================================\n";
    cout << "           Rented Cars                  \n";
    cout << "=========================================\n";
    bool rentedFound = false;
    for (int i = 0; i < carCount; i++) {
        if (!cars[i].available) {  // If the car is rented (not available)
            cout << "ID: " << cars[i].id << ", Name: " << cars[i].name
                 << ", Model: " << cars[i].model << ", Price: " << cars[i].pricePerDay << " birr/day\n";
            rentedFound = true;
        }
    }
    if (!rentedFound) {
        cout << "No cars have been rented yet.\n";
    }
    cout << "=========================================\n";
}

void bookCar() {
    int carID, rentalDays;

    cout << "Enter car ID to book: ";
    cin >> carID;

    for (int i = 0; i < carCount; i++) {
        if (cars[i].id == carID) {
            if (!cars[i].available) {
                cout << "Car is not available.\n";
                return;
            }

            cout << "Enter number of rental days: ";
            cin >> rentalDays;

            double totalCost = cars[i].pricePerDay * rentalDays;
            cout << "Total cost: " << totalCost << " birr\n";

            processPayment(totalCost);
            cars[i].available = false;  // Mark the car as rented
            saveCarData();             // Save updated car data to file
            cout << "\nCar booked successfully!\n";
            return;
        }
    }

    cout << "Car ID not found.\n";
}

bool isValidPIN(const string& pin) {
    // Validate the PIN (it must be exactly 4 digits long)
    if (pin.length() != 4) return false;
    for (char c : pin) {
        if (!isdigit(c)) return false;  // If the PIN contains non-digit characters
    }
    return true;
}

void processPayment(double totalCost) {
    int paymentMethod;
    string cardNumber, pin;

    cout << "\nChoose payment method:\n";
    cout << "1. CBE\n2. Telebirr\nEnter your choice: ";
    cin >> paymentMethod;

    switch (paymentMethod) {
        case 1:
            cout << "Enter your CBE card number: ";
            cin >> cardNumber;
            cout << "Enter your PIN (4 digits): ";
            cin >> pin;

            if (pin.length() != 4 || !isValidPIN(pin)) {
                cout << "Invalid PIN. Payment not processed.\n";
                return;
            }

            cout << "Payment successful using CBE card!\n";
            break;

        case 2:
            cout << "You have chosen Telebirr. Please proceed with your payment.\n";
            // Payment logic for Telebirr
            break;

        default:
            cout << "Invalid choice. Payment not processed.\n";
            return;
    }
}

void initializeCars() {
    cars[0] = Car(1, "Toyota Camry", "Sedan", 2500.0, true);
    cars[1] = Car(2, "Ford Explorer", "SUV", 3750.0, true);
    cars[2] = Car(3, "Mazda MX-5", "Convertible", 4500.0, true);
    carCount = 3;
}

void loadCustomerData() {
    ifstream file("customers.txt");
    if (file.is_open()) {
        file >> customerCount;
        file.ignore();
        for (int i = 0; i < customerCount; i++) {
            file >> customers[i].username >> customers[i].password >> customers[i].name;
        }
        file.close();
    }
}

void loadCarData() {
    ifstream file("cars.txt");
    if (file.is_open()) {
        file >> carCount;
        for (int i = 0; i < carCount; i++) {
            file >> cars[i].id;
            file.ignore();
            file.getline(cars[i].name, MAX_LENGTH);
            file.getline(cars[i].model, MAX_LENGTH);
            file >> cars[i].pricePerDay >> cars[i].available;
        }
        file.close();
    }
}

void saveCustomerData() {
    ofstream file("customers.txt");
    if (file.is_open()) {
        file << customerCount << endl;
        for (int i = 0; i < customerCount; i++) {
            file << customers[i].username << " " << customers[i].password << " " << customers[i].name << endl;
        }
        file.close();
    }
}

void saveCarData() {
    ofstream file("cars.txt");
    if (file.is_open()) {
        file << carCount << endl;
        for (int i = 0; i < carCount; i++) {
            file << cars[i].id << " " << cars[i].name << " " << cars[i].model << " "
                 << cars[i].pricePerDay << " " << cars[i].available << endl;
        }
        file.close();
    }
}
