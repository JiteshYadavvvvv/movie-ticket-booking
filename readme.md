# Movie Ticket Booking System (C++)

A simple terminal-based movie ticket booking system written in beginner-level C++.
It uses fixed-size arrays (no `vector`), simple functions, and basic `cin`/`cout`
input and output. Built as a college mini project.

## Features

- View movies, show timings, and seat layout
- Book one or more seats for a movie and show
- Cancel an existing booking (seats are released back to available)
- View details of a specific booking
- View total revenue from active (non-cancelled) bookings
- Input validation for menu choices, movie IDs, show numbers, and seat numbers

## Files

- `main.cpp` — complete source code
- `readme.md` — this file
- `samples/` — sample terminal output transcripts

## Compiling

```
g++ -std=c++17 -Wall -Wextra main.cpp -o movie_booking
```

This compiles cleanly with no warnings.

## Running

```
./movie_booking
```

Follow the on-screen menu by typing a number and pressing Enter.

## Program structure

- `showMenu()` — prints the main menu
- `showMovies()` — prints the list of movies
- `showTimings(movieIndex)` — prints show timings for a movie
- `showSeats(movieIndex, showIndex)` — prints the seat layout grid
- `selectMovie()` / `selectShow(movieIndex)` — ask the user to pick a movie/show, with validation
- `bookTickets()` — walks through booking one or more seats
- `cancelBooking()` — cancels a booking by ID and releases its seats
- `showBookingDetails()` — looks up and prints one booking by ID
- `showCollection()` — sums the total amount of all active bookings
- `readInt()` / `readChar()` — read a number/letter from the keyboard and re-ask on bad input (and exit cleanly if input ever runs out)

### Data

- Movies, show timings, and prices are stored in fixed-size arrays (4 movies, 3 shows each).
- Seats are stored in a 4-dimensional array `seatLayout[movie][show][row][col]`, each cell
  holding `'O'` (available) or `'X'` (booked), for a 5x8 seat grid per movie/show.
- Each booking is stored in a `Booking` struct (booking ID, movie, show, the seats taken,
  ticket count, total amount, and whether it is still active) inside a fixed-size array
  of bookings.

## Sample output

`samples/full_session_transcript.txt` is a complete, real terminal transcript from an
actual run of the compiled program (not hand-written), covering: viewing movies and
timings, booking seats, trying to book an already-booked seat, viewing booking details,
cancelling a booking, confirming the seat is released and that it no longer counts
toward the collection, an invalid menu choice, and invalid seat entries. The exact
inputs typed for that run are in `samples/full_session_inputs.txt`. Short excerpts
below:

**Movie listing**

```
ID   Title                 Genre       Duration    Price
------------------------------------------------------------
1    The Code Avengers     Action      128         180.00
2    Laugh Compiler        Comedy      110         150.00
3    Silent Semicolon      Thriller    135         200.00
4    Pixel Hearts          Romance     120         160.00
```

**Successful booking**

```
BOOKING CONFIRMED
------------------------------------------------------------
Booking ID   : 1
Movie        : The Code Avengers
Show Time    : 10:00 AM
Seats        : A1
Ticket Count : 1
Total Amount : Rs. 180.00
```

**Booking an already-booked seat**

```
Seat A1 is already booked. Please choose another seat.
```

**Cancellation and seat release**

```
Booking 1 cancelled successfully. Seats released.
```

After cancelling, seat A1 shows as `O` again in the seat layout, and
`View Total Collection` no longer counts booking 1's amount.

## Viva notes (quick explanation of key functions)

- **`showMenu()`** just prints the eight menu options in a loop; `main()` keeps
  calling it until the user picks option 8 (Exit).
- **`selectMovie()`** prints the movie list and asks for a movie ID. It searches
  the `movieIds` array for a match and returns the array index, or `-1` if the
  ID is invalid or the user typed `0` to cancel.
- **`selectShow()`** works the same way but for the 3 show timings of the chosen movie.
- **`showSeats()`** loops over the 5x8 `seatLayout` array for the chosen movie/show
  and prints `O` or `X` for every seat, with row letters (A–E) and column numbers (1–8).
- **`bookTickets()`** asks how many tickets are needed, then for each ticket asks for
  a row letter and seat number. It checks the seat is inside the grid, is not already
  booked (`'X'`), and is not picked twice in the same booking, looping until a valid
  seat is given. Once all seats are confirmed valid, it marks them `'X'`, stores a new
  `Booking` record, and prints a confirmation.
- **`cancelBooking()`** looks up a booking by ID. If it exists and is still active, it
  flips `isActive` to `false` and turns its seats back to `'O'`. If the booking does not
  exist, or was already cancelled, it prints an error instead.
- **`showCollection()`** adds up `totalAmount` only for bookings where `isActive` is
  `true`, so cancelled bookings never count toward revenue.
- **`readInt()` / `readChar()`** wrap `cin >>` with a retry loop: if the user types
  something that is not a number (or the input stream ever reaches end-of-file), they
  print an error and ask again instead of crashing or looping forever.
