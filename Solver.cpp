#include "Solver.h"
#include <iostream>
#include <algorithm>

Solver::Solver(Board initial) : initial(initial), moves(0)
{
    std::unordered_set<std::string> visited;
    std::priority_queue<Board, std::vector<Board>, std::greater<Board>> pq;
    std::unordered_map<std::string, std::string> parent;

    pq.push(initial);
    parent[initial.toString()] = "";

    Board goalBoard(0, true);
    bool found = false;

    while (!pq.empty())
    {
        Board current = pq.top();
        pq.pop();

        if (visited.find(current.toString()) != visited.end())
            continue;
        visited.insert(current.toString());

        if (current.isGoal())
        {
            goalBoard = current;
            found = true;
            break;
        }

        std::vector<Board> neighbors = current.neighbors();
        for (Board neighbor : neighbors)
        {
            if (visited.find(neighbor.toString()) == visited.end())
            {
                if (parent.find(neighbor.toString()) == parent.end())
                    parent[neighbor.toString()] = current.toString();
                pq.push(neighbor);
            }
        }
    }

    if (found)
    {
        std::vector<std::string> path;
        std::string currentState = goalBoard.toString();
        while (!currentState.empty())
        {
            path.push_back(currentState);
            currentState = parent[currentState];
        }
        std::reverse(path.begin(), path.end());

        std::cout << "Solution found in " << path.size() - 1 << " moves:" << std::endl;
        for (const auto &state : path)
        {
            std::cout << state << std::endl;
        }
    }
    else
    {
        std::cout << "No solution found." << std::endl;
    }
}

void Solver::storePatternDatabase()
{
    Board solvedBoard(this->initial.getSize(), true);
    solvedBoard = solvedBoard.zero5678();

    std::queue<Board> q;
    q.push(solvedBoard);
    // Đánh dấu trạng thái goal ngay từ đầu
    patternDatabase[solvedBoard.toString()] = 0;
    
    int level = 0;
    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            Board current = q.front();
            q.pop();
            // current đã được đánh dấu khi được push, có thể dùng cho các mục đích khác
            
            
            for (Board &neighbor : current.neighbors())
            {
                string neighborKey = neighbor.toString();
                // Nếu neighbor chưa được duyệt, đánh dấu ngay khi push vào queue
                if (patternDatabase.find(neighborKey) == patternDatabase.end())
                {
                    patternDatabase[neighborKey] = level + 1;
                    q.push(neighbor);
                }
            }
        }
        level++;
    }
}


std::unordered_map<std::string, int> Solver::getPatternDatabase()
{
    return this->patternDatabase;
}
