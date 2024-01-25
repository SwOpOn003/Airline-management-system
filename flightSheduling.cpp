#include <bits/stdc++.h>
#include <stack>
#include <string>

using namespace std;


struct Flight {
    string flightNumber;
    string departureCity;
    string destinationCity;
    string departureTime;
    string arrivalTime;
};


void displayFlight(const Flight& flight) {
    cout << "Flight Number: " << flight.flightNumber << endl;
    cout << "Departure City: " << flight.departureCity << endl;
    cout << "Destination City: " << flight.destinationCity << endl;
    cout << "Departure Time: " << flight.departureTime << endl;
    cout << "Arrival Time: " << flight.arrivalTime << endl;
    cout << "------------------------" << endl;
}

int main() {
    stack<Flight> flightSchedule;


    Flight flight1 = {"F123", "Bangladesh", "Delhi", "08:00Am", "11:00Am"};
    Flight flight2 = {"F234", "Dubai", "Bangladesh", "12:00Am", "10:00pm"};
    Flight flight3 = {"F345", "Soudi Arabia", "Bangladesh", "10:00Am", "02:00pm"};
    Flight flight4 = {"F344", "Bangladesh", "Nepal", "10:00Am", "01:00pm"};


    flightSchedule.push(flight1);
    flightSchedule.push(flight2);
    flightSchedule.push(flight3);
    flightSchedule.push(flight4);


    cout << "Current Flight Schedule:" << endl;
    while (!flightSchedule.empty()) {
        displayFlight(flightSchedule.top());
        flightSchedule.pop();
    }

    return 0;
}

