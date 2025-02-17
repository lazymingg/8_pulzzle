#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Board
{
    private:
        int size;
        int **tiles;
    public:

        // create board with random tiles
        Board(int size)
        {
            // set the size of the board
            this->size = size;
            tiles = new int*[size];
            for (int i = 0; i < size; i++)
            {
                tiles[i] = new int[size];
            }
            
            // create a vector of tiles
            vector <int> tiles;
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
        ~Board()
        {
            for (int i = 0; i < size; i++)
            {
                delete[] tiles[i];
            }
            delete[] tiles;
        }

        string  toString()
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
        int mahanattan()
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
            int inversion = 0;
            for (int i = 0; i < size * size; i++)
            {
                for (int j = i + 1; j < size * size; j++)
                {
                    if (tiles[i / size][i % size] != 0 && tiles[j / size][j % size] != 0 && tiles[i / size][i % size] > tiles[j / size][j % size])
                    {
                        inversion++;
                    }
                }
            }
        }
};

int main()
{
    Board b(3);
    cout << b.toString();
    return 0;
}