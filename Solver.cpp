#include "Solver.h"
#include <iostream>
#include <algorithm>

#define INT_MAX 2147483647

Solver::Solver(Board initial) : initial(initial), moves(0)
{
    auto start = std::chrono::high_resolution_clock::now();

    // std::unordered_set<std::string> visited;
    // std::priority_queue<Board, std::vector<Board>, std::greater<Board>> pq;
    // std::unordered_map<std::string, std::string> parent;

    // pq.push(initial);
    // parent[initial.toString()] = "";

    // Board goalBoard(0, true);
    // bool found = false;

    // while (!pq.empty())
    // {
    //     Board current = pq.top();
    //     pq.pop();

    //     if (visited.find(current.hashString()) != visited.end())
    //         continue;
    //     visited.insert(current.hashString());

    //     if (current.isGoal())
    //     {
    //         goalBoard = current;
    //         found = true;
    //         break;
    //     }

    //     std::vector<Board> neighbors = current.neighbors();
    //     for (Board neighbor : neighbors)
    //     {
    //         if (visited.find(neighbor.hashString()) == visited.end())
    //         {
    //             if (parent.find(neighbor.toString()) == parent.end())
    //                 parent[neighbor.toString()] = current.toString();
    //             pq.push(neighbor);
    //         }
    //     }
    // }

    // if (found)
    // {
    //     std::vector<std::string> path;
    //     std::string currentState = goalBoard.toString();
    //     while (!currentState.empty())
    //     {
    //         path.push_back(currentState);
    //         currentState = parent[currentState];
    //     }
    //     std::reverse(path.begin(), path.end());
    //     auto end = std::chrono::high_resolution_clock::now(); //  Kết thúc đo
    //     std::chrono::duration<double> elapsed = end - start;
    //     std::cout << "time count: " << elapsed.count() << " seccond\n";
    //     std::cout << "Solution found in " << path.size() - 1 << " moves:" << std::endl;
    //     for (const auto &state : path)
    //     {
    //         std::cout << state << std::endl;
    //     }
    // }
    // else
    // {
    //     std::cout << "No solution found." << std::endl;
    // }

    IDAStar(initial);
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Time count: " << elapsed.count() << " seconds" << std::endl;
}



bool findNeigh(vector<Board> &array, Board &x)
{
    for (Board &a : array)
    {
        if (a.equal(x))
            return true;
    }
    return false;
}


//sort in decending order
void sortNeigh(vector<Board> &array, int g)
{
    for (int i = 0; i < array.size() - 1; i++)
    {
        for (int j = i + 1; j < array.size(); j++)
        {
            if ((array[i].heuristic() + g) > (array[j].heuristic() + g)) swap(array[i], array[j]);
        }
    }
}

int Search(vector<Board> &path, int g, int bound)
{
    Board current = path.back();
    int f = g + current.heuristic();

    if (f > bound)
        return f;
    if (current.isGoal())
        return -1;

    int min = INT_MAX;
    vector<Board> neighbors = current.neighbors();
    sortNeigh(neighbors, g + 1);
    
    for (Board &neigh : neighbors)
    {
        if (!findNeigh(path, neigh))
        {
            path.push_back(neigh);
            int temp = Search(path, g + 1, bound);
            if (temp == -1)
                return -1;
            if (temp < min)
                min = temp;
            path.pop_back();
        }
    }
    return min;
}

void Solver::IDAStar(Board &initial)
{
    int bound = initial.heuristic();
    vector<Board> path;
    path.push_back(initial);

    while (true)
    {
        int temp = Search(path, 0, bound);
        if (temp == -1)
        {
            cout << "Solution Found in : " << path.size() << endl;
            cout << "Path" << endl;
            for (Board &x : path)
            {
                cout << x.toString() << endl;
            }
            return;
        }
        if (temp == INT_MAX)
        {
            cout << "No solution" << endl;
        }
        bound = temp;
    }
}
