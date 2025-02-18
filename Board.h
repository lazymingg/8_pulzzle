#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <utility>

using namespace std;

class Board {
private:
    int size;
    int **tiles;
    int g;

    void allocateTiles();  // Helper function to allocate memory for tiles

public:
    Board();
    Board(int size, bool solved);
    Board(const Board &b);
    ~Board();

    Board &operator=(const Board &b);
    string toString() const;

    int mahanattan() const;
    int hamming();
    bool isGoal();
    bool isSolvable();

    int tileAt(int row, int col);
    void setTileAt(int row, int col, int value);

    bool equal(const Board &board) const;

    Board moveLeft(int row, int col);
    Board moveRight(int row, int col);
    Board moveUp(int row, int col);
    Board moveDown(int row, int col);

    vector<Board> neighbors();

    Board zero5678();
    Board zero1234();

    bool operator<(const Board &b) const;
    bool operator>(const Board &b) const;
    bool operator==(const Board &b) const;
    bool operator!=(const Board &b) const;

    int getSize();
};

#endif // BOARD_H
