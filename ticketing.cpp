#include <iostream>
#include <string>

using namespace std;

struct Ticket {
    int ticketNumber;
    string passengerName;
    string destination;
    bool isBooked;
};

class TicketingSystem {
private:
    static const int MAX_TICKETS = 50;
    Ticket tickets[MAX_TICKETS];
    int numBookedTickets;

public:
    TicketingSystem() : numBookedTickets(0) {
        for (int i = 0; i < MAX_TICKETS; ++i) {
            tickets[i].ticketNumber = i + 1;
            tickets[i].isBooked = false;
        }
    }
    void bookTicket() {
        if (numBookedTickets < MAX_TICKETS) {
            int ticketIndex;
            cout << "Enter ticket number to book: ";
            cin >> ticketIndex;

            if (ticketIndex >= 1 && ticketIndex <= MAX_TICKETS && !tickets[ticketIndex - 1].isBooked) {
                cout << "Enter passenger name: ";
                cin.ignore();
                getline(cin, tickets[ticketIndex - 1].passengerName);

                cout << "Enter destination: ";
                getline(cin, tickets[ticketIndex - 1].destination);

                tickets[ticketIndex - 1].isBooked = true;
                ++numBookedTickets;

                cout << "Ticket booked successfully!" << endl;
            } else {
                cout << "Invalid ticket number or ticket already booked." << endl;
            }
        } else {
            cout << "All tickets are booked. No more bookings allowed." << endl;
        }
    }
    void displayBookedTickets() {
        cout << "Booked Tickets:" << endl;
        for (int i = 0; i < MAX_TICKETS; ++i) {
            if (tickets[i].isBooked) {
                cout << "Ticket Number: " << tickets[i].ticketNumber << "\t Passenger Name: " << tickets[i].passengerName
                     << "\t Destination: " << tickets[i].destination << endl;
            }
        }
    }

    void cancelTicket() {
        int ticketIndex;
        cout << "Enter ticket number to cancel: ";
        cin >> ticketIndex;

        if (ticketIndex >= 1 && ticketIndex <= MAX_TICKETS && tickets[ticketIndex - 1].isBooked) {
            tickets[ticketIndex - 1].isBooked = false;
            --numBookedTickets;

            cout << "Ticket canceled successfully!" << endl;
        } else {
            cout << "Invalid ticket number or ticket not booked." << endl;
        }
    }
};

int main() {
    TicketingSystem ticketSystem;

    char choice;
    do {
        cout << "\nTicketing system:\n1. Book Ticket\n2. Display Booked Tickets\n3. Cancel Ticket\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                ticketSystem.bookTicket();
                break;
            case '2':
                ticketSystem.displayBookedTickets();
                break;
            case '3':
                ticketSystem.cancelTicket();
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
