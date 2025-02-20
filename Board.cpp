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

Board::Board(Board &&b)
{
    size = b.size;
    g = b.g;
    tiles = b.tiles;
    b.tiles = nullptr;
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
        s += to_string(tiles[i]) + ",";
    }
    return s;
}

int Board::hash() const
{
    int h = 0;
    for (short i = 0; i < size * size; ++i)
    {
        h = 31 * h + tiles[i];
    }
    return h;
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

int Board::heuristic() const
{
    //using mahattan
    return mahanattan();

    //using pdb
    return extractHeuristicFromPatternDB();
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
    cout << "Inversion: " << inversion << endl;

    if (size % 2 == 1)
        return inversion % 2 == 0;

    short blankRowFromBottom = size - blankRow;
    cout << "Blank row from bottom: " << blankRowFromBottom << endl;

    return (inversion + blankRowFromBottom) % 2 == 1;
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
vector<Board> Board::neighbors()
{
    vector<Board> neighbors;
    // Tìm tất cả các vị trí có ô 0
    vector<short> zeroPositions;
    for (short i = 0; i < size * size; ++i)
    {
        if (tiles[i] == 0)
            zeroPositions.push_back(i);
    }

    // Với mỗi vị trí 0, tạo các trạng thái mới theo các hướng hợp lệ
    for (short index : zeroPositions)
    {
        short row = index / size;
        short col = index % size;

        // Di chuyển lên
        if (row > 0)
        {
            Board neighbor(*this);    // copy board hiện tại một lần
            swap(neighbor.tiles[index], neighbor.tiles[index - size]);
            neighbor.g += 1;
            neighbors.push_back(std::move(neighbor));
        }
        // Di chuyển xuống
        if (row < size - 1)
        {
            Board neighbor(*this);
            swap(neighbor.tiles[index], neighbor.tiles[index + size]);
            neighbor.g += 1;
            neighbors.push_back(std::move(neighbor));
        }
        // Di chuyển sang trái
        if (col > 0)
        {
            Board neighbor(*this);
            swap(neighbor.tiles[index], neighbor.tiles[index - 1]);
            neighbor.g += 1;
            neighbors.push_back(std::move(neighbor));
        }
        // Di chuyển sang phải
        if (col < size - 1)
        {
            Board neighbor(*this);
            swap(neighbor.tiles[index], neighbor.tiles[index + 1]);
            neighbor.g += 1;
            neighbors.push_back(std::move(neighbor));
        }
    }
    return neighbors;
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



// bool Board::operator<(const Board &b) const
// {
//     // using manhattan distance as heuristic
//     return mahanattan() + g < b.mahanattan() + b.g;
    
//     //using hamming distance as heuristic
//     // return hamming() + g < b.hamming() + b.g;

//     //using pattern database as heuristic
//     // return extractHeuristicFromPatternDB() + g < b.extractHeuristicFromPatternDB() + b.g;
// }

// bool Board::operator>(const Board &b) const
// {
//     // using manhattan distance as heuristic
//     return mahanattan() + g > b.mahanattan() + b.g;
    
//     //using hamming distance as heuristic
//     // return hamming() + g > b.hamming() + b.g;

//     //using pattern database as heuristic
//     // return extractHeuristicFromPatternDB() + g > b.extractHeuristicFromPatternDB() + b.g;
// }

// bool Board::operator==(const Board &b) const
// {
//     return equal(b);
// }

// bool Board::operator!=(const Board &b) const
// {
//     return !equal(b);
// }

short Board::getSize()
{
    return this->size;
}
