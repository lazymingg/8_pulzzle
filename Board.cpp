#include "Board.h"

Board::Board() : size(0), tiles(nullptr), g(0) {}

Board::Board(short size, bool solved) : g(0), size(size)
{
    tiles = new short[size * size];

    for (short i = 0; i < size * size - 1; i++)
    {
        tiles[i] = i + 1;
    }
    if (size != 0)
    {
        tiles[size * size - 1] = 0;
    }

    if (!solved)
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(tiles, tiles + size * size, g);
    }
}

Board::Board(const Board &b) : g(b.g), size(b.size)
{
    tiles = new short[size * size];
    copy(b.tiles, b.tiles + size * size, tiles);
}


Board::~Board()
{
    delete[] tiles;
}

Board &Board::operator=(const Board &b)
{
    if (this == &b)
        return *this;

    delete[] tiles;
    size = b.size;
    g = b.g;
    tiles = new short[size * size];
    copy(b.tiles, b.tiles + size * size, tiles);

    return *this;
}

void Board::allocateTiles()
{
    tiles = new short[size * size];
}

void Board::deallocateTiles()
{
    delete[] tiles;
}


string Board::toString() const
{
    string s = to_string(size) + "\n";
    for (short i = 0; i < size; ++i)
    {
        for (short j = 0; j < size; ++j)
        {
            s += to_string(tiles[i * size + j]) + " ";
        }
        s += "\n";
    }
    return s;
}

string Board::hashString() const
{
    string s = "";
    for (short i = 0; i < size * size; ++i)
    {
        s += to_string(tiles[i]);
    }
    return s;
}

short Board::mahanattan() const
{
    short distance = 0;
    for (short i = 0; i < size * size; ++i)
    {
        short value = tiles[i];
        if (value != 0)
        {
            short targetX = (value - 1) / size;
            short targetY = (value - 1) % size;
            short currentX = i / size;
            short currentY = i % size;
            distance += abs(currentX - targetX) + abs(currentY - targetY);
        }
    }
    return distance;
}


short Board::hamming() const
{
    short distance = 0;
    for (short i = 0; i < size * size - 1; ++i)
    {
        if (tiles[i] != i + 1)
        {
            distance++;
        }
    }
    return distance;
}

short Board::extractHeuristicFromPatternDB() const
{
    PatternDataBase *patternDB = PatternDataBase::getInstance();
    return patternDB->lookup(*this);
}

bool Board::isGoal()
{
    for (short i = 0; i < size * size - 1; ++i)
    {
        if (tiles[i] != i + 1)
        {
            return false;
        }
    }
    return tiles[size * size - 1] == 0;
}


bool Board::isSolvable()
{
    vector<short> tempTiles;
    short blankRow = -1;
    short inversion = 0;

    for (short i = 0; i < size * size; ++i)
    {
        if (tiles[i] == 0)
            blankRow = i / size; 
        else
            tempTiles.push_back(tiles[i]);
    }

    short n = tempTiles.size();
    for (short i = 0; i < n - 1; ++i)
    {
        for (short j = i + 1; j < n; ++j)
        {
            if (tempTiles[i] > tempTiles[j])
                inversion++;
        }
    }

    if (size % 2 == 1)
        return inversion % 2 == 0;

    short blankRowFromBottom = size - blankRow;

    return (inversion + blankRowFromBottom) % 2 == 0;
}


short Board::tileAt(short row, short col)
{
    return this->tiles[row * size + col];
}

void Board::setTileAt(short row, short col, short value)
{
    this->tiles[row * size + col] = value;
}

bool Board::equal(const Board &board) const
{
    if (size != board.size)
        return false;

    for (short i = 0; i < size * size; ++i)
    {
        if (tiles[i] != board.tiles[i])
            return false;
    }
    return true;
}

Board Board::moveLeft(short row, short col)
{
    if (col == 0)
        return *this;

    Board newBoard(*this);
    short index = row * size + col;
    swap(newBoard.tiles[index], newBoard.tiles[index - 1]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveRight(short row, short col)
{
    if (col == size - 1)
        return *this;

    Board newBoard(*this);
    short index = row * size + col;
    swap(newBoard.tiles[index], newBoard.tiles[index + 1]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveUp(short row, short col)
{
    if (row == 0)
        return *this;

    Board newBoard(*this);
    short index = row * size + col;
    swap(newBoard.tiles[index], newBoard.tiles[index - size]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveDown(short row, short col)
{
    if (row == size - 1)
        return *this;

    Board newBoard(*this);
    short index = row * size + col;
    swap(newBoard.tiles[index], newBoard.tiles[index + size]);
    newBoard.g++;
    return newBoard;
}

vector<Board> Board::neighbors()
{
    vector<Board> neighbors;
    vector<short> zeroPositions;

    // Tìm vị trí các ô 0
    for (short i = 0; i < size * size; ++i)
    {
        if (tiles[i] == 0)
        {
            zeroPositions.push_back(i);
        }
    }

    for (short index : zeroPositions)
    {
        short row = index / size;
        short col = index % size;

        if (row > 0)
            neighbors.push_back(moveUp(row, col));
        if (row < size - 1)
            neighbors.push_back(moveDown(row, col));
        if (col > 0)
            neighbors.push_back(moveLeft(row, col));
        if (col < size - 1)
            neighbors.push_back(moveRight(row, col));
    }

    return neighbors;
}


Board Board::zeroExcluded(vector<int> zeros) const
{
    Board newBoard(*this);
    std::unordered_set<int> excluded(zeros.begin(), zeros.end());

    for (short i = 0; i < size * size; ++i)
    {
        if (excluded.find(newBoard.tiles[i]) != excluded.end()) 
        {
            newBoard.tiles[i] = 0; 
        }
    }
    return newBoard;
}

// zeroExcept
Board Board::zeroExcept(vector<int> notZero) const
{
    Board newBoard(*this);
    std::unordered_set<int> allowed(notZero.begin(), notZero.end());

    for (short i = 0; i < size * size; ++i)
    {
        if (allowed.find(newBoard.tiles[i]) == allowed.end()) 
        {
            newBoard.tiles[i] = 0; 
        }
    }
    return newBoard;
}



bool Board::operator<(const Board &b) const
{
    // using manhattan distance as heuristic
    // return mahanattan() + g < b.mahanattan() + b.g;
    
    //using hamming distance as heuristic
    // return hamming() + g < b.hamming() + b.g;

    //using pattern database as heuristic
    return extractHeuristicFromPatternDB() + g < b.extractHeuristicFromPatternDB() + b.g;
}

bool Board::operator>(const Board &b) const
{
    // using manhattan distance as heuristic
    // return mahanattan() + g > b.mahanattan() + b.g;
    
    //using hamming distance as heuristic
    // return hamming() + g > b.hamming() + b.g;

    //using pattern database as heuristic
    return extractHeuristicFromPatternDB() + g > b.extractHeuristicFromPatternDB() + b.g;
}

bool Board::operator==(const Board &b) const
{
    return equal(b);
}

bool Board::operator!=(const Board &b) const
{
    return !equal(b);
}

short Board::getSize()
{
    return this->size;
}
