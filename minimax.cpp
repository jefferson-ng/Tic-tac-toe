#include <iostream>
#include <array>
#include <cstdlib>

/**
 * @class Board implement the board and its different methods
 * @param cells of 9 characters representing the Board .
 */
class Board
{
    // implement 3x3 grid and related methods
private:
    std::array<char, 9> cells;

public:
    /**
     * @brief Default Constructor
     */
    Board() : cells{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    {
    }

    /**
     * @brief Destructor
     */
    ~Board()
    {
    }

    /**
     * @brief validate or invalidate a move depending on the actual state of the game and the intended position .
     * @param position the intended position relative to the 1D array .
     * @param playerSymbol the player's symbol .
     */
    bool makeMove(int position, char playerSymbol)
    {
        // check for validity of the intended move
        if (position < 0 || position >= 9 || cells[position] != ' ')
        {
            return false;
        }
        cells[position] = playerSymbol;
        return true;
    }

    /**
     * @brief Check wether the Board is full
     */
    bool isFull() const
    {
        for (char cell : cells)
        {
            if (cell == ' ')
                return false;
        }
        return true;
    }

    /**
     * @brief Check wether the player with a given player's symbol won the game .
     * @param playerSymbol player's symbol
     */
    bool checkWin(char playerSymbol) const
    {
        // Checks rows
        for (int i = 0; i < 9; i += 3)
        {
            if (cells[i] == playerSymbol && cells[i + 1] == playerSymbol && cells[i + 2] == playerSymbol)
                return true;
        }
        // Checks columns
        for (int i = 0; i < 3; ++i)
        {
            if (cells[i] == playerSymbol && cells[i + 3] == playerSymbol && cells[i + 6] == playerSymbol)
                return true;
        }
        // Checks diagonal
        if (cells[0] == playerSymbol && cells[4] == playerSymbol && cells[8] == playerSymbol || cells[2] == playerSymbol && cells[4] == playerSymbol && cells[6] == playerSymbol)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Print the current state of the  board
     */
    void print() const
    {
        std::cout << "     1     2     3  " << std::endl;
        std::cout << "  ___________________" << std::endl;
        for (int row = 0; row < 3; ++row)
        {
            std::cout << "  |     |     |     |" << std::endl;
            std::cout << row + 1 << " |  ";
            for (int col = 0; col < 3; ++col)
            {
                char cellContent = cells[row * 3 + col];
                std::cout << (cellContent == '-' ? ' ' : cellContent) << "  |  ";
            }
            std::cout << std::endl;
            std::cout << "  |_____|_____|_____|" << std::endl;
        }
        std::cout << std::endl;
    }

    /**
     * @brief check wether a  cells is empty .
     */
    bool isEmptyCell(int position)
    {
        return (position >= 0 && position < 9 && cells[position] == ' ');
    }

    Board getCopy() const
    {
        return *this;
    }
};

/**
 * @class Player interface of a player .
 */
class Player
{
public:
    /**
     * @brief Default Constructor
     */
    Player() {}
    /**
     * @return the character used by the player
     */
    virtual char getSymbol() const = 0;
    /**
     * @brief pure virtual function for a player to make a move
     */
    virtual void makeMove(Board &board) = 0;
    /**
     * @brief Default Destructor
     */
    virtual ~Player() = default;
};

/**
 * @class HumanPlayer
 * @param symbol the character used by the Player
 */
class HumanPlayer : public Player
{
private:
    char symbol;

public:
    /**
     * @brief Default Constructor
     * @param sym the Character for the Human player
     */
    HumanPlayer(char sym) : symbol(sym)
    {
    }

    /**
     * @brief return the character of the Player
     * @return the character of the player
     */
    char getSymbol() const override
    {
        return symbol;
    }

    /**
     * @brief  function for a player to make a move
     */
    void makeMove(Board &board) override
    {
        int row, col, position;
        do
        {
            std::cout << "Select a row (1-3): ";
            std::cin >> row;
            std::cout << "Select a column (1-3): ";
            std::cin >> col;

            // Adjust for 0-based indexing
            row--;
            col--;
            position = row * 3 + col;

            if (position < 0 || position > 8 || !board.isEmptyCell(position))
                std::cout << "Invalid move. Try again.\n";
            else
            {
                board.makeMove(position, getSymbol());
                std::cout << "Player " << row << "|" << col << std::endl;
                break;
            }
        } while (true);
    }
};

/**
 * @class Mode
 * @brief refers to the game mode used to play against the computer : Random or Minimax
 */
enum class Mode
{
    RANDOM,
    MINIMAX
};

/**
 * @class ComputerPlayer
 * @param symbol the character used by the player
 * @param mode the mode of game
 */
class ComputerPlayer : public Player
{
private:
    char symbol;
    Mode mode;
    /**
     * @brief function for a player to make a move
     */
    void makeRandomMove(Board &board)
    {
        int row, col, position;
        // Keep trying random positions until an empty cell is found
        do
        {
            // Generate random row and column
            row = rand() % 3;
            col = rand() % 3;

            // Convert 2D coordinates to 1D position
            position = row * 3 + col;
        } while (!board.isEmptyCell(position));

        board.makeMove(position, getSymbol());
    }

    void makeMinimaxMove(Board &board)
    {
        int bestScore = -1000;
        int bestMove = -1;

        for (int i = 0; i < 9; i++)
        {
            if (board.isEmptyCell(i))
            {
                Board tempBoard = board; // Create a copy of the board
                tempBoard.makeMove(i, symbol);
                int score = minimax(tempBoard, 0, false);

                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = i;
                }
            }
        }

        if (bestMove != -1)
        {
            board.makeMove(bestMove, symbol);
            std::cout << "Computer " << (bestMove / 3 + 1) << "|" << (bestMove % 3 + 1) << std::endl;
        }
    }

    int minimax(Board board, int depth, bool isMaximizing)
    {
        char opponent = (symbol == 'X') ? 'O' : 'X';

        if (board.checkWin(symbol))
            return 10 - depth;
        if (board.checkWin(opponent))
            return depth - 10;
        if (board.isFull())
            return 0;

        int bestScore = isMaximizing ? -1000 : 1000;

        for (int i = 0; i < 9; i++)
        {
            if (board.isEmptyCell(i))
            {
                board.makeMove(i, isMaximizing ? symbol : opponent);
                int score = minimax(board, depth + 1, !isMaximizing);

                if (isMaximizing)
                {
                    bestScore = std::max(score, bestScore);
                }
                else
                {
                    bestScore = std::min(score, bestScore);
                }
            }
        }

        return bestScore;
    }

public:
    /**
     * @brief Default Constructor
     */
    ComputerPlayer(char sym, Mode m) : symbol(sym), mode(m)
    {
    }

    /**
     * @return the character of the player
     */
    char getSymbol() const override
    {
        return symbol;
    }

    /**
     * @brief make a move on the Boasd if valid
     */
    void makeMove(Board &board) override
    {
        switch (mode)
        {
        case Mode::RANDOM:
            makeRandomMove(board);
            break;
        case Mode::MINIMAX:
            makeMinimaxMove(board);
            break;
        }
    }
};

/**
 * @class Game
 * @param board the game board
 * @param player1 first player
 * @param player2 second player
 * @param currentPlayer the current player
 */
class Game
{
private:
    Board board;
    Player *player1;
    Player *player2;
    int currentPlayer;

public:
    /**
     * @brief Default Constructpr
     */
    Game() : currentPlayer(0), player1(nullptr), player2(nullptr) {}
    /**
     * @brief Default Destructor
     */
    ~Game()
    {
        delete player1;
        delete player2;
    }

    // Prevent copying
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    /**
     * @brief run the game
     */
    void run()
    {
        // Display the game mode menu
        printMenu();
        int choice;
        std::cin >> choice;

        // Set up players based on user's choice
        setupPlayers(choice);
        int draw = 0;
        // Main game loop
        while (!board.isFull() && !board.checkWin('X') && !board.checkWin('O'))
        {
            // Display current board state
            board.print();
            if (draw == 0)
            {
                std::cout << "Player 1: X" << std::endl;
                std::cout << "Player 2: O" << std::endl;
            }
            ++draw;
            std::cout << "Player's " << currentPlayer + 1 << " turn " << std::endl;
            // Get move from the current player
            (currentPlayer == 0 ? player1 : player2)->makeMove(board);
            // switch to the other player
            currentPlayer = 1 - currentPlayer;
        }

        // Display the final board state
        board.print();

        // announce the game result
        announceResult();
    }

    /**
     * @brief print the menu
     */
    void printMenu()
    {
        // Display game mode options to the user
        std::cout << "Choose your game mode.\n";
        std::cout << "(1) Human vs. Human\n";
        std::cout << "(2) Human vs. Computer (Minimax)\n";
        std::cout << "(3) Human vs. Computer (Random)\n";
        std::cout << "(4) Computer (Minimax) vs. Computer (Minimax)\n";
        std::cout << "(5) Exit Program\n";
    }

    /**
     * @brief Setup the player depending on the choice
     * @param choice
     */
    void setupPlayers(int choice)
    {
        delete player1;
        delete player2;
        // Create player objects based on user's choice
        switch (choice)

        {
        case 1:
            // Human vs Human: Both players are HumanPlayer
            player1 = new HumanPlayer('X');
            player2 = new HumanPlayer('O');
            break;
        case 2:
            // Human vs Computer (Minimax)
            player1 = new HumanPlayer('X');
            player2 = new ComputerPlayer('O', Mode::MINIMAX);
            break;

        case 3:
            // Human vs Computer (Random)
            player1 = new HumanPlayer('X');
            player2 = new ComputerPlayer('O', Mode::RANDOM);
            break;

        case 4:
            // Computer  (Minimax) vs. Computer (Minimax)
            player1 = new ComputerPlayer('X', Mode::MINIMAX);
            player2 = new ComputerPlayer('O', Mode::MINIMAX);
            break;
        case 5:
            // Exit the program if user chooses to
            std::cout << "Exiting the game. Goodbye!\n";
            exit(0);
        default:
            // Handle invalid input
            std::cout << "Invalid choice. Exiting ... \n";
            exit(1);
        }
    }

    /**
     * @brief print out the result of the game
     */
    void announceResult()
    {
        // Check win conditions and announce the result
        if (board.checkWin('X'))
            std::cout << "Winner is: Player 1(X) \n";
        else if (board.checkWin('O'))
            std::cout << "Winner is: Player 2(O) \n";
        else
            std::cout << "A draw! \n";
    }
};

int main()
{
    Game game;
    game.run();
    return 0;
}