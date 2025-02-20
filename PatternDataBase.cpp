#include "PatternDataBase.h"

PatternDataBase::PatternDataBase()
{
}

PatternDataBase *PatternDataBase::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PatternDataBase();
    }
    return instance;
}

void PatternDataBase::generatePatternDB(int size)
{
    if (size == 3)
    {
        this->notZeroCase.push_back({1, 2, 3, 4});
        this->notZeroCase.push_back({5, 6, 7, 8});
    }
    if (size == 4)
    {
        this->notZeroCase.push_back({1,2,3,6,15});
        this->notZeroCase.push_back({4,5,8,9,12});
        this->notZeroCase.push_back({7,10,11,13,14});
    }


    vector<Board> goalStates;
    // generate goal states
    for (vector<int> notZero : notZeroCase)
    {
        Board goal(size, true);
        goal = goal.zeroExcept(notZero);
        goalStates.push_back(goal);
    }


    for (Board &goal : goalStates)
    {

        cout << "Generating patternDB for goal state: " << goal.toString() << endl;

        std::queue<Board> q;
        q.push(goal);
        // mark goal state from the beginning this level 0
        insert(goal.hashString(), 0);

        // BFS to generate patternDB starting from level 1
        int level = 1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                Board current = q.front();
                q.pop();

                for (Board &neighbor : current.neighbors())
                {
                    string neighborKey = neighbor.hashString();

                    // if neighbor is not in patternDB yet
                    if (patternDB.find(neighborKey) == patternDB.end())
                    {
                        insert(neighborKey, level);
                        // cout << "level: " << level << "g: " << neighbor.g << endl;
                        q.push(neighbor);
                    }
                }
            }
            level++;
        }
    }
}

// int PatternDataBase::lookup(string pattern)
// {
//     return patternDB[pattern];
// }

int PatternDataBase::lookup(const Board& board)
{
    int sum = 0;
    for (vector<int> notZero : notZeroCase)
    {
        Board temp = board.zeroExcept(notZero);

        string pattern = temp.hashString();
        sum += patternDB[pattern];
    }
    return sum;

}

void PatternDataBase::writePatternDB()
{
    std::ofstream file("patternDB.txt");
    if (!file) // Kiểm tra lỗi mở file
    {
        std::cerr << "Error: Cannot open patternDB.txt for writing.\n";
        return;
    }

    for (const auto &[pattern, distance] : patternDB)
    {
        file << pattern << " " << distance << "\n";
    }
    file.close();
}

void PatternDataBase::readPatternDB()
{
    std::ifstream file("patternDB.txt");
    if (!file) // Kiểm tra lỗi mở file
    {
        std::cerr << "Error: Cannot open patternDB.txt for reading.\n";
        return;
    }

    std::string pattern;
    int distance;
    while (file >> pattern >> distance)
    {
        patternDB[pattern] = distance;

    }

    // //verify read data read vs written data
    // // loop through patternDB and compare with newPatternDB
    // for (const auto &[pattern, distance] : patternDB)
    // {
    //     if (newPatternDB[pattern] != distance)
    //     {
    //         std::cerr << "Error: PatternDB read failed, possible corruption.\n";
    //         return;
    //     }
    // }

    // cout << "PatternDB read successfully" << endl;

    // patternDB = newPatternDB;

    if (file.fail() && !file.eof()) // Kiểm tra nếu file có lỗi khi đọc
    {
        std::cerr << "Error: File reading failed, possible corruption.\n";
    }

    file.close();
}

void PatternDataBase::insert(string pattern, int moves)
{
    this->patternDB[pattern] = moves;
}

int PatternDataBase::getNumberOfPatterns()
{
    return patternDB.size();
}
