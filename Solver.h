// Solver.h
#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>

class Solver
{
private:
    Board initial;
    int moves;
    std::vector<Board> solution;
    std::unordered_map<std::string, int> patternDatabase;

public:
    Solver(Board initial);
    void storePatternDatabase();
    std::unordered_map<std::string, int> getPatternDatabase();
};

#endif // SOLVER_H