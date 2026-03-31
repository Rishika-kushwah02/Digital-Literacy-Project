#include <iostream> // For input/output (cin, cout)
using namespace std; // So we don’t have to write std:: every time

// Define colors using ANSI escape codes (just for styling output)
#define RED "\033[31m"    // Red color for X
#define GREEN "\033[32m"  // Green color for O
#define RESET "\033[0m"   // Reset color back to normal

// Declare a 3x3 board (2D array of characters)
char board[3][3];

// Score variables for players X and O
int scoreX = 0, scoreO = 0;

// Function to initialize the board with numbers 1–9
void initializeBoard() {
    char ch = '1'; // Start from character '1'

    // Loop through rows
    for(int i = 0; i < 3; i++)
        // Loop through columns
        for(int j = 0; j < 3; j++)
            board[i][j] = ch++; // Assign value and then increment ('1'→'2'→...)
}

// Function to display the board
void displayBoard() {
    for(int i = 0; i < 3; i++) {        // Loop through rows
        for(int j = 0; j < 3; j++) {    // Loop through columns
            
            char c = board[i][j]; // Get current cell value

            // Print X in red
            if(c == 'X') cout << RED << c << RESET;

            // Print O in green
            else if(c == 'O') cout << GREEN << c << RESET;

            // Otherwise print the number
            else cout << c;

            // Print separator between columns
            if(j < 2) cout << " | ";
        }

        cout << "\n"; // Move to next line after each row

        // Print row separator
        if(i < 2) cout << "--+---+--\n";
    }

    cout << "\n"; // Extra spacing
}

// Function to check if a player has won
bool checkWin(char player) {

    // Check rows and columns
    for(int i = 0; i < 3; i++)
        if(
            // Check row i
            (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            ||
            // Check column i
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)
          )
            return true; // Win found

    // Check diagonals
    if(
        (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)
      )
        return true;

    return false; // No win
}

// Function to check if the board is full (draw)
bool isDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            // If any cell is NOT X or O → game still going
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;

    return true; // All cells filled → draw
}

// Function to handle player move
void playerMove(char player) {
    int move, row, col;

    while(true) { // Keep asking until valid input

        cout << "Player " << player << ", enter cell (1-9): ";
        cin >> move; // Take input

        // Check if input is within range
        if(move < 1 || move > 9) {
            cout << "Invalid! Try 1-9.\n";
            continue; // Ask again
        }

        // Convert move (1–9) to row and column index
        row = (move - 1) / 3; // Row index
        col = (move - 1) % 3; // Column index

        // Check if cell already taken
        if(board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell taken! Choose another.\n";
            continue; // Ask again
        }

        // Place player's symbol
        board[row][col] = player;

        break; // Exit loop after valid move
    }
}

// Main function (program starts here)
int main() {

    char currentPlayer; // Tracks whose turn it is
    char playAgain;     // For replay option

    do { // Game loop (for replay)

        initializeBoard(); // Reset board
        currentPlayer = 'X'; // X starts first
        displayBoard(); // Show board

        while(true) { // Main game loop

            // Show current score
            cout << "Score: X=" << scoreX << " | O=" << scoreO << "\n";

            playerMove(currentPlayer); // Take player move
            displayBoard(); // Show updated board

            // Check if current player wins
            if(checkWin(currentPlayer)) {
                cout << "Player " << currentPlayer << " wins!\n";

                // Update score
                if(currentPlayer == 'X') scoreX++;
                else scoreO++;

                break; // End game
            }

            // Check for draw
            else if(isDraw()) {
                cout << "It's a draw!\n";
                break; // End game
            }

            // Switch player using ternary operator
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        // Ask user if they want to play again
        cout << "Play again? (y/n): ";
        cin >> playAgain;

    } while(playAgain == 'y' || playAgain == 'Y'); // Repeat if yes

    // Final score display
    cout << "Final Score: X=" << scoreX << " | O=" << scoreO << "\n";
    cout << "Thanks for playing!\n";

    return 0; // End program
}