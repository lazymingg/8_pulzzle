
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
    // PatternDataBase::getInstance()->generatePatternDB(4);
    // PatternDataBase::getInstance()->writePatternDB();
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
    // 5 15 4 3 
    // 12 14 8 10 
    // 7 9 11 6 
    // 2 0 1 13 

    Board b(4, false);
    b.setTileAt(0, 0, 5);
    b.setTileAt(0, 1, 15);
    b.setTileAt(0, 2, 4);
    b.setTileAt(0, 3, 3);
    b.setTileAt(1, 0, 12);
    b.setTileAt(1, 1, 14);
    b.setTileAt(1, 2, 8);
    b.setTileAt(1, 3, 10);
    b.setTileAt(2, 0, 7);
    b.setTileAt(2, 1, 9);
    b.setTileAt(2, 2, 11);
    b.setTileAt(2, 3, 6);
    b.setTileAt(3, 0, 2);
    b.setTileAt(3, 1, 0);
    b.setTileAt(3, 2, 1);
    b.setTileAt(3, 3, 13);

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
 