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
    int heuristic() const;
    bool isGoal();
    bool isSolvable();

    short tileAt(short row, short col);
    void setTileAt(short row, short col, short value);

    bool equal(const Board &board) const;

    vector<Board> neighbors();

    Board zeroExcept(vector<int> notZero) const;

    short getSize();
};

#endif // BOARD_H
