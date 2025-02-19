#include "Solver.h"
#include <iostream>
#include <algorithm>

Solver::Solver(Board initial) : initial(initial), moves(0)
{
    // auto start = std::chrono::high_resolution_clock::now();

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
}

int search(Board &node, int threshold, unordered_map<string, string> &parent)
{
    int f = node.extractHeuristicFromPatternDB();
    if (f > threshold)
        return f;
    if (node.isGoal())
    {
        cout << "Solution found " << endl;
        return -1;
    }
    
    int minThreshold = INT_MAX;

    priority_queue<Board, vector<Board>, greater<Board>> pq;
    for (Board &neighbor : node.neighbors())
    {
        if (parent.find(neighbor.toString()) == parent.end())
        {
            pq.push(neighbor);
        }
    }

    while (!pq.empty())
    {
        Board neighbor = pq.top();
        pq.pop();
        parent[neighbor.toString()] = node.toString();

        int temp = search(neighbor, threshold, parent);
        if (temp == -1)
            return -1;
        minThreshold = min(minThreshold, temp);
        parent.erase(neighbor.toString()); // Backtracking
    }
    return minThreshold;
}


void Solver::IDAStar(Board &start)
{
    int threshold = start.extractHeuristicFromPatternDB();
    unordered_map<string, string> parent;
    parent[start.toString()] = ""; // Trạng thái ban đầu không có cha

    while (true)
    {
        int temp = search(start, threshold, parent);
        if (temp == -1)
        {
            // Tìm trạng thái goal trong `parent`
            Board goalState(4, true);

            // Truy vết đường đi từ trạng thái goal
            vector<string> path;
            string currentState = goalState.toString();
            while (!currentState.empty() && parent.find(currentState) != parent.end())
            {
                path.push_back(currentState);
                currentState = parent[currentState]; // Đi ngược lên cha
            }

            // In kết quả
            cout << "Solution found in " << path.size() - 1 << " moves:" << endl;
            reverse(path.begin(), path.end());
            for (const auto &state : path)
            {
                cout << state << endl;
            }
            break;
        }
        if (temp == INT_MAX)
        {
            cout << "No solution found." << endl;
            break;
        }
        threshold = temp;
    }
}

