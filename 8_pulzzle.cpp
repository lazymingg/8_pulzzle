
#include "Board.h"
#include "Solver.h"
#include "PatternDataBase.h"
#include <chrono>
using namespace std;

// init pattern database
PatternDataBase *PatternDataBase::instance = nullptr;

int main()
{

    // init pattern database
    PatternDataBase::getInstance()->generatePatternDB(3);
    PatternDataBase::getInstance()->writePatternDB();
    cout << "Pattern database writed" << endl;
    // PatternDataBase::getInstance()->readPatternDB();
    cout << "Pattern database readed" << endl;
    cout << "Number of patterns: " << PatternDataBase::getInstance()->getNumberOfPatterns() << endl;

    // double totalTime = 0.0;
    // int solvedCount = 0;

    // // Giải 100 board ngẫu nhiên
    // for (int i = 0; i < 100; i++)
    // {
    //     Board b(3, false);
    //     while (!b.isSolvable())
    //     {
    //         b = Board(3, false);
    //     }

    //     // Đo thời gian giải cho board hiện tại
    //     auto start = std::chrono::high_resolution_clock::now();
    //     Solver solver(b);
    //     auto end = std::chrono::high_resolution_clock::now();

    //     std::chrono::duration<double> elapsed = end - start;
    //     totalTime += elapsed.count();
    //     solvedCount++;

    //     cout << "Board " << i + 1 << " solved in " << elapsed.count() << " seconds." << endl;
    // }

    // double averageTime = totalTime / solvedCount;
    // cout << "Average time over " << solvedCount << " boards: " << averageTime << " seconds." << endl;

    // solve one board
    Board b(4, false);
    while (!b.isSolvable())
    {
        b = Board(4, false);
    }

    
    cout << "Initial board: " << endl;
    cout << b.toString();
    cout << "Mahanattan: " << b.mahanattan() << endl;
    cout << "Hamming: " << b.hamming() << endl;
    cout << "========Is solvable: " << b.isSolvable() << endl;

    // check solved board
    Board solvedBoard(4, true);
    cout << solvedBoard.toString();
    cout << "isGoal: " << solvedBoard.isGoal() << endl;


    // if (b.isSolvable())
    // {
        Solver solver(b);
    // }

    
    return 0;
}
 