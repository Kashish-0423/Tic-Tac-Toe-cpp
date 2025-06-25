#include <iostream>
#include <unordered_map>
using namespace std;

bool validate_cell(char currentinput, unordered_map<char, string>& m) {
    // Check if the input is a valid key in the map (i.e., the cell is unclaimed)
    return m.count(currentinput) > 0;
}

void displayBoard(char board[3][3]) {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "--+---+--\n";
    }
    cout << endl;
}

bool checkWin(char board[3][3], char currentplayer) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentplayer && board[i][1] == currentplayer && board[i][2] == currentplayer) ||
            (board[0][i] == currentplayer && board[1][i] == currentplayer && board[2][i] == currentplayer))
            return true;
    }

    // Check diagonals
    if ((board[0][0] == currentplayer && board[1][1] == currentplayer && board[2][2] == currentplayer) ||
        (board[0][2] == currentplayer && board[1][1] == currentplayer && board[2][0] == currentplayer))
        return true;

    return false;
}

int main() {
    unordered_map<char, string> m;
    char board[3][3];
    char currentplayer = 'X';
    char currentinput;
    int l = 1;

    // Initialize board and map
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = (l + 48);
            string value = to_string(i) + to_string(j);
            m[board[i][j]] = value;
            l++;
        }
    }

    int moveCount = 0;
    while (moveCount < 9) {
        displayBoard(board);
        cout << "Current player is: " << currentplayer << endl;
        cout << "Choose a cell from 1 to 9: ";
        cin >> currentinput;

        bool valid = validate_cell(currentinput, m);
        if (valid) {
            string pos = m[currentinput];
            int row = pos[0] - '0';
            int col = pos[1] - '0';
            board[row][col] = currentplayer;
            m.erase(currentinput);
            moveCount++;

             if (checkWin(board, currentplayer)) {
                displayBoard(board);
                cout << "Player " << currentplayer << " wins!\n";
                return 0;
            }

            // Switch player AFTER move is made
            currentplayer = (currentplayer == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    displayBoard(board);
    cout << "Game Over! It's a draw (no win-checking added yet).\n";
    return 0;
}

