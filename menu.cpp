#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Pyramid Tic-Tac-Toe
const int SIZE_PYRAMID = 4;
vector<vector<char>> boardPyramid(SIZE_PYRAMID, vector<char>(2 * SIZE_PYRAMID - 1, ' '));

// Function prototypes
void initializePyramid();
void displayBoardPyramid();
bool isMoveValidPyramid(int row, int col);
bool isWinnerPyramid(char player);
bool isBoardFullPyramid();
void markMovePyramid(int row, int col, char player);

// Four-in-a-row
const int rows = 6;
const int cols = 7;
vector<vector<char>> boardFourInARow(rows, vector<char>(cols, ' '));

// Function prototypes
void printBoardFourInARow(const vector<vector<char>> &board);
bool checkWinFourInARow(const vector<vector<char>> &board, char player);

// 5x5 Tic Tac Toe
class Board {
public:
    virtual ~Board() {}

    virtual void displayBoard() const = 0;
    virtual bool isGameOver() const = 0;
    virtual bool isValidMove(int x, int y) const = 0;
    virtual void makeMove(int x, int y, char symbol) = 0;
    virtual bool checkWin(char symbol) const = 0;
};

class TicTacToeBoard : public Board {
private:
    char board[5][5];

public:
    TicTacToeBoard() {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    void displayBoard() const override {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                cout << board[i][j];
                if (j < 4) cout << " | ";
            }
            cout << endl;
            if (i < 4) cout << "---------" << endl;
        }
        cout << endl;
    }

    bool isGameOver() const override {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (board[i][j] == ' ') {
                    return false; // Game is not over if there's an empty space
                }
            }
        }
        return true; // Game is over if all spaces are filled
    }

    bool isValidMove(int x, int y) const override {
        return (x >= 0 && x < 5 && y >= 0 && y < 5 && board[x][y] == ' ');
    }

    void makeMove(int x, int y, char symbol) override {
        board[x][y] = symbol;
    }

    bool checkWin(char symbol) const override {
        // Check rows and columns
        for (int i = 0; i < 5; ++i) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
                return true; // Row
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
                return true; // Column
        }

        // Check diagonals
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
            return true; // Diagonal from top-left to bottom-right
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
            return true; // Diagonal from top-right to bottom-left

        return false;
    }
};

class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& n, char s) : name(n), symbol(s) {}

    string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    virtual void makeMove(Board& board, int& x, int& y) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const string& n) : Player(n, ' ') {
        // Prompt the player to choose 'X' or 'O'
        cout << n << ", choose 'X' or 'O': ";
        char choice;
        cin >> choice;
        while (choice != 'X' && choice != 'O') {
            cout << "Invalid choice. Choose 'X' or 'O': ";
            cin >> choice;
        }
        symbol = choice;
    }

    void makeMove(Board& board, int& x, int& y) override {
        cout << "Enter row number (0-4): ";
        cin >> x;
        cout << "Enter column number (0-4): ";
        cin >> y;
    }
};

class RandomComputerPlayer : public Player {
public:
    RandomComputerPlayer(const string& n, char s) : Player(n, s) {}

    void makeMove(Board& board, int& x, int& y) override {
        // Generate random moves until a valid move is found
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (!board.isValidMove(x, y));
    }
};

class GameManager {
private:
    Player* player1;
    Player* player2;
    Board* board;
    Player* currentPlayer;

public:
    GameManager(Player* p1, Player* p2, Board* b) : player1(p1), player2(p2), board(b) {
        currentPlayer = player1;
    }

    ~GameManager() {
        delete player1;
        delete player2;
        delete board;
    }

    void runGame() {
        while (!board->isGameOver()) {
            board->displayBoard();
            int x, y;
            currentPlayer->makeMove(*board, x, y);

            if (board->isValidMove(x, y)) {
                board->makeMove(x, y, currentPlayer->getSymbol());

                if (board->checkWin(currentPlayer->getSymbol())) {
                    board->displayBoard();
                    cout << currentPlayer->getName() << " wins!" << endl;
                    return;
                }
                swapTurns();
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }

        board->displayBoard();
        cout << "It's a draw!" << endl;
    }

    void swapTurns() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
};

// Function prototypes
void playPyramidTicTacToe();
void playFourInARow();
void play5x5TicTacToe();

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice;

    do {


 cout << "Select a game to play:" << endl;
        cout << "1. Pyramid Tic-Tac-Toe" << endl;
        cout << "2. Four-in-a-row" << endl;
        cout << "3. 5x5 Tic Tac Toe" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playPyramidTicTacToe();
                break;
            case 2:
                playFourInARow();
                break;
            case 3:
                play5x5TicTacToe();
                break;
            case 0:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}

// Pyramid Tic-Tac-Toe
void initializePyramid() {
    for (int i = 0; i < SIZE_PYRAMID; ++i) {
        for (int j = 0; j < 2 * SIZE_PYRAMID - 1; ++j) {
            boardPyramid[i][j] = ' ';
        }
    }
}

void displayBoardPyramid() {
    for (int i = 0; i < SIZE_PYRAMID; ++i) {
        for (int j = 0; j < SIZE_PYRAMID - i - 1; ++j) {
            cout << " ";
        }

        for (int j = 0; j < 2 * i + 1; ++j) {
            cout << boardPyramid[i][j];
            if (j < 2 * i) {
                cout << "|";
            }
        }
        cout << endl;
    }
}

bool isMoveValidPyramid(int row, int col) {
    if (row < 0 || row >= SIZE_PYRAMID || col < 0 || col >= 2 * row + 1 || boardPyramid[row][col] != ' ') {
        cout << "Invalid move is Full. Try again." << endl;
        return false;
    }
    return true;
}

bool isWinnerPyramid(char player) {
    for (int i = 0; i < SIZE_PYRAMID; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (boardPyramid[i][j] == player) {
                int count = 0;

                // Check horizontally
                for (int k = j; k < j + 3 && k < 2 * i + 1 && boardPyramid[i][k] == player; ++k) {
                    count++;
                }
                if (count == 3) {
                    return true;
                }

                count = 0;
                // Check diagonally
                for (int k = 0; k < 3 && i + k < SIZE_PYRAMID && j + k < 2 * (i + k) + 1 && boardPyramid[i + k][j + k] == player; ++k) {
                    count++;
                }
                if (count == 3) {
                    return true;
                }

                count = 0;
                // Check diagonally
                for (int k = 0; k < 3 && i + k < SIZE_PYRAMID && j - k >= 0 && boardPyramid[i + k][j - k] == player; ++k) {
                    count++;
                }
                if (count == 3) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isBoardFullPyramid() {
    for (int i = 0; i < SIZE_PYRAMID; ++i) {
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (boardPyramid[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void markMovePyramid(int row, int col, char player) {
    boardPyramid[row][col] = player;
}

void playPyramidTicTacToe() {
    int row, col;
    char currentPlayer = 'X';

    initializePyramid();

    do {
        displayBoardPyramid();

        do {
            cout << "Player " << currentPlayer << ", Enter your move (Row and Column): ";
            cin >> row >> col;
        } while (!isMoveValidPyramid(row, col));

        markMovePyramid(row, col, currentPlayer);

        if (isWinnerPyramid(currentPlayer)) {
            displayBoardPyramid();
            cout << "Player " << currentPlayer << " Wins!" << endl;
            break;
        }

        if (isBoardFullPyramid()) {
            displayBoardPyramid();
            cout << "The game is a draw!" << endl;
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    } while (1);
}

// Four-in-a-row
void printBoardFourInARow(const vector<vector<char>> &board) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

bool checkWinFourInARow(const vector<vector<char>> &board, char player) {
    // Check for horizontal win
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= cols - 4; ++j) {
            if (board[i][j] == player && board[i][j + 1] == player &&
                board[i][j + 2] == player && board[i][j + 3] == player) {
                return true;
            }
        }
    }

    // Check for vertical win
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == player && board[i + 1][j] == player &&
                board[i + 2][j] == player && board[i + 3][j] == player) {
                return true;
            }
        }
    }

    // Check for diagonal win (from bottom-left to top-right)
    for (int i = 3; i < rows; ++i) {
        for (int j = 0; j <= cols - 4; ++j) {
            if (board[i][j] == player && board[i - 1][j + 1] == player &&
                board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return true;
            }
        }
    }

  // Check for diagonal win (from top-left to bottom-right)
    for (int i = 0; i <= rows - 4; ++i) {
        for (int j = 0; j <= cols - 4; ++j) {
            if (board[i][j] == player && board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

void playFourInARow() {
    vector<vector<char>> boardFourInARow(rows, vector<char>(cols, ' ')); // Initialize an empty game board

    char currentPlayer = 'X'; // 'X' goes first

    int column;

    // Main game loop
    while (true) {
        printBoardFourInARow(boardFourInARow);

        // Get the column from the current player
        cout << "Player " << currentPlayer << ", choose a column (1-7): ";
        cin >> column;

        // Convert column number to zero-based index
        column--;

        // Check if the selected column is valid
        if (column < 0 || column >= cols || boardFourInARow[0][column] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        // Make the move
        for (int i = rows - 1; i >= 0; --i) {
            if (boardFourInARow[i][column] == ' ') {
                boardFourInARow[i][column] = currentPlayer;
                break;
            }
        }

        // Check if the current player has won
        if (checkWinFourInARow(boardFourInARow, currentPlayer)) {
            printBoardFourInARow(boardFourInARow);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        // Check if the board is full (a draw)
        bool isFull = true;
        for (int i = 0; i < cols; ++i) {
            if (boardFourInARow[0][i] == ' ') {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            printBoardFourInARow(boardFourInARow);
            cout << "It's a draw!" << endl;
            break;
        }

        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void play5x5TicTacToe() {
    cout << "Select an option:" << endl;
    cout << "1. Play against another player" << endl;
    cout << "2. Play against the computer" << endl;

    int option;
    cin >> option;

    Player* player1;
    Player* player2;

    if (option == 1) {
        player1 = new HumanPlayer("Player 1");
        player2 = new HumanPlayer("Player 2");
    } else if (option == 2) {
        player1 = new HumanPlayer("Player 1");
        player2 = new RandomComputerPlayer("Computer Player", 'O');
    } else {
        cout << "Invalid option. Exiting." << endl;
        return;
    }

    TicTacToeBoard ticTacToeBoard;
    GameManager ticTacToeGame(player1, player2, &ticTacToeBoard);
    ticTacToeGame.runGame();
}
