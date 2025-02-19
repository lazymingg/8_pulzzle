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
    // this->notZeroCase.push_back({1,2,3,6,15});
    // this->notZeroCase.push_back({4,5,8,9,12});
    // this->notZeroCase.push_back({7,10,11,13,14});

    this->notZeroCase.push_back({1, 2, 3, 4});
    this->notZeroCase.push_back({5, 6, 7, 8});
    // this->notZeroCase.push_back({2, 4, 6, 8});

    vector<Board> goalStates;
    // generate goal states
    for (vector<int> notZero : notZeroCase)
    {
        Board goal(size, true);
        goal = goal.zeroExcept(notZero);
        goalStates.push_back(goal);
        
        cout << "Goal state: " << goal.toString() << endl;
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
                        q.push(neighbor);
                    }
                }
            }
            level++;
        }
    }
}

int PatternDataBase::lookup(string pattern)
{
    return patternDB[pattern];
}

int PatternDataBase::lookup(const Board& board)
{
    int max = 0;
    for (vector<int> notZero : notZeroCase)
    {
        Board temp = board.zeroExcept(notZero);
        string pattern = temp.hashString();
        int moves = lookup(pattern);
        if (moves > max)
        {
            max = moves;
        }
    }
    return max;
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
        insert(pattern, distance);
    }

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
