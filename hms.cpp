//Abhishek Pant
//ACE079BCT006
//Hotel Management System

#include <iostream>
#include <string>
using namespace std;

// Constants defining the maximum number of rooms and guests
const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;

// Class representing individual rooms in the hotel
class Room {
public:
    int roomNumber; // Room number
    bool isBooked;  // Indicates whether the room is booked or not

    // Constructor to initialize room
    Room() : roomNumber(0), isBooked(false) {}

    // Initialize room with room number
    void initialize(int number) {
        roomNumber = number;
        isBooked = false;
    }

    // Mark the room as booked
    void bookRoom() {
        isBooked = true;
    }

    // Mark the room as vacant
    void vacateRoom() {
        isBooked = false;
    }

    // Check if the room is available
    bool checkAvailability() {
        return !isBooked;
    }
};

// Class representing guests staying in the hotel
class Guest {
public:
    string name;      // Guest name
    int roomNumber;   // Room number assigned to the guest

    // Constructor to initialize guest
    Guest() : name(""), roomNumber(0) {}

    // Initialize guest with name and room number
    void initialize(string guestName, int roomNum) {
        name = guestName;
        roomNumber = roomNum;
    }
};

// Class representing the hotel and its operations
class Hotel {
private:
    Room rooms[MAX_ROOMS];       // Array to store rooms
    Guest guests[MAX_GUESTS];    // Array to store guests
    int guestCount;               // Count of guests currently staying

public:
    // Constructor to initialize the hotel
    Hotel() : guestCount(0) {
        // Initialize each room with room number
        for (int i = 0; i < MAX_ROOMS; ++i) {
            rooms[i].initialize(i + 1);
        }
    }

    // Book a room for a guest
    void bookRoom(string guestName) {
        // Find the first available room and book it
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i].checkAvailability()) {
                rooms[i].bookRoom();
                // If there's space in the guest list, add the guest
                if (guestCount < MAX_GUESTS) {
                    guests[guestCount].initialize(guestName, rooms[i].roomNumber);
                    guestCount++;
                    cout << "Room " << rooms[i].roomNumber << " booked for " << guestName << endl;
                } else {
                    cout << "Guest list is full." << endl;
                }
                return;
            }
        }
        cout << "No rooms available." << endl;
    }

    // Book a specific room for a guest
    void bookSpecificRoom(string guestName, int roomNumber) {
        // Check if the room number is valid
        if (roomNumber < 1 || roomNumber > MAX_ROOMS) {
            cout << "Invalid room number." << endl;
            return;
        }

        // Find the specified room and book it
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i].roomNumber == roomNumber) {
                if (rooms[i].checkAvailability()) {
                    rooms[i].bookRoom();
                    // If there's space in the guest list, add the guest
                    if (guestCount < MAX_GUESTS) {
                        guests[guestCount].initialize(guestName, roomNumber);
                        guestCount++;
                        cout << "Room " << roomNumber << " booked for " << guestName << endl;
                    } else {
                        cout << "Guest list is full." << endl;
                    }
                } else {
                    cout << "Room " << roomNumber << " is already booked." << endl;
                }
                return;
            }
        }
    }

    // Vacate a room
    void vacateRoom(int roomNumber) {
        // Find the specified room and mark it as vacant
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i].roomNumber == roomNumber && rooms[i].isBooked) {
                rooms[i].vacateRoom();
                // Remove the guest associated with the room
                removeGuest(roomNumber);
                cout << "Room " << roomNumber << " is now available." << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " is not currently booked." << endl;
    }

    // Remove a guest from the guest list
    void removeGuest(int roomNumber) {
        for (int i = 0; i < guestCount; ++i) {
            if (guests[i].roomNumber == roomNumber) {
                guestCount--;
                return;
            }
        }
    }

    // List all guests currently staying in the hotel
    void listGuests() {
        if (guestCount == 0) {
            cout << "No guests currently." << endl;
            return;
        }
        for (int i = 0; i < guestCount; ++i) {
            cout << "Guest Name: " << guests[i].name << ", Room Number: " << guests[i].roomNumber << endl;
        }
    }

    // List all available rooms in the hotel
    void listAvailableRooms() {
        bool available = false;
        for (int i = 0; i < MAX_ROOMS; ++i) {
            if (rooms[i].checkAvailability()) {
                cout << "Room " << rooms[i].roomNumber << " is available." << endl;
                available = true;
            }
        }
        if (!available) {
            cout << "No available rooms." << endl;
        }
    }
};

// Main function
int main() {
    Hotel myHotel; // Create a hotel

    int choice;
    string guestName;
    int roomNumber;

    // Menu style interface
    while (true) {
        cout << "1. Book Room" << endl;
        cout << "2. Book Specific Room" << endl;
        cout << "3. Vacate Room" << endl;
        cout << "4. List Guests" << endl;
        cout << "5. List Available Rooms" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Perform the selected operation based on user input
        switch (choice) {
            case 1:
                cout << "Enter guest name: ";
                cin >> guestName;
                myHotel.bookRoom(guestName);
                break;
            case 2:
                cout << "Enter guest name: ";
                cin >> guestName;
                cout << "Enter room number to book: ";
                cin >> roomNumber;
                myHotel.bookSpecificRoom(guestName, roomNumber);
                break;
            case 3:
                cout << "Enter room number to vacate: ";
                cin >> roomNumber;
                myHotel.vacateRoom(roomNumber);
                break;
            case 4:
                myHotel.listGuests();
                break;
            case 5:
                myHotel.listAvailableRooms();
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
