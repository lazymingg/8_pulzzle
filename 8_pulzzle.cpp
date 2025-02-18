
#include "Board.h"
#include "Solver.h"
using namespace std;


int main()
{
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
        solver.storePatternDatabase();
        auto patternDatabase = solver.getPatternDatabase();
        cout << "Pattern database:" << endl;
        int count = 0;
        for (const auto &[pattern, distance] : patternDatabase)
        {
            count++;
            cout << pattern << " -> " << distance << endl;
        }
        cout << "Total patterns: " << count << endl;
        
    }



    return 0;
}