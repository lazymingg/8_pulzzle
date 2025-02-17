#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;
class Board
{
private:
    int size;
    int **tiles;
    int g;
public:

    Board()
    {
        size = 0;
        tiles = nullptr;
        g = 0;
    }
    // create board with random tiles
    Board(int size) : g(0)
    {
        // set the size of the board
        this->size = size;
        tiles = new int *[size];
        for (int i = 0; i < size; i++)
        {
            tiles[i] = new int[size];
        }

        // create a vector of tiles
        vector<int> tiles;
        for (int i = 0; i < size * size; i++)
        {
            tiles.push_back(i);
        }

        // shuffle the tiles
        random_device rd;
        mt19937 g(rd());
        shuffle(tiles.begin(), tiles.end(), g);

        // assign the tiles to the board
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                this->tiles[i][j] = tiles[i * size + j];
            }
        }
            
    }
    
    //copy constructor
    Board(const Board &b) : g(b.g)
    {
        this->size = b.size;
        tiles = new int *[size];
        for (int i = 0; i < size; i++)
        {
            tiles[i] = new int[size];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                this->tiles[i][j] = b.tiles[i][j];
            }
        }
    }
    ~Board()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] tiles[i];
        }
        delete[] tiles;
    }

    // = operator
    Board &operator=(const Board &b)
    {
        if (this == &b)
            return *this;

        for (int i = 0; i < size; i++)
        {
            delete[] tiles[i];
        }
        delete[] tiles;

        this->size = b.size;
        tiles = new int *[size];
        for (int i = 0; i < size; i++)
        {
            tiles[i] = new int[size];
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                this->tiles[i][j] = b.tiles[i][j];
            }
        }
        this->g = b.g;
        return *this;
    }

    string toString()
    {
        string s = to_string(size) + "\n";
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                s += to_string(tiles[i][j]) + " ";
            }
            s += "\n";
        }
        return s;
    }

    // return sum of mahanattan distance
    int mahanattan() const
    {
        int distance = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
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

    // return the number of tiles out of place
    int hamming()
    {
        int distance = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
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

    // return true if this board is goal
    bool isGoal()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                int value = tiles[i][j];
                if (value != 0 && value != i * size + j + 1)
                {
                    return false;
                }
            }
        }
        return true;
    }

    // return true if this board is solvable
    bool isSolvable()
    {
        vector<int> tempTiles;
        int blankRow = -1;
        int inversion = 0;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (tiles[i][j] == 0)
                    blankRow = i;
                else
                    tempTiles.push_back(tiles[i][j]);
            }
        }

        int n = tempTiles.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (tempTiles[i] > tempTiles[j])
                    inversion++;
            }
        }

        if (size % 2 == 1)
            return inversion % 2 == 0;

        return (inversion + (size - blankRow)) % 2 == 0;
    }

    int tileAt(int row, int col)
    {
        return this->tiles[row][col];
    }

    bool equal(Board board) const
    {
        if (this->size != board.size) return false;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (this->tiles[i][j] != tiles[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    Board moveLeft(int row, int col)
    {
        if (col == 0)
            return *this;
        
        Board newBoard(*this);
        swap(newBoard.tiles[row][col], newBoard.tiles[row][col - 1]);
        this->g++;
        return newBoard;
    }
    Board moveRight(int row, int col)
    {
        if (col == size - 1)
            return *this;
        
        Board newBoard(*this);
        swap(newBoard.tiles[row][col], newBoard.tiles[row][col + 1]);
        this->g++;
        return newBoard;
    }
    Board moveUp(int row, int col)
    {
        if (row == 0)
            return *this;
        
        Board newBoard(*this);
        swap(newBoard.tiles[row][col], newBoard.tiles[row - 1][col]);
        this->g++;
        return newBoard;

    }
    Board moveDown(int row, int col)
    {
        if (row == size - 1)
            return *this;
        
        Board newBoard(*this);
        swap(newBoard.tiles[row][col], newBoard.tiles[row + 1][col]);
        this->g++;
        return newBoard;
    }
    vector<Board> neighbors()
    {
        vector<Board> neighbors;
        int row, col;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (tiles[i][j] == 0)
                {
                    row = i;
                    col = j;
                    break;
                }
            }
        }

        if (row > 0)
            neighbors.push_back(moveUp(row, col));
        if (row < size - 1)
            neighbors.push_back(moveDown(row, col));
        if (col > 0)
            neighbors.push_back(moveLeft(row, col));
        if (col < size - 1)
            neighbors.push_back(moveRight(row, col));

        return neighbors;
    }

    bool operator<(const Board &b) const
    {
        return mahanattan() + g < b.mahanattan() + b.g;
    }
    bool operator>(const Board &b) const
    {
        return mahanattan() + g > b.mahanattan() + b.g;
    }

    bool operator==(const Board &b) const
    {
        return equal(b);
    }
    bool operator!=(const Board &b) const
    {
        return !equal(b);
    }

};

class Solver {
    private:
        Board initial;
        int moves;
        vector<Board> solution;
    
    public:
        Solver(Board initial) : initial(initial), moves(0) {
            unordered_set<string> visited;
            priority_queue<Board, vector<Board>, greater<Board>> pq;
            unordered_map<string, string> parent;
    
            pq.push(initial);
            parent[initial.toString()] = "";
    
            Board goalBoard(0);
            bool found = false;
    
            while (!pq.empty()) {
                Board current = pq.top();
                pq.pop();
    
                if (visited.find(current.toString()) != visited.end())
                    continue;
                visited.insert(current.toString());
    
                if (current.isGoal()) {
                    goalBoard = current;
                    found = true;
                    break;
                }
    
                vector<Board> neighbors = current.neighbors();
                for (Board neighbor : neighbors) {
                    if (visited.find(neighbor.toString()) == visited.end()) {
                        if (parent.find(neighbor.toString()) == parent.end())
                            parent[neighbor.toString()] = current.toString();
                        pq.push(neighbor);
                    }
                }
            }
    
            if (found) {
                vector<string> path;
                string currentState = goalBoard.toString();
                while (!currentState.empty()) {
                    path.push_back(currentState);
                    currentState = parent[currentState];
                }
                reverse(path.begin(), path.end());
    
                cout << "Solution found in " << path.size() - 1 << " moves:" << endl;
                for (const auto &state : path) {
                    cout << state << endl;
                }
            } else {
                cout << "No solution found." << endl;
            }
        }
    };
    


int main()
{
    Board b(3);
    while (!b.isSolvable())
    {
        b = Board(3);
    }
    cout << b.toString();
    cout << "Mahanattan: " << b.mahanattan() << endl;
    cout << "Hamming: " << b.hamming() << endl;
    cout << "Is goal: " << b.isGoal() << endl;
    cout << "Is solvable: " << b.isSolvable() << endl;

    if (b.isSolvable())
    {
        Solver solver(b);
    }
    return 0;
}