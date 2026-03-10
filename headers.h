#pragma once
#include <iostream>     // For input and output operations
#include <string>
#include <vector>       // For std::vector
#include <random>       // For std::random_device and std::mt19937
#include <algorithm>    // For std::shuffle
#include <ctime>        // For time functions
#include <iomanip>      // For std::setw and std::setfill
#include <fstream>
using namespace std;    // Use the standard namespace to avoid prefixing std::

// Function declarations
void ShuffleCards();
void DealCards();
void InitialCheckWin();
void InitializeGame();
void CheckPlayerHandValue(vector<char> hand);
void CheckDealerHandValue(vector<char> hand);
void OutputPlayerHand();
void OutputDealerHand();
void OutputDealerHandHidden();
void Hit();
void Stand();
void CheckWin();
void ClearScreen();
void PressEnterToContinue();
void OutputGameStats();
void SaveGameStatsToFile();
void LoadGameStatsFromFile();

// Constants
const string RESET_TEXT = "\033[0m";    // Reset text color
const string RED_TEXT = "\033[31m";     // Red text color for error messages
const string GREEN_TEXT = "\033[32m";   // Green text color for success messages
const string YELLOW_TEXT = "\033[33m";  // Yellow text color for warnings
const string MAGENTA_TEXT = "\033[35m"; // Magenta text color for special messages
const string CYAN_TEXT = "\033[36m";    // Cyan text color for highlights
const string BOLD_TEXT = "\033[1m";     // Bold text style

const int WIDTH = 53; // Width for formatting output
const string FILENAME = "infile.txt"; // File name for saving game statistics

// Global variables
const vector<char> ORDERED_DECK = {
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
    '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
};
vector<char> randomizedDeck;    // Randomized deck of cards
vector<char> playerHand;        // Player's hand
vector<char> dealerHand;        // Dealer's hand
int playerHandValue;            // Player's hand value
int dealerHandValue;            // Dealer's hand value
bool stand;                     // Flag to indicate if the player has chosen to stand
bool gameOver;                  // Flag to indicate if the game is over
string input;                   // Input string for user interaction
const string TITLE = "BLACKJACK"; // Game title
int playerWins = 0;           // Counter for player's wins
int dealerWins = 0;           // Counter for dealer's wins
int ties = 0;              // Counter for ties

void InitializeGame() {
    ClearScreen();                  // Clear the screen at the start of the game
    randomizedDeck.clear();         // Clear the previous randomized deck
    randomizedDeck = ORDERED_DECK;  // Initialize with the ordered deck
    playerHand.clear();             // Clear previous player's hand
    dealerHand.clear();             // Clear previous dealer's hand
    playerHandValue = 0;            // Reset player's hand value
    dealerHandValue = 0;            // Reset dealer's hand value
    stand = false;                  // Reset the stand flag
    gameOver = false;               // Reset the game over flag
}

void ShuffleCards(){
    // Create a random number generator
    static mt19937 g(time(0));   // Seed the generator with the random number

    // Shuffle the deck using the random number generator
    shuffle(randomizedDeck.begin(), randomizedDeck.end(), g);

    /* Print the shuffled deck for debugging purposes
    cout << "Shuffled Deck: ";
    for (char card : randomizedDeck) {
        cout << card << " ";
    }
    cout << endl;
    */
}

void DealCards(){
    // Deal two cards to the player and two cards to the dealer
    for (int i = 0; i < 2; ++i) {
        playerHand.push_back(randomizedDeck.back());    // Take the last card from the shuffled deck
        randomizedDeck.pop_back();                      // Remove the card from the deck
        dealerHand.push_back(randomizedDeck.back());    // Take the last card from the shuffled deck
        randomizedDeck.pop_back();                      // Remove the card from the deck
    }

    OutputDealerHandHidden();  // Output the dealer's hand with one card hidden
    OutputPlayerHand();        // Output the player's hand
    
    /* Print the deck size for debugging purposes
    cout << "Deck Size: " << randomizedDeck.size() << endl;  // Print the size of the deck
    */
}

void CheckPlayerHandValue(vector<char> hand) {
    playerHandValue = 0;  // Reset player's hand value
    int aceCount = 0;  // Count of Aces in the player's hand

    // This function can be used to check the value of a hand
    for (char card : hand) {
        if (card >= '2' && card <= '9') {
            // Cards 2-9 have their face value
            playerHandValue += card - '0';  // Convert char to int
        } else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K') {
            // Face cards have a value of 10
            playerHandValue += 10;  // Face cards are worth 10
        } else if (card == 'A') {
            // Ace can be 1 or 11, depending on the hand
            aceCount++;  // Count the number of Aces
        }
    }
    // Handle Aces after calculating the initial value
    if(aceCount > 0){
        for (int i = 0; i < aceCount; ++i) {
            // Use Ace as 11 if it doesn't bust the hand
            if (playerHandValue + 11 <= 21) {
                playerHandValue += 11;
            } else {
                playerHandValue += 1;  // Otherwise, use Ace as 1
            }
        }
    }
}

void CheckDealerHandValue(vector<char> hand) {
    dealerHandValue = 0;  // Reset dealer's hand value
    int aceCount = 0;  // Count of Aces in the dealer's hand

    // This function can be used to check the value of a hand
    for (char card : hand) {
        if (card >= '2' && card <= '9') {
            // Cards 2-9 have their face value
            dealerHandValue += card - '0';  // Convert char to int
        } else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K') {
            // Face cards have a value of 10
            dealerHandValue += 10;  // Face cards are worth 10
        } else if (card == 'A') {
            // Ace can be 1 or 11, depending on the hand
            aceCount++;  // Count the number of Aces
        }
    }
    // Handle Aces after calculating the initial value
    for (int i = 0; i < aceCount; ++i) {
        // Use Ace as 11 if it doesn't bust the hand
        if (dealerHandValue + 11 <= 21 ) {
            dealerHandValue += 11;
        } else if (dealerHandValue + 11 >= 17 && dealerHandValue + 11 <= 21) {
            dealerHandValue += 11;  // Use Ace as 11 if it keeps the hand value between 17 and 21
        } else {
            dealerHandValue += 1;  // Otherwise, use Ace as 1
        }
    }
}

void Hit(){
    int offset = 19;  // Offset for formatting output
    char newCard = randomizedDeck.back();   // Take the last card from the shuffled deck
    playerHand.push_back(newCard);          // Add the new card to the player's hand
    randomizedDeck.pop_back();              // Remove the card from the deck
    ClearScreen();                          // Clear the screen
    OutputDealerHandHidden();               // Output the dealer's hand
    OutputPlayerHand();                     // Output the player's hand
    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Player hits and receives: " << CYAN_TEXT << newCard;
    cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
    CheckWin();                             // Check if the player has won
}

void OutputPlayerHand() {
    int offset = 31;
    for (char card : playerHand) {
        offset--;
        offset--;
    }
    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Player's Hand: ";
    for (char card : playerHand) {
        cout << GREEN_TEXT << card << " ";  // Print each card in the hand
    }
    cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
}

void OutputDealerHand() {
    int offset = 31;
    for (char card : dealerHand) {
        offset--;
        offset--;
    }
    
    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Dealer's Hand: ";
    for (char card : dealerHand) {
        cout << RED_TEXT << card << " ";  // Print each card in the hand
    }
    cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
}

void OutputDealerHandHidden() {
    int offset = 28;

    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Dealer's Hand: ";
    cout << RED_TEXT << "? " << dealerHand[1];  // Hide the first card
    cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
}

void Stand(){
    int offset = 19;  // Offset for formatting output
    // Player stands, dealer's turn
    stand = true;                               // Set the stand flag to true
    CheckDealerHandValue(dealerHand);           // Calculate dealer's hand value
    while (dealerHandValue < 17) {
        char newCard = randomizedDeck.back();   // Take the last card from the shuffled deck
        dealerHand.push_back(newCard);          // Add the new card to the dealer's hand
        randomizedDeck.pop_back();              // Remove the card from the deck
        CheckDealerHandValue(dealerHand);       // Recalculate dealer's hand value
    }
    ClearScreen();                              // Clear the screen
    OutputDealerHand();                         // Output the dealer's hand
    OutputPlayerHand();                         // Output the player's hand
    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Player stands.";  // Print a message indicating the player has stood
    cout << MAGENTA_TEXT << string(32, ' ') << '-' << endl;  // Print a separator line
    for(int i = 2; i < dealerHand.size(); ++i) {
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Dealer hits and receives: " << CYAN_TEXT << dealerHand[i];
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
    }
    CheckWin();                                 // Check for a win
}

void InitialCheckWin(){
    CheckPlayerHandValue(playerHand);  // Calculate player's hand value
    CheckDealerHandValue(dealerHand);  // Calculate dealer's hand value
    int offset;  // Offset for formatting output

    if(dealerHandValue == 21 && playerHandValue == 21) {
        gameOver = true;  // Set game over flag to true
        ties++;  // Increment the ties counter
        ClearScreen();                              // Clear the screen
        OutputDealerHand();                         // Output the dealer's hand
        OutputPlayerHand();                         // Output the player's hand
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Both have a Blackjack! It's a tie!";   // Print a message indicating a tie
        offset = 1;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if (dealerHandValue == 21) {
        gameOver = true;  // Set game over flag to true
        dealerWins++;  // Increment the dealer's wins counter
        ClearScreen();                              // Clear the screen
        OutputDealerHand();                         // Output the dealer's hand
        OutputPlayerHand();                         // Output the player's hand
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Blackjack! " << RED_TEXT << "Dealer wins!";
        offset = 23;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen

    } else if (playerHandValue == 21) {
        gameOver = true;  // Set game over flag to true
        playerWins++;  // Increment the player's wins counter
        ClearScreen();                              // Clear the screen
        OutputDealerHand();                         // Output the dealer's hand
        OutputPlayerHand();                         // Output the player's hand
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Blackjack! " << YELLOW_TEXT << "Player wins!";
        offset = 23;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else {
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Enter '";
        cout << YELLOW_TEXT << "(H)it" << RESET_TEXT << "', '";
        cout << YELLOW_TEXT << "(S)tand" << RESET_TEXT << "', or '";
        cout << YELLOW_TEXT << "(Q)uit" << RESET_TEXT;
        cout << MAGENTA_TEXT << "          -" << endl;
    }
}    

void CheckWin(){
    CheckPlayerHandValue(playerHand);  // Calculate player's hand value
    CheckDealerHandValue(dealerHand);  // Calculate dealer's hand value
    int offset;  // Offset for formatting output

    if(playerHandValue == dealerHandValue && dealerHandValue >= 16 && stand) {
        ties++;  // Increment the ties counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Both have the same hand value! It's a tie!";
        offset = 4;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(dealerHandValue == 21) {
        dealerWins++;  // Increment the dealer's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Blackjack! " << RED_TEXT << "Dealer wins!";
        offset = 23;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(playerHandValue == 21) {
        playerWins++;  // Increment the player's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Blackjack! " << YELLOW_TEXT << "Player wins!";
        offset = 23;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(playerHandValue > 21) {
        dealerWins++;  // Increment the dealer's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Player busts! " << RED_TEXT << "Dealer wins!";
        offset = 20;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(dealerHandValue > 21) {
        playerWins++;  // Increment the player's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Dealer busts! " << YELLOW_TEXT << "Player wins!";
        offset = 20;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(playerHandValue > dealerHandValue && dealerHandValue >= 16 && stand) {
        playerWins++;  // Increment the player's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << YELLOW_TEXT << "Player wins!";
        offset = 34;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else if(dealerHandValue > playerHandValue && stand) {
        dealerWins++;  // Increment the dealer's wins counter
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << RED_TEXT << "Dealer wins!";
        offset = 34;
        cout << MAGENTA_TEXT << string(offset, ' ') << '-' << RESET_TEXT << endl;  // Print a separator line
        gameOver = true;  // Set game over flag to true
        PressEnterToContinue();  // Wait for user input
        ClearScreen();  // Clear the screen
    } else {
        cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Enter '";
        cout << YELLOW_TEXT << "(H)it" << RESET_TEXT << "', '";
        cout << YELLOW_TEXT << "(S)tand" << RESET_TEXT << "', or '";
        cout << YELLOW_TEXT << "(Q)uit" << RESET_TEXT;
        cout << MAGENTA_TEXT << "          -" << endl;
    }
}

void PressEnterToContinue() {
    int offset = 18;  // Offset for formatting output
    cout << MAGENTA_TEXT << "- " << RESET_TEXT;
    cout << "Press '";
    cout << YELLOW_TEXT << "Enter" << RESET_TEXT;  // Prompt the user to press Enter
    cout << "' to continue...";
    cout << MAGENTA_TEXT << string(offset, ' ') << '-' << endl;  // Print a separator line
    cout << setw(53) << setfill('-') << RESET_TEXT << endl;  // Print a separator line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore any previous input
    cin.get();  // Wait for the user to press Enter
    }

void ClearScreen(){
    int padding = WIDTH - TITLE.length();  // Calculate padding for the title
    int leftPadding = (padding - 2) / 2;  // Calculate left padding
    int rightPadding = padding - leftPadding - 6;  // Calculate right padding

    // Clear the console screen
    system("cls");  // For Windows
    cout << MAGENTA_TEXT << setw(WIDTH) << setfill('-') << RESET_TEXT <<endl;  // Print a divider line

    cout << MAGENTA_TEXT << "-";
    cout << BOLD_TEXT << YELLOW_TEXT << string(leftPadding, ' ') << TITLE << string(rightPadding, ' ');  // Print the game title
    cout << MAGENTA_TEXT << "-" << endl;  // Print a divider line

    int pad = (WIDTH - 29) / 2;
    cout << MAGENTA_TEXT << "-" << RESET_TEXT;
    cout << string(pad - 2, ' ');  // Subtract 1 because of the starting "-"
    OutputGameStats();            // Output the actual stats text (should be gameStatsTextLength long)

    cout << MAGENTA_TEXT << setw(WIDTH) << setfill('-') << RESET_TEXT << endl;  // Print a separator line
}

void OutputGameStats() {
    int gameStatsTextLength = 29;
    int gameStatsOffset = 8;
    if (playerWins > 9) {
        gameStatsTextLength++;
        gameStatsOffset--;
    }
    if (dealerWins > 9) {
        gameStatsTextLength++;  // Adjust the text length if dealer wins is greater than 9
        gameStatsOffset--;
    }
    if (ties > 9){
        gameStatsTextLength++;  // Adjust the text length if ties is greater than 9
        gameStatsOffset--;
    }
    cout << "Wins: " << GREEN_TEXT << playerWins << RESET_TEXT;
    cout << " | Losses: " << RED_TEXT << dealerWins << RESET_TEXT;
    cout << " | Ties: " << RESET_TEXT << ties; 
    cout << MAGENTA_TEXT << string(gameStatsOffset, ' ') << "-" << RESET_TEXT << endl;
}

void SaveGameStatsToFile() {
    ofstream outFile(FILENAME);  // Open the file for writing
    if (outFile.is_open()) {
        outFile << playerWins << endl;  // Write player's wins
        outFile << dealerWins << endl;  // Write dealer's wins
        outFile << ties << endl;         // Write ties
        outFile.close();                 // Close the file
    } else {
        cout << RED_TEXT << "Error: Unable to save game stats." << RESET_TEXT << endl;  // Print an error message
    }
    int offset = 11;
    cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Game statistics saved successfully!" << MAGENTA_TEXT << string(offset, ' ') << "-" << RESET_TEXT << endl;  // Print a success message
}

void LoadGameStatsFromFile() {
    ifstream inFile(FILENAME);  // Open the file for reading
    if (inFile.is_open()) {
        inFile >> playerWins >> dealerWins >> ties;         // Read ties
        inFile.close();         // Close the file
    } else {
        cout << RED_TEXT << "Error: Unable to load game stats." << RESET_TEXT << endl;  // Print an error message
    }
}