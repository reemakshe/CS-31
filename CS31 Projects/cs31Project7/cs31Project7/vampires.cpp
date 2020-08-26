// vampires.cpp
//Reema Kshetramade
//SID: 205328402
//Project 7

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;                // max number of rows in the arena
const int MAXCOLS = 20;                // max number of columns in the arena
const int MAXVAMPIRES = 100;           // max number of vampires allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Vampire declaration.

class Vampire
{
  public:
      // Constructor
    Vampire(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool m_isPoisoned;
    int m_turnsSincePoisoned;
    bool m_dead;
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonVial();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     vampireCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfVampiresAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addVampire(int r, int c);
    bool addPlayer(int r, int c);
    void moveVampires();

  private:
    int      m_grid[MAXROWS][MAXCOLS];
    int      m_rows;
    int      m_cols;
    Player*  m_player;
    Vampire* m_vampires[MAXVAMPIRES];
    int      m_nVampires;
    int      m_turns;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Vampire implementation
///////////////////////////////////////////////////////////////////////////

Vampire::Vampire(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A vampire must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Vampire created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_isPoisoned = false;
    m_dead = false;
    m_turnsSincePoisoned = 0;
}

int Vampire::row() const
{
    return m_row;
}

int Vampire::col() const
{
    return m_col;
}

bool Vampire::isDead() const
{
    return m_dead;
}

void Vampire::move()
{
    
    //If the vampire has been poisoned and it is not a turn which it cannot move or it has not been poisoned
    if ((m_isPoisoned && m_turnsSincePoisoned % 2 == 0) || (!m_isPoisoned))
    {
        //Generate a random integer and use that as the direction the vampire should move in
        int dir = randInt(0, 3);
        attemptMove(*m_arena, dir, m_row, m_col);
    }
    
    //If the cell the vampire moves in has poison, if it is already poisoned then it becomes dead
    //Otherwise it just gets poisoned and slowed down for future moves
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
    {
        if (m_isPoisoned)
        {
            m_dead = true;
        }
        else
        {
            m_isPoisoned = true;
        }
        //After the vampire has drunk the poison, the cell should no longer have any more poison
        m_arena->setCellStatus(m_row, m_col, EMPTY);
    }
    
    //If vampire is poisoned, increment the turns since poisoned to keep track of when the vampire can move
    if (m_isPoisoned)
        m_turnsSincePoisoned++;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropPoisonVial()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned blood vial at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned blood vial has been dropped.";
}

string Player::move(int dir)
{
    string rtnStr = "Player couldn't move; player stands.";
    
    //Attempt to move and if the move cannot be made, return the error string
    bool isMove = attemptMove(*m_arena, dir, m_row, m_col);
    if (!isMove)
        return rtnStr;
    //Otherwise set the string to be returned to indicate the direction the player moved
    else
    {
        switch (dir)
        {
            case NORTH:
                rtnStr = "Player moved north.";
                break;
            case EAST:
                rtnStr = "Player moved east.";
                break;
            case SOUTH:;
                rtnStr = "Player moved south.";
                break;
            case WEST:
                rtnStr = "Player moved west.";
                break;
        }
    }
    
    //If the player moves into a vampire, set the return string to indicate the player's death
    if (m_arena->numberOfVampiresAt(m_row, m_col) > 0)
    {
        setDead();
        rtnStr = "Player walked into a vampire and died.";
    }
    
    return rtnStr;
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nVampires = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    for (int i = 0; i < m_nVampires; i++)
    {
        delete m_vampires[i];
    }
    
    delete m_player;
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::vampireCount() const
{
    return m_nVampires;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfVampiresAt(int r, int c) const
{
    //Loop through the vampire pointer array and increment numVampires for each vampire at position (r, c)
    int numVampires = 0;
    for (int i = 0; i < m_nVampires; i++)
    {
        if (m_vampires[i]->row() == r && m_vampires[i]->col() == c)
            numVampires++;
    }
    return numVampires;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned blood vials)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

    //Loop through each vampire in the arena
    for (int i = 0; i < m_nVampires; i++)
    {
        int row = m_vampires[i]->row();
        int col = m_vampires[i]->col();
        char disChar = displayGrid[row - 1][col - 1];
        
        //If the cell is empty, then set the display character to a V
        if (disChar == '.')
            displayGrid[row - 1][col - 1] = 'V';
        //If the cell already has one vampire in it, set the character to 2
        else if (disChar == 'V')
            displayGrid[row - 1][col - 1] = '2';
        //If the cell already has 9 or more vampires in it, do not change the display character
        else if (disChar == '9')
            continue;
        //If the other conditions are not met, then the display character must be a number between 2 and 8
        //So the number can be incremented by incrementing the character itself
        else
            displayGrid[row - 1][col - 1] = disChar + 1;
    }

      // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, vampire, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << vampireCount() << " vampires remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addVampire(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a vampire on a spot with a poisoned blood vial
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a vampire on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

      // If there are MAXVAMPIRES existing vampires, return false.  Otherwise,
      // dynamically allocate a new vampire at coordinates (r,c).  Save the
      // pointer to newly allocated vampire and return true.

    if (m_nVampires == MAXVAMPIRES)
    {
        return false;
    }
    
    //Create a new vampire dynamically and increment the number of vampires and return true
    m_vampires[m_nVampires] = new Vampire(this, r, c);
    m_nVampires++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a vampire
    if (numberOfVampiresAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveVampires()
{
      // Move all vampires
    for (int i = 0; i < m_nVampires; i++)
    {
        m_vampires[i]->move();
        //Make sure the player exists before checking its location
        if (m_player != nullptr)
        {
            //If the player is at the same location as the vampire, it becomes dead
            if (m_player->row() == m_vampires[i]->row() && m_player->col() == m_vampires[i]->col())
                m_player->setDead();
        }
        
        //If the vampire is dead, delete the vampire from memory
        //and shift the array of vampire pointers to delete it from the array and decrement num of vampires
        if (m_vampires[i]->isDead())
        {
            delete m_vampires[i];
            for (int j = i; j < m_nVampires - 1; j++)
                m_vampires[j] = m_vampires[j + 1];
            m_nVampires--;
            i--;
        }
        
    }
      // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nVampires)
{
    if (nVampires < 0)
    {
        cout << "***** Cannot create Game with negative number of vampires!" << endl;
        exit(1);
    }
    if (nVampires > MAXVAMPIRES)
    {
        cout << "***** Trying to create Game with " << nVampires
             << " vampires; only " << MAXVAMPIRES << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVampires - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nVampires << " vampires!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with vampires
    while (nVampires > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addVampire(r, c);
        nVampires--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonVial();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropPoisonVial();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->vampireCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveVampires();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    //Based on dir, either update the position, or return false if the position would be outside the arena
    switch (dir)
    {
        case NORTH:
            if (r - 1 < 1)
                return false;
            r--;
            break;
        case EAST:
            if (c + 1 > a.cols())
                return false;
            c++;
            break;
        case SOUTH:
            if (r + 1 > a.rows())
                return false;
            r++;
            break;
        case WEST:
            if (c - 1 < 1)
                return false;
            c--;
            break;
    }
    return true;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned blood vial and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    
    int pCol = 0;
    int pRow = 0;
    bool moveFound = false;
    int leastVamps = 10000;
    int leastVampsAt = -1;
        
    for (int i = 0; i < 5; i++)
    {
        //For each iteration of the loop -- each possible direction of movement (or no movement at all for
        //the last iteration) -- set what the row and column position would be for that move
        switch (i)
        {
            case NORTH:
                if (r - 1 < 1)
                    continue;
                pRow = r - 1;
                pCol = c;
                break;
            case EAST:
                if (c + 1 > a.cols())
                    continue;
                pRow = r;
                pCol = c + 1;
                break;
            case SOUTH:
                if (r + 1 > a.rows())
                    continue;
                pRow = r + 1;
                pCol = c;
                break;
            case WEST:
                if (c - 1 < 1)
                    continue;
                pRow = r;
                pCol = c - 1;
                break;
            case 4:
                pRow = r;
                pCol = c;
                break;
  
        }

        //If there are vampires at that position, then move to the next iteration of the loop (check the next
        //possible move)
        if (a.numberOfVampiresAt(pRow, pCol) != 0)
        {
            continue;
        }
        
        //Find the vampires to the north, east, south, and west of the players new possible position
        //because any of these vampires could move onto the player on their move and kill it
        int nVampNor = a.numberOfVampiresAt(pRow - 1, pCol);
        int nVampEas = a.numberOfVampiresAt(pRow, pCol + 1);
        int nVampSou = a.numberOfVampiresAt(pRow + 1, pCol);
        int nVampWes = a.numberOfVampiresAt(pRow, pCol - 1);
        
        //If the total number of vampires that could kill the player if it moved in that direction
        //is less than the current minimum, then set this as the new minimum
        //and change the direction where the least vampires would be to the current direction
        if (nVampNor + nVampEas + nVampSou + nVampWes < leastVamps)
        {
            leastVamps = nVampNor + nVampEas + nVampSou + nVampWes;
            leastVampsAt = i;
        }
    }
    
    //If the least vampires are found by moving (4 signifies that the player possible move is to stay put)
    if (leastVampsAt != 4)
    {
        //Set the best direction to the direction found that is accessible to the least possible number of
        //vampires and set move found to true
        bestDir = leastVampsAt;
        moveFound = true;
    }

    //Return moveFound (which was initialized as false and set to true if a direction to move was found)
    return moveFound;
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    
    Game g(3, 5, 2);
    //Game g(10, 12, 40);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
