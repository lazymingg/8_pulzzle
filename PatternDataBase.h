#ifndef _PATTERN_DATABASE_H
#define _PATTERN_DATABASE_H

#include "Board.h"
#include <unordered_map>
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Board;
//singleton class
class PatternDataBase
{
private:
    std::unordered_map<string, int> patternDB;
    static PatternDataBase *instance;
    vector <vector<int>> notZeroCase;
    PatternDataBase();
public:
    static PatternDataBase *getInstance();
    void generatePatternDB(int size);
    int lookup(string pattern);
    int lookup(const Board& board);
    void writePatternDB();
    void readPatternDB();
    void insert(string pattern, int moves);
    int getNumberOfPatterns();
};

#endif