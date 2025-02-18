#include "Board.h"

Board::Board() : size(0), tiles(nullptr), g(0) {}

Board::Board(int size, bool solved) : g(0), size(size)
{
    allocateTiles();

    vector<int> tempTiles(size * size);
    for (int i = 0; i < size * size - 1; i++)
    {
        tempTiles[i] = i + 1;
    }
    if (size != 0)
    {
        tempTiles[size * size - 1] = 0;
    }

    if (!solved)
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(tempTiles.begin(), tempTiles.end(), g);
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            tiles[i][j] = tempTiles[i * size + j];
        }
    }
}

Board::Board(const Board &b) : g(b.g), size(b.size)
{
    allocateTiles();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            tiles[i][j] = b.tiles[i][j];
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < size; ++i)
    {
        delete[] tiles[i];
    }
    delete[] tiles;
}

Board &Board::operator=(const Board &b)
{
    if (this == &b)
        return *this;

    for (int i = 0; i < size; ++i)
    {
        delete[] tiles[i];
    }
    delete[] tiles;

    size = b.size;
    g = b.g;
    allocateTiles();

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            tiles[i][j] = b.tiles[i][j];
        }
    }

    return *this;
}

void Board::allocateTiles()
{
    tiles = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        tiles[i] = new int[size];
    }
}

string Board::toString() const
{
    string s = to_string(size) + "\n";
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            s += to_string(tiles[i][j]) + " ";
        }
        s += "\n";
    }
    return s;
}

int Board::mahanattan() const
{
    int distance = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int value = tiles[i][j];
            if (value != 0)
            {
                int targetX = (value - 1) / size;
                int targetY = (value - 1) % size;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}

int Board::hamming()
{
    int distance = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            int value = tiles[i][j];
            if (value != 0 && value != i * size + j + 1)
            {
                distance++;
            }
        }
    }
    return distance;
}

bool Board::isGoal()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (tiles[i][j] != i * size + j + 1 && (i != size - 1 || j != size - 1))
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::isSolvable()
{
    vector<int> tempTiles;
    int blankRow = -1;
    int inversion = 0;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (tiles[i][j] == 0)
                blankRow = i;
            else
                tempTiles.push_back(tiles[i][j]);
        }
    }

    int n = tempTiles.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (tempTiles[i] > tempTiles[j])
                inversion++;
        }
    }

    if (size % 2 == 1)
        return inversion % 2 == 0;

    return (inversion + (size - blankRow)) % 2 == 0;
}

int Board::tileAt(int row, int col)
{
    return this->tiles[row][col];
}

void Board::setTileAt(int row, int col, int value)
{
    this->tiles[row][col] = value;
}

bool Board::equal(const Board &board) const
{
    if (this->size != board.size)
        return false;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (this->tiles[i][j] != board.tiles[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Board Board::moveLeft(int row, int col)
{
    if (col == 0)
        return *this;

    Board newBoard(*this);
    swap(newBoard.tiles[row][col], newBoard.tiles[row][col - 1]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveRight(int row, int col)
{
    if (col == size - 1)
        return *this;

    Board newBoard(*this);
    swap(newBoard.tiles[row][col], newBoard.tiles[row][col + 1]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveUp(int row, int col)
{
    if (row == 0)
        return *this;

    Board newBoard(*this);
    swap(newBoard.tiles[row][col], newBoard.tiles[row - 1][col]);
    newBoard.g++;
    return newBoard;
}

Board Board::moveDown(int row, int col)
{
    if (row == size - 1)
        return *this;

    Board newBoard(*this);
    swap(newBoard.tiles[row][col], newBoard.tiles[row + 1][col]);
    newBoard.g++;
    return newBoard;
}

vector<Board> Board::neighbors()
{
    vector<Board> neighbors;
    vector<pair<int, int>> zeroPositions;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (tiles[i][j] == 0)
            {
                zeroPositions.emplace_back(i, j);
            }
        }
    }

    for (const auto &[row, col] : zeroPositions)
    {
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

Board Board::zero5678()
{
    Board newBoard(*this);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (newBoard.tiles[i][j] == 5)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 6)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 7)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 8)
                newBoard.tiles[i][j] = 0;
        }
    }
    return newBoard;
}

Board Board::zero1234()
{
    Board newBoard(*this);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (newBoard.tiles[i][j] == 1)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 2)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 3)
                newBoard.tiles[i][j] = 0;
            else if (newBoard.tiles[i][j] == 4)
                newBoard.tiles[i][j] = 0;
        }
    }
    return newBoard;
}

bool Board::operator<(const Board &b) const
{
    return mahanattan() + g < b.mahanattan() + b.g;
}

bool Board::operator>(const Board &b) const
{
    return mahanattan() + g > b.mahanattan() + b.g;
}

bool Board::operator==(const Board &b) const
{
    return equal(b);
}

bool Board::operator!=(const Board &b) const
{
    return !equal(b);
}

int Board::getSize()
{
    return this->size;
}
