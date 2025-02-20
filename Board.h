#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "PatternDataBase.h"

using namespace std;

class Board {
private:
    short size;
    short *tiles;
    // short x, y;
public:
    int g;

    Board();
    Board(short size, bool solved);
    Board(const Board &b);
    //move constructor
    Board(Board &&b);
    ~Board();

    Board &operator=(const Board &b);
    string toString() const;
    string hashString() const;
    int hash() const;

    short mahanattan() const;
    short hamming() const;
    short extractHeuristicFromPatternDB() const;
    bool isGoal();
    bool isSolvable();

    short tileAt(short row, short col);
    void setTileAt(short row, short col, short value);

    bool equal(const Board &board) const;

    Board moveLeft(short row, short col);
    Board moveRight(short row, short col);
    Board moveUp(short row, short col);
    Board moveDown(short row, short col);

    vector<Board> neighbors();

    Board zeroExcluded(vector<int> zeros) const;
    Board zeroExcept(vector<int> notZero) const;

    bool operator<(const Board &b) const;
    bool operator>(const Board &b) const;
    bool operator==(const Board &b) const;
    bool operator!=(const Board &b) const;

    short getSize();
};

#endif // BOARD_H
