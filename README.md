# Blackjack (C++ Console Game)

## Overview

This project is a console-based Blackjack game written in C++ that simulates a player competing against a dealer following standard Blackjack rules.

The program features a fully implemented game loop, randomized deck shuffling, hand value evaluation (including Ace logic), and persistent game statistics saved between sessions.

The project demonstrates C++ programming concepts such as vectors, random number generation, file I/O, modular design, and game state management.

---

## Features

### Core Gameplay

- Full Blackjack gameplay mechanics
- Player actions:
  - Hit
  - Stand
  - Quit
- Dealer follows traditional Blackjack rule:
  - Hits until reaching **17 or higher**

---

### Card System

- **52-card deck simulation**
- Randomized shuffling using `std::shuffle`
- Proper handling of:
  - Face cards (value **10**)
  - Ace values (**1 or 11** depending on hand)

---

### Game Interface

- Structured console UI
- Colored terminal output using **ANSI escape codes**
- Clear display of:
  - Player hand
  - Dealer hand (with hidden card)
  - Game messages
  - Round results

---

### Persistent Statistics

Game statistics are saved between sessions:

- Player wins
- Dealer wins
- Ties

Stats are stored in:

```
infile.txt
```

Example file contents:

```
22
46
4
```

Which represent:

- Player Wins
- Dealer Wins
- Ties

---

## Technologies Used

- **C++**
- STL containers (`std::vector`)
- Random number generation (`std::mt19937`)
- File input/output (`fstream`)
- Console formatting (`iomanip`)
- Modular program design

---

## Project Structure

```
Blackjack/

│
├── main.cpp
├── headers.h
├── infile.txt
└── BlackJack.exe
```

### main.cpp

Handles the main game loop and player input.

### headers.h

Contains:

- Game logic
- Card handling
- Deck shuffling
- Win condition checks
- UI rendering
- File saving/loading

### infile.txt

Stores persistent statistics between game sessions.

---

## How the Game Works

### 1. Deck Initialization

The game starts with an ordered **52-card deck**.

Example representation:

```
2 3 4 5 6 7 8 9 T J Q K A
```

Each rank appears **four times**.

---

### 2. Shuffling

The deck is randomized using:

```cpp
std::shuffle(randomizedDeck.begin(), randomizedDeck.end(), g);
```

---

### 3. Dealing Cards

Both the player and dealer receive **two cards**.

The dealer’s **first card remains hidden** until the player stands.

---

### 4. Player Turn

The player chooses:

- **(H)it**
- **(S)tand**
- **(Q)uit**

---

### 5. Dealer Turn

If the player stands, the dealer draws cards until the hand value reaches **17 or higher**.

---

### 6. Win Evaluation

The program checks:

- Blackjack
- Busts
- Higher hand value
- Tie

---

## Running the Program

### Compile

```bash
g++ main.cpp -o blackjack
```

### Run

```bash
./blackjack
```

Or run the included executable:

```
BlackJack.exe
```

---

## Example Gameplay

```
Player's Hand: 8 K
Dealer's Hand: ? 7

Enter (H)it, (S)tand, or (Q)uit
```

Player chooses:

```
Hit
```

New card:

```
Player hits and receives: 5
```

---

## Concepts Demonstrated

- Game state management
- Randomization algorithms
- File persistence
- Modular program structure
- User input validation
- Console UI design
- STL usage

---

## Future Improvements

Possible enhancements include:

- Multiple decks
- Betting system
- Split and double-down mechanics
- Graphical interface
- Multiplayer mode
- Improved input parsing
- Cross-platform screen clearing
