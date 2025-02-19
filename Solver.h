// Solver.h
#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <chrono>

class Solver
{
private:
    Board initial;
    int moves;
    std::vector<Board> solution;
public:
    Solver(Board initial);
    void IDAStar(Board &start);
};

#endif // SOLVER_H