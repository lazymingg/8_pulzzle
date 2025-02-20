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

// int search(Board &node, int threshold, unordered_map<string, string> &parent)
// {
//     int f = node.extractHeuristicFromPatternDB() + node.g;
//     cout << "g" << node.g << endl;
//     if (f > threshold)
//         return f;
//     if (node.isGoal())
//     {
//         cout << "Solution found " << endl;
//         return -1;
//     }
    
//     int minThreshold = INT_MAX;

//     // Lấy vector hàng xóm và (tùy chọn) sắp xếp chúng theo f nếu cần
//     vector<Board> nbrs = node.neighbors();
//     // Nếu muốn sắp xếp:
//     sort(nbrs.begin(), nbrs.end(), [](const Board &a, const Board &b) {
//         return a.extractHeuristicFromPatternDB() + a.g < b.extractHeuristicFromPatternDB() + b.g;
//     });

//     for (Board &neighbor : nbrs)
//     {
//         if (parent.find(neighbor.toString()) == parent.end())
//         {
//             parent[neighbor.toString()] = node.toString();
//             int temp = search(neighbor, threshold, parent);
//             if (temp == -1)
//                 return -1;
//             minThreshold = min(minThreshold, temp);
//             parent.erase(neighbor.toString()); // Backtracking
//         }
//     }
//     return minThreshold;
// }

// void Solver::IDAStar(Board &start)
// {
//     int threshold = start.extractHeuristicFromPatternDB() + start.g;
//     unordered_map<string, string> parent;
//     parent[start.toString()] = "";

//     // Lưu board goal khi tìm thấy (có thể cần biến global hoặc truyền qua tham số)
//     Board goalState = Board(start.getSize(), true); 
//     while (true)
//     {
//         int temp = search(start, threshold, parent);
//         if (temp == -1)
//         {
//             // Ở đây, thay vì tạo board mới, hãy lấy board goal thật sự
//             // Giả sử rằng board goal có toString() trùng với trạng thái đích
//             // Truy vết đường đi từ trạng thái goal bằng parent map
//             vector<string> path;
//             string currentState = goalState.toString(); // Cần đảm bảo goalState đã được cập nhật
//             while (!currentState.empty() && parent.find(currentState) != parent.end())
//             {
//                 path.push_back(currentState);
//                 currentState = parent[currentState];
//             }

//             cout << "Solution found in " << path.size() - 1 << " moves:" << endl;
//             reverse(path.begin(), path.end());
//             for (const auto &state : path)
//             {
//                 cout << state << endl;
//             }
//             break;
//         }
//         if (temp == INT_MAX)
//         {
//             cout << "No solution found." << endl;
//             break;
//         }
//         threshold = temp;
//     }
// }



// using mahanattan distance as heuristic version

int search(Board &node, int threshold, unordered_map<string, string> &parent)
{
    int f = node.mahanattan() + node.g;
    if (f > threshold)
        return f;
    if (node.isGoal())
    {
        cout << "Solution found " << endl;
        return -1;
    }
    
    int minThreshold = INT_MAX;

    vector<Board> nbrs = node.neighbors();
    sort(nbrs.begin(), nbrs.end(), [](const Board &a, const Board &b) {
        return a.mahanattan() + a.g < b.mahanattan() + b.g;
    });

    for (Board &neighbor : nbrs)
    {
        if (parent.find(neighbor.toString()) == parent.end())
        {
            parent[neighbor.toString()] = node.toString();
            int temp = search(neighbor, threshold, parent);
            if (temp == -1)
                return -1;
            minThreshold = min(minThreshold, temp);
            parent.erase(neighbor.toString()); //Backtracking
        }
    }
    return minThreshold;
}

void Solver::IDAStar(Board &start)
{
    int threshold = start.mahanattan() + start.g;
    unordered_map<string, string> parent;
    parent[start.toString()] = "";

    Board goalState = Board(start.getSize(), true); 
    while (true)
    {
        int temp = search(start, threshold, parent);
        if (temp == -1)
        {
            vector<string> path;
            string currentState = goalState.toString();
            while (!currentState.empty() && parent.find(currentState) != parent.end())
            {
                path.push_back(currentState);
                currentState = parent[currentState];
            }

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


// int search(Board node, int threshold, unordered_map<string, int> &g_values, unordered_map<string, string> &parent)
// {
//     int f = node.mahanattan() + node.g;
//     if (f > threshold)
//         return f;
//     if (node.isGoal())
//     {
//         cout << "Solution found" << endl;
//         return -1;
//     }
    
//     int minThreshold = INT_MAX;
//     vector<Board> nbrs = node.neighbors();
    
//     // Cập nhật g cho các trạng thái hàng xóm trước khi sắp xếp
//     for (Board &neighbor : nbrs)
//     {
//         neighbor.g = node.g + 1;
//     }
    
//     // Sắp xếp hàng xóm theo giá trị f(n) = g + h
//     sort(nbrs.begin(), nbrs.end(), [](const Board &a, const Board &b) {
//         return a.mahanattan() + a.g < b.mahanattan() + b.g;
//     });

//     for (Board &neighbor : nbrs)
//     {
//         string neighborKey = neighbor.toString();
//         if (g_values.find(neighborKey) == g_values.end() || neighbor.g < g_values[neighborKey])
//         {
//             parent[neighborKey] = node.toString();
//             g_values[neighborKey] = neighbor.g; // Lưu giá trị g tốt nhất

//             int temp = search(neighbor, threshold, g_values, parent);
//             if (temp == -1)
//                 return -1;
//             minThreshold = min(minThreshold, temp);
//         }
//     }
//     return minThreshold;
// }

// void Solver::IDAStar(Board &start)
// {
//     if (start.isGoal()) {
//         cout << "Start state is already the goal." << endl;
//         return;
//     }
    
//     int threshold = start.mahanattan();
//     unordered_map<string, string> parent;
//     unordered_map<string, int> g_values;
//     parent[start.toString()] = "";
//     g_values[start.toString()] = 0;

//     Board goalState = Board(start.getSize(), true);
//     while (true)
//     {
//         Board currentState = start; // Tạo bản sao để tránh ghi đè
//         int temp = search(currentState, threshold, g_values, parent);
//         if (temp == -1)
//         {
//             vector<string> path;
//             string currentState = goalState.toString();
//             while (!currentState.empty() && parent.find(currentState) != parent.end())
//             {
//                 path.push_back(currentState);
//                 currentState = parent[currentState];
//             }

//             cout << "Solution found in " << path.size() - 1 << " moves:" << endl;
//             reverse(path.begin(), path.end());
//             for (const auto &state : path)
//             {
//                 cout << state << endl;
//             }
//             break;
//         }
//         if (temp == INT_MAX)
//         {
//             cout << "No solution found." << endl;
//             break;
//         }
//         threshold = temp;
//     }
// }
