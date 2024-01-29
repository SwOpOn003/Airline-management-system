#include <iostream>
#include <string>

using namespace std;

struct Passenger {
    int id;
    string name;
    string destination;
    Passenger* next;
};


class PassengerManagementSystem {
private:
    Passenger* head;

public:

    PassengerManagementSystem() : head(nullptr) {}

    void addPassenger() {
        int id;
        string name, destination;

        cout << "Enter passenger ID: ";
        cin >> id;

        cout << "Enter passenger name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter destination: ";
        getline(cin, destination);

        Passenger* newPassenger = new Passenger{ id, name, destination, nullptr };
        if (!head) {
            head = newPassenger;
        } else {
            newPassenger->next = head;
            head = newPassenger;
        }

        cout << "Passenger added successfully!" << endl;
    }

    void searchPassenger() {
        int id;
        cout << "Enter passenger ID to search: ";
        cin >> id;

        Passenger* current = head;
        while (current) {
            if (current->id == id) {
                cout << "Passenger found!" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Destination: " << current->destination << endl;
                return;
            }
            current = current->next;
        }
        cout << "Passenger not found." << endl;
    }
    void deletePassenger() {
        int id;
        cout << "Enter passenger ID to delete: ";
        cin >> id;

        Passenger* current = head;
        Passenger* prev = nullptr;

        while (current) {
            if (current->id == id) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }

                delete current;
                cout << "Passenger deleted successfully!" << endl;
                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Passenger not found." << endl;
    }
};

int main() {
    PassengerManagementSystem passengerSystem;

    char choice;
    do {
        cout << "\nPlease follow the instruction in below:\n1. Add Passenger\n2. Search Passenger\n3. Delete Passenger\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                passengerSystem.addPassenger();
                break;
            case '2':
                passengerSystem.searchPassenger();
                break;
            case '3':
                passengerSystem.deletePassenger();
                break;
            case '4':
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '4');

    return 0;
}
