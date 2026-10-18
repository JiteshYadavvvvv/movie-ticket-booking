#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;

const int MAX_MOVIES = 4;
const int MAX_SHOWS = 3;
const int SEAT_ROWS = 5;
const int SEATS_PER_ROW = 8;
const int MAX_BOOKINGS = 100;
const int MAX_TICKETS = 8;

int movieIds[MAX_MOVIES];
string movieTitles[MAX_MOVIES];
string movieGenres[MAX_MOVIES];
int movieDurations[MAX_MOVIES];
double moviePrices[MAX_MOVIES];
string showTimes[MAX_MOVIES][MAX_SHOWS];
char seatLayout[MAX_MOVIES][MAX_SHOWS][SEAT_ROWS][SEATS_PER_ROW];

struct Booking {
    int bookingId;
    bool isActive;
    bool isUsed;
    int movieIndex;
    int showIndex;
    int seatRow[MAX_TICKETS];
    int seatCol[MAX_TICKETS];
    int ticketCount;
    double totalAmount;
};

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;
int nextBookingId = 1;

void printSeparator() {
    cout << "------------------------------------------------------------" << endl;
}

int readInt() {
    int value;
    while (!(cin >> value)) {
        if (cin.eof()) {
            cout << endl << "Input ended unexpectedly. Exiting program." << endl;
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    return value;
}

char readChar() {
    char value;
    while (!(cin >> value)) {
        if (cin.eof()) {
            cout << endl << "Input ended unexpectedly. Exiting program." << endl;
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a letter: ";
    }
    return value;
}

void initMovies() {
    movieIds[0] = 1;
    movieTitles[0] = "The Code Avengers";
    movieGenres[0] = "Action";
    movieDurations[0] = 128;
    moviePrices[0] = 180.0;

    movieIds[1] = 2;
    movieTitles[1] = "Laugh Compiler";
    movieGenres[1] = "Comedy";
    movieDurations[1] = 110;
    moviePrices[1] = 150.0;

    movieIds[2] = 3;
    movieTitles[2] = "Silent Semicolon";
    movieGenres[2] = "Thriller";
    movieDurations[2] = 135;
    moviePrices[2] = 200.0;

    movieIds[3] = 4;
    movieTitles[3] = "Pixel Hearts";
    movieGenres[3] = "Romance";
    movieDurations[3] = 120;
    moviePrices[3] = 160.0;

    showTimes[0][0] = "10:00 AM";
    showTimes[0][1] = "02:00 PM";
    showTimes[0][2] = "06:30 PM";

    showTimes[1][0] = "11:00 AM";
    showTimes[1][1] = "03:00 PM";
    showTimes[1][2] = "07:00 PM";

    showTimes[2][0] = "12:00 PM";
    showTimes[2][1] = "04:00 PM";
    showTimes[2][2] = "09:00 PM";

    showTimes[3][0] = "01:00 PM";
    showTimes[3][1] = "05:00 PM";
    showTimes[3][2] = "08:30 PM";
}

void initSeats() {
    for (int m = 0; m < MAX_MOVIES; m++) {
        for (int s = 0; s < MAX_SHOWS; s++) {
            for (int r = 0; r < SEAT_ROWS; r++) {
                for (int c = 0; c < SEATS_PER_ROW; c++) {
                    seatLayout[m][s][r][c] = 'O';
                }
            }
        }
    }
}

void showMenu() {
    printSeparator();
    cout << "        MOVIE TICKET BOOKING SYSTEM" << endl;
    printSeparator();
    cout << "1. View Movies" << endl;
    cout << "2. View Show Timings" << endl;
    cout << "3. View Seat Layout" << endl;
    cout << "4. Book Movie Tickets" << endl;
    cout << "5. Cancel Booking" << endl;
    cout << "6. View Booking Details" << endl;
    cout << "7. View Total Collection" << endl;
    cout << "8. Exit" << endl;
    printSeparator();
    cout << "Enter your choice: ";
}

void showMovies() {
    printSeparator();
    cout << "              NOW SHOWING" << endl;
    printSeparator();
    cout << left << setw(5) << "ID" << setw(22) << "Title" << setw(12)
         << "Genre" << setw(12) << "Duration" << setw(10) << "Price" << endl;
    printSeparator();
    for (int i = 0; i < MAX_MOVIES; i++) {
        cout << left << setw(5) << movieIds[i] << setw(22) << movieTitles[i]
             << setw(12) << movieGenres[i] << setw(12) << (movieDurations[i]) << setw(10)
             << fixed << setprecision(2) << moviePrices[i] << endl;
    }
    printSeparator();
}

void showTimings(int movieIndex) {
    cout << "Show timings for " << movieTitles[movieIndex] << ":" << endl;
    for (int s = 0; s < MAX_SHOWS; s++) {
        cout << "  " << (s + 1) << ". " << showTimes[movieIndex][s] << endl;
    }
}

int findMovieIndexById(int id) {
    for (int i = 0; i < MAX_MOVIES; i++) {
        if (movieIds[i] == id) {
            return i;
        }
    }
    return -1;
}

int selectMovie() {
    showMovies();
    cout << "Enter Movie ID (0 to cancel): ";
    int id = readInt();
    if (id == 0) {
        cout << "Operation cancelled." << endl;
        return -1;
    }
    int index = findMovieIndexById(id);
    if (index == -1) {
        cout << "Invalid Movie ID." << endl;
        return -1;
    }
    return index;
}

int selectShow(int movieIndex) {
    showTimings(movieIndex);
    cout << "Enter show number (1-" << MAX_SHOWS << ", 0 to cancel): ";
    int choice = readInt();
    if (choice == 0) {
        cout << "Operation cancelled." << endl;
        return -1;
    }
    if (choice < 1 || choice > MAX_SHOWS) {
        cout << "Invalid show selection." << endl;
        return -1;
    }
    return choice - 1;
}

void showSeats(int movieIndex, int showIndex) {
    printSeparator();
    cout << "Seat Layout - " << movieTitles[movieIndex] << " (" << showTimes[movieIndex][showIndex] << ")" << endl;
    printSeparator();
    cout << "     ";
    for (int c = 1; c <= SEATS_PER_ROW; c++) {
        cout << setw(3) << c;
    }
    cout << endl;
    for (int r = 0; r < SEAT_ROWS; r++) {
        cout << "  " << char('A' + r) << "  ";
        for (int c = 0; c < SEATS_PER_ROW; c++) {
            cout << setw(3) << seatLayout[movieIndex][showIndex][r][c];
        }
        cout << endl;
    }
    cout << "Legend: O = Available, X = Booked" << endl;
    printSeparator();
}

void viewSeatLayoutMenu() {
    int movieIndex = selectMovie();
    if (movieIndex == -1) return;
    int showIndex = selectShow(movieIndex);
    if (showIndex == -1) return;
    showSeats(movieIndex, showIndex);
}

void bookTickets() {
    int movieIndex = selectMovie();
    if (movieIndex == -1) return;

    int showIndex = selectShow(movieIndex);
    if (showIndex == -1) return;

    showSeats(movieIndex, showIndex);

    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking limit reached. Cannot create new bookings." << endl;
        return;
    }

    cout << "Enter number of tickets to book (1-" << MAX_TICKETS << "): ";
    int ticketCount = readInt();
    if (ticketCount < 1 || ticketCount > MAX_TICKETS) {
        cout << "Invalid number of tickets." << endl;
        return;
    }

    int tempRow[MAX_TICKETS];
    int tempCol[MAX_TICKETS];

    for (int i = 0; i < ticketCount; i++) {
        while (true) {
            cout << "Ticket " << (i + 1) << " - Enter seat row (A-E): ";
            char rowChar = readChar();
            rowChar = toupper(rowChar);
            int row = rowChar - 'A';

            cout << "Ticket " << (i + 1) << " - Enter seat number (1-" << SEATS_PER_ROW << "): ";
            int seatNum = readInt();
            int col = seatNum - 1;

            if (row < 0 || row >= SEAT_ROWS || col < 0 || col >= SEATS_PER_ROW) {
                cout << "Invalid seat. Please try again." << endl;
                continue;
            }

            if (seatLayout[movieIndex][showIndex][row][col] != 'O') {
                cout << "Seat " << rowChar << seatNum << " is already booked. Please choose another seat." << endl;
                continue;
            }

            bool duplicate = false;
            for (int j = 0; j < i; j++) {
                if (tempRow[j] == row && tempCol[j] == col) {
                    duplicate = true;
                    break;
                }
            }
            if (duplicate) {
                cout << "Seat " << rowChar << seatNum << " is already selected in this booking. Please choose another seat." << endl;
                continue;
            }

            tempRow[i] = row;
            tempCol[i] = col;
            break;
        }
    }

    for (int i = 0; i < ticketCount; i++) {
        seatLayout[movieIndex][showIndex][tempRow[i]][tempCol[i]] = 'X';
    }

    Booking newBooking;
    newBooking.bookingId = nextBookingId;
    newBooking.isActive = true;
    newBooking.isUsed = true;
    newBooking.movieIndex = movieIndex;
    newBooking.showIndex = showIndex;
    newBooking.ticketCount = ticketCount;
    newBooking.totalAmount = ticketCount * moviePrices[movieIndex];
    for (int i = 0; i < ticketCount; i++) {
        newBooking.seatRow[i] = tempRow[i];
        newBooking.seatCol[i] = tempCol[i];
    }

    bookings[bookingCount] = newBooking;
    bookingCount++;
    nextBookingId++;

    printSeparator();
    cout << "BOOKING CONFIRMED" << endl;
    printSeparator();
    cout << "Booking ID   : " << newBooking.bookingId << endl;
    cout << "Movie        : " << movieTitles[movieIndex] << endl;
    cout << "Show Time    : " << showTimes[movieIndex][showIndex] << endl;
    cout << "Seats        : ";
    for (int i = 0; i < ticketCount; i++) {
        cout << char('A' + tempRow[i]) << (tempCol[i] + 1);
        if (i != ticketCount - 1) cout << ", ";
    }
    cout << endl;
    cout << "Ticket Count : " << ticketCount << endl;
    cout << "Total Amount : Rs. " << fixed << setprecision(2) << newBooking.totalAmount << endl;
    printSeparator();
}

int findBookingIndexById(int id) {
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].isUsed && bookings[i].bookingId == id) {
            return i;
        }
    }
    return -1;
}

void cancelBooking() {
    cout << "Enter Booking ID to cancel: ";
    int id = readInt();
    int index = findBookingIndexById(id);

    if (index == -1) {
        cout << "No booking found with ID " << id << "." << endl;
        return;
    }

    if (!bookings[index].isActive) {
        cout << "This booking is already cancelled." << endl;
        return;
    }

    bookings[index].isActive = false;
    int m = bookings[index].movieIndex;
    int s = bookings[index].showIndex;
    for (int i = 0; i < bookings[index].ticketCount; i++) {
        int r = bookings[index].seatRow[i];
        int c = bookings[index].seatCol[i];
        seatLayout[m][s][r][c] = 'O';
    }

    cout << "Booking " << id << " cancelled successfully. Seats released." << endl;
}

void showBookingDetails() {
    cout << "Enter Booking ID: ";
    int id = readInt();
    int index = findBookingIndexById(id);

    if (index == -1) {
        cout << "No booking found with ID " << id << "." << endl;
        return;
    }

    Booking b = bookings[index];
    printSeparator();
    cout << "BOOKING DETAILS" << endl;
    printSeparator();
    cout << "Booking ID   : " << b.bookingId << endl;
    cout << "Movie        : " << movieTitles[b.movieIndex] << endl;
    cout << "Show Time    : " << showTimes[b.movieIndex][b.showIndex] << endl;
    cout << "Seats        : ";
    for (int i = 0; i < b.ticketCount; i++) {
        cout << char('A' + b.seatRow[i]) << (b.seatCol[i] + 1);
        if (i != b.ticketCount - 1) cout << ", ";
    }
    cout << endl;
    cout << "Ticket Count : " << b.ticketCount << endl;
    cout << "Total Amount : Rs. " << fixed << setprecision(2) << b.totalAmount << endl;
    cout << "Status       : " << (b.isActive ? "Active" : "Cancelled") << endl;
    printSeparator();
}

void showCollection() {
    double total = 0.0;
    int activeCount = 0;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].isActive) {
            total += bookings[i].totalAmount;
            activeCount++;
        }
    }
    printSeparator();
    cout << "TOTAL COLLECTION" << endl;
    printSeparator();
    cout << "Active Bookings : " << activeCount << endl;
    cout << "Total Revenue   : Rs. " << fixed << setprecision(2) << total << endl;
    printSeparator();
}

int main() {
    initMovies();
    initSeats();

    int choice;
    do {
        showMenu();
        choice = readInt();

        switch (choice) {
            case 1:
                showMovies();
                break;
            case 2: {
                int movieIndex = selectMovie();
                if (movieIndex != -1) {
                    showTimings(movieIndex);
                }
                break;
            }
            case 3:
                viewSeatLayoutMenu();
                break;
            case 4:
                bookTickets();
                break;
            case 5:
                cancelBooking();
                break;
            case 6:
                showBookingDetails();
                break;
            case 7:
                showCollection();
                break;
            case 8:
                cout << "Thank you for using the Movie Ticket Booking System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }

    } while (choice != 8);

    return 0;
}
