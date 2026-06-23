#include <iostream>
#include <limits>
using namespace std;

struct Customer {
    string name;
    int roomNumber;
    Customer* next;
};

class Hotel {
private:
    bool rooms[10];
    Customer* head;

public:
    Hotel() {
        for (int i = 0; i < 10; i++) {
            rooms[i] = false;
        }
        head = NULL;
    }

    void bookRoom(string customerName) {
        int roomFound = -1;
        for (int i = 0; i < 10; i++) {
            if (!rooms[i]) {
                roomFound = i + 1;
                rooms[i] = true;
                break;
            }
        }

        if (roomFound == -1) {
            cout << "No rooms available at the moment." << endl;
            return;
        }

        Customer* newCustomer = new Customer;
        newCustomer->name = customerName;
        newCustomer->roomNumber = roomFound;
        newCustomer->next = head;
        head = newCustomer;

        cout << "Room booked successfully! Your room number is " << roomFound << "." << endl;
    }

    void checkOut(int roomNum) {
        if (roomNum < 1 || roomNum > 10) {
            cout << "Invalid room number!" << endl;
            return;
        }

        if (!rooms[roomNum - 1]) {
            cout << "Room is already empty!" << endl;
            return;
        }

        Customer* temp = head;
        Customer* prev = NULL;

        while (temp != NULL) {
            if (temp->roomNumber == roomNum) {
                if (prev == NULL) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp;
                rooms[roomNum - 1] = false;
                cout << "Check-out successful!" << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "Customer not found for the given room number." << endl;
    }

    void showBookings() {
        if (head == NULL) {
            cout << "No bookings found." << endl;
            return;
        }

        Customer* temp = head;
        cout << "\n--- Current Bookings ---" << endl;
        while (temp != NULL) {
            cout << "Name: " << temp->name << ", Room: " << temp->roomNumber << endl;
            temp = temp->next;
        }
    }

    void showRooms() {
        cout << "\n--- Room Status ---" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "Room " << (i + 1) << ": " << (rooms[i] ? "Booked" : "Empty") << endl;
        }
    }
};

bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    Hotel h;
    int choice;
    string name;
    int roomNo;

    do {
        cout << "\n--- WELCOME TO OUR HOTEL ---\n";
        cout << "--- HAILE GRAND HOTEL MENU ---\n";
        cout << "1. Book a Room\n";
        cout << "2. Check Out\n";
        cout << "3. Show Bookings\n";
        cout << "4. Show Room Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter your name: ";
                cin >> name;
                if (isValidName(name)) {
                    h.bookRoom(name);
                } else {
                    cout << "Invalid name. Please use letters only!" << endl;
                }
                break;

            case 2:
                cout << "Enter room number to check out: ";
                cin >> roomNo;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid room number!" << endl;
                } else {
                    h.checkOut(roomNo);
                }
                break;

            case 3:
                h.showBookings();
                break;

            case 4:
                h.showRooms();
                break;

            case 5:
                cout << "Thank you for choosing Haile Grand Hotel!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
