#include "headers.h"

int main() {
    LoadGameStatsFromFile();  // Load game statistics from a file
    do {
        InitializeGame();   // Initialize the game
        ShuffleCards();     // Shuffle the cards and print the randomized deck
        DealCards();        // Deal the cards to the player and dealer
        InitialCheckWin();
        while(!gameOver && input != "Q" && input != "q" && input != "quit" && input != "Quit") {
            cout << MAGENTA_TEXT << setw(WIDTH) << setfill('-') << RESET_TEXT << endl;  // Print a separator line
            cout << MAGENTA_TEXT << '-' << ' ' << RESET_TEXT << "Choose your action: ";
            cin >> input;       // Get user input
            if (input == "Hit" || input == "hit" || input == "h" || input == "H") {
                Hit();           // Player chooses to hit
            } else if (input == "Stand" || input == "stand" || input == "s" || input == "S") {
                Stand();         // Player chooses to stand
            } else if (input != "Q" && input != "q" && input != "quit" && input != "Quit") {
                ClearScreen();  // Clear the screen for invalid input
                OutputDealerHandHidden();  // Output the dealer's hand with one card hidden
                OutputPlayerHand();  // Output the player's hand
                cout << MAGENTA_TEXT << "- " << RESET_TEXT;
                cout << "Please type '";
                cout << YELLOW_TEXT << "(H)it" << RESET_TEXT << "', '";
                cout << YELLOW_TEXT << "(S)tand" << RESET_TEXT << "', or '";
                cout << YELLOW_TEXT << "(Q)uit" << RESET_TEXT << "'";
                cout << MAGENTA_TEXT << "   -" << RESET_TEXT << endl;  // Handle invalid input
            } else {
                cout << MAGENTA_TEXT << "- " << RESET_TEXT << "Exiting the game." << MAGENTA_TEXT << string(29, ' ') << "-" << endl;  // Handle exit command
                break;  // Exit the loop if the player chooses to exit
            }
        }
        SaveGameStatsToFile();  // Save game statistics to a file
    } while (input != "Q" && input != "q" && input != "quit" && input != "Quit");
    cout << MAGENTA_TEXT << "- " << YELLOW_TEXT << "Thank you" << RESET_TEXT << " for playing!" << MAGENTA_TEXT << string(24, ' ') << "-" << endl;  // Thank the player for playing
    cout << MAGENTA_TEXT << setw(WIDTH) << setfill('-') << RESET_TEXT << endl;  // Print a separator line
    cout << endl;  // Print a new line
    cout << endl;  // Print a new line
    return 0;
}