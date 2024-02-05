#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
using namespace std;

struct User {
    string username;
    string password;
    bool registered;
};

struct Flight {
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    int availableSeats;
};

struct Booking {
    string uniqueCode;
    string flightNumber;
    string username;
    int seatNumber;
};

struct Passenger {
    string username;
    string ticketUniqueCode;
    bool checkedIn;
    bool boarded;
    bool baggageChecked;
};

struct Node {
    User data;
    Node* next;
};

void addUser(Node*& head, const User& newUser);
bool userExists(Node* head, const string& username);
bool loginUser(Node* head, const string& username, const string& password);
void displayFlightSchedule(const vector<Flight>& schedule);
Flight* findFlightByNumber(vector<Flight>& schedule, const string& flightNumber);
string generateUniqueCode();
void getUserDetailsForBooking(string& username, int& age, int& numSeats);
void displayAvailableSeats(const vector<Booking>& bookings, const Flight& flight);
bool isSeatAvailable(const vector<Booking>& bookings, const Flight& flight, int seatNumber);
void performCheckIn(vector<Passenger>& passengers, const string& username);
void performBoarding(vector<Passenger>& passengers, const string& username);
void performBaggageCheck(vector<Passenger>& passengers, const string& username);
void trackBaggage(const vector<Passenger>& passengers, const string& username);
bool findPassengerByUsername(const vector<Passenger>& passengers, const string& username, Passenger& foundPassenger);
void displayPassengerDetails(const vector<Passenger>& passengers);
void registerUser(Node*& userList);
void bookSeat(vector<Flight>& schedule, vector<Booking>& bookings, Flight& flight, Node* userHead, vector<Passenger>& passengers);
void searchBookedTicket(const vector<Booking>& bookings);
void displayPassengerDetails(const vector<Passenger>& passengers);

int main() {
    Node* userList = nullptr;

    User adminUser = {"swopon", "1234", true};
    addUser(userList, adminUser);

    vector<Flight> flightSchedule = {
        {"F123", "CityA", "CityB", "10:00 AM", 50},
        {"F456", "CityB", "CityC", "01:30 PM", 30},
        {"F789", "CityC", "CityD", "05:45 PM", 20}
    };

    vector<Booking> bookings;
    vector<Passenger> passengers;

    string enteredUsername, enteredPassword;
    cout << "Enter admin username: ";
    cin >> enteredUsername;
    cout << "Enter admin password: ";
    cin >> enteredPassword;

    if (loginUser(userList, enteredUsername, enteredPassword)) {
        cout << "Admin login successful. Displaying flight schedule:\n";
        displayFlightSchedule(flightSchedule);

        int choice;
        do {
            cout << "\nChoose an option:\n";
            cout << "1. Register as a New User\n";
            cout << "2. Book a Ticket\n";
            cout << "3. Search for a Booked Ticket\n";
            cout << "4. Display Passenger Details\n";
            cout << "5. Check-In Passenger\n";
            cout << "6. Board Passenger\n";
            cout << "7. Check Baggage\n";
            cout << "8. Track Baggage\n";
            cout << "9. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    registerUser(userList);
                    break;
                case 2: {
                    string chosenFlightNumber;
                    cout << "Enter the flight number you prefer: ";
                    cin >> chosenFlightNumber;

                    Flight* chosenFlight = findFlightByNumber(flightSchedule, chosenFlightNumber);

                    if (chosenFlight != nullptr) {
                        displayAvailableSeats(bookings, *chosenFlight);
                        bookSeat(flightSchedule, bookings, *chosenFlight, userList, passengers);
                    } else {
                        cout << "Invalid flight number.\n";
                    }
                    break;
                }
                case 3:
                    searchBookedTicket(bookings);
                    break;
                case 4:
                    displayPassengerDetails(passengers);
                    break;
                case 5: {
                    string username;
                    cout << "Enter passenger username: ";
                    cin >> username;
                    performCheckIn(passengers, username);
                    break;
                }
                case 6: {
                    string username;
                    cout << "Enter passenger username: ";
                    cin >> username;
                    performBoarding(passengers, username);
                    break;
                }
                case 7: {
                    string username;
                    cout << "Enter passenger username: ";
                    cin >> username;
                    performBaggageCheck(passengers, username);
                    break;
                }
                case 8: {
                    string username;
                    cout << "Enter passenger username: ";
                    cin >> username;
                    trackBaggage(passengers, username);
                    break;
                }
                case 9:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please enter a valid option.\n";
            }

        } while (choice != 9);
    } else {
        cout << "Admin login failed. Exiting program.\n";
    }

    while (userList != nullptr) {
        Node* temp = userList;
        userList = userList->next;
        delete temp;
    }

    return 0;
}

// Function to find a passenger by username
bool findPassengerByUsername(const vector<Passenger>& passengers, const string& username, Passenger& foundPassenger) {
    for (const Passenger& passenger : passengers) {
        if (passenger.username == username) {
            foundPassenger = passenger;
            return true;
        }
    }
    return false;
}

void addUser(Node*& head, const User& newUser) {
    Node* newNode = new Node;
    newNode->data = newUser;
    newNode->next = head;
    head = newNode;
}

bool userExists(Node* head, const string& username) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.username == username) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool loginUser(Node* head, const string& username, const string& password) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.username == username && current->data.password == password) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void displayFlightSchedule(const vector<Flight>& schedule) {
    cout << "\nFlight Schedule:\n";
    cout << "--------------------------------------\n";
    cout << "Flight Number | Origin | Destination | Departure Time | Available Seats\n";
    cout << "--------------------------------------\n";
    for (const Flight& flight : schedule) {
        cout << "   " << flight.flightNumber << "       |  " << flight.origin << " |    " << flight.destination << "     |   " << flight.departureTime << "   |   " << flight.availableSeats << "\n";
    }
    cout << "--------------------------------------\n";
}

Flight* findFlightByNumber(vector<Flight>& schedule, const string& flightNumber) {
    for (Flight& flight : schedule) {
        if (flight.flightNumber == flightNumber) {
            return &flight;
        }
    }
    return nullptr;
}

string generateUniqueCode() {
    const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int codeLength = 8;
    string uniqueCode;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < codeLength; ++i) {
        uniqueCode += charset[rand() % charset.length()];
    }

    return uniqueCode;
}

void getUserDetailsForBooking(string& username, int& age, int& numSeats) {
    cout << "Enter your name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, username);

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter the number of seats you want to book: ";
    cin >> numSeats;
}

void displayAvailableSeats(const vector<Booking>& bookings, const Flight& flight) {
    set<int> bookedSeats;
    for (const Booking& booking : bookings) {
        if (booking.flightNumber == flight.flightNumber) {
            bookedSeats.insert(booking.seatNumber);
        }
    }

    cout << "Available Seats for Flight " << flight.flightNumber << ": ";
    for (int seat = 1; seat <= flight.availableSeats; ++seat) {
        if (bookedSeats.find(seat) == bookedSeats.end()) {
            cout << seat << " ";
        }
    }
    cout << "\n";
}

bool isSeatAvailable(const vector<Booking>& bookings, const Flight& flight, int seatNumber) {
    for (const Booking& booking : bookings) {
        if (booking.flightNumber == flight.flightNumber && booking.seatNumber == seatNumber) {
            return false;
        }
    }
    return true;
}

void performCheckIn(vector<Passenger>& passengers, const string& username) {
    Passenger foundPassenger;
    if (findPassengerByUsername(passengers, username, foundPassenger)) {
        if (!foundPassenger.checkedIn) {
            foundPassenger.checkedIn = true;
            cout << "Check-in successful for passenger " << username << ".\n";
        } else {
            cout << "Passenger " << username << " is already checked in.\n";
        }
    } else {
        cout << "Passenger not found with the provided username.\n";
    }
}

void performBoarding(vector<Passenger>& passengers, const string& username) {
    Passenger foundPassenger;
    if (findPassengerByUsername(passengers, username, foundPassenger)) {
        if (foundPassenger.checkedIn && !foundPassenger.boarded) {
            foundPassenger.boarded = true;
            cout << "Boarding successful for passenger " << username << ".\n";
        } else if (!foundPassenger.checkedIn) {
            cout << "Passenger " << username << " needs to check-in first.\n";
        } else {
            cout << "Passenger " << username << " is already boarded.\n";
        }
    } else {
        cout << "Passenger not found with the provided username.\n";
    }
}

void performBaggageCheck(vector<Passenger>& passengers, const string& username) {
    Passenger foundPassenger;
    if (findPassengerByUsername(passengers, username, foundPassenger)) {
        if (foundPassenger.checkedIn && !foundPassenger.baggageChecked) {
            foundPassenger.baggageChecked = true;
            cout << "Baggage check successful for passenger " << username << ".\n";
        } else if (!foundPassenger.checkedIn) {
            cout << "Passenger " << username << " needs to check-in first.\n";
        } else {
            cout << "Baggage already checked for passenger " << username << ".\n";
        }
    } else {
        cout << "Passenger not found with the provided username.\n";
    }
}

void trackBaggage(const vector<Passenger>& passengers, const string& username) {
    Passenger foundPassenger;
    if (findPassengerByUsername(passengers, username, foundPassenger)) {
        if (foundPassenger.baggageChecked) {
            cout << "Baggage tracking information for passenger " << username << ":\n";
            cout << "Status: In Transit\n";
            cout << "Current Location: Airport " << foundPassenger.username[0] << " Baggage Claim\n";
        } else {
            cout << "Baggage not checked for passenger " << username << ".\n";
        }
    } else {
        cout << "Passenger not found with the provided username.\n";
    }
}

void displayPassengerDetails(const vector<Passenger>& passengers) {
    cout << "\nPassenger Details:\n";
    cout << "--------------------------------------\n";
    cout << "Username | Checked-In | Boarded | Baggage Checked\n";
    cout << "--------------------------------------\n";
    for (const Passenger& passenger : passengers) {
        cout << "   " << passenger.username << "    |      " << (passenger.checkedIn ? "Yes" : "No") << "      |   " << (passenger.boarded ? "Yes" : "No") << "   |      " << (passenger.baggageChecked ? "Yes" : "No") << "\n";
    }
    cout << "--------------------------------------\n";
}

void registerUser(Node*& userList) {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    if (!userExists(userList, username)) {
        cout << "Enter a password: ";
        cin >> password;

        User newUser = {username, password, true};
        addUser(userList, newUser);

        cout << "Registration successful.\n";
    } else {
        cout << "Username already exists. Registration failed.\n";
    }
}

void bookSeat(vector<Flight>& schedule, vector<Booking>& bookings, Flight& flight, Node* userHead, vector<Passenger>& passengers) {
    string username;
    int age, numSeats;

    getUserDetailsForBooking(username, age, numSeats);

    if (!userExists(userHead, username)) {
        cout << "Passenger not registered. Please register before booking a ticket.\n";
        return;
    }

    set<int> bookedSeats;
    for (const Booking& booking : bookings) {
        if (booking.flightNumber == flight.flightNumber) {
            bookedSeats.insert(booking.seatNumber);
        }
    }

    if (numSeats >= 1 && numSeats <= flight.availableSeats) {
        cout << "Specific available seats for Flight " << flight.flightNumber << ": ";
        for (int seat = 1; seat <= flight.availableSeats; ++seat) {
            if (bookedSeats.find(seat) == bookedSeats.end()) {
                cout << seat << " ";
            }
        }
        cout << "\n";

        set<int> chosenSeats;
        for (int i = 0; i < numSeats; ++i) {
            int chosenSeat;
            cout << "Enter seat number " << (i + 1) << ": ";
            cin >> chosenSeat;

            if (isSeatAvailable(bookings, flight, chosenSeat)) {
                chosenSeats.insert(chosenSeat);
            } else {
                cout << "Invalid seat number or seat already booked. Please choose an available seat.\n";
                --i;
            }
        }

        flight.availableSeats -= numSeats;

        for (int chosenSeat : chosenSeats) {
            string uniqueCode = generateUniqueCode();
            Booking newBooking = {uniqueCode, flight.flightNumber, username, chosenSeat};
            bookings.push_back(newBooking);

            Passenger newPassenger = {username, uniqueCode, false, false, false};
            passengers.push_back(newPassenger);

            cout << "Seat " << chosenSeat << " booked successfully. Your unique booking code is: " << uniqueCode << "\n";
        }
    } else {
        cout << "Invalid number of seats or insufficient availability. Booking failed.\n";
    }
}

void searchBookedTicket(const vector<Booking>& bookings) {
    string uniqueCode;
    cout << "Enter your unique booking code: ";
    cin >> uniqueCode;

    for (const Booking& booking : bookings) {
        if (booking.uniqueCode == uniqueCode) {
            cout << "\nBooking Details:\n";
            cout << "--------------------------------------\n";
            cout << "Unique Code: " << booking.uniqueCode << "\n";
            cout << "Flight Number: " << booking.flightNumber << "\n";
            cout << "Username: " << booking.username << "\n";
            cout << "Seat Number: " << booking.seatNumber << "\n";
            cout << "--------------------------------------\n";
            return;
        }
    }

    cout << "Booking not found with the provided unique code.\n";
}
