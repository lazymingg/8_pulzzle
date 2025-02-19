
#include "Board.h"
#include "Solver.h"
#include "PatternDataBase.h"
using namespace std;


//init pattern database
PatternDataBase *PatternDataBase::instance = nullptr;

int main()
{

    //init pattern database
    PatternDataBase::getInstance()->generatePatternDB(3);
    PatternDataBase::getInstance()->writePatternDB();
    cout << "Pattern database writed" << endl;
    // PatternDataBase::getInstance()->readPatternDB();
    cout << "Pattern database readed" << endl;
    cout << "Number of patterns: " << PatternDataBase::getInstance()->getNumberOfPatterns() << endl;


    Board b(3, false);
    while (!b.isSolvable())
    {
        b = Board(3, false);
    }
    cout << b.toString();
    cout << "Mahanattan: " << b.mahanattan() << endl;
    cout << "Hamming: " << b.hamming() << endl;
    cout << "Is goal: " << b.isGoal() << endl;
    cout << "Is solvable: " << b.isSolvable() << endl;

    if (b.isSolvable())
    {
        Solver solver(b);
    }



    return 0;
}