#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

#define INPUT_PATH "../../rec/day_2.txt"

// Return true if the input is safe for puzzle 1
bool isInputSafe(std::vector<int> &levelList)
{
    // a list of size 1 is not a list
    if (levelList.size() < 2)
    {
        return false;
    }

    int diff = (levelList[1] - levelList[0]);
    bool isUptrend = (diff > 0);

    for (int i = 1; i < levelList.size(); i++)
    {
        diff = levelList[i] - levelList[i - 1];
        // the difference should be less then 3 and never 0
        if (diff == 0 || std::abs(diff) > 3)
        {
            return false;
        }
        // the trend should not be changed
        if (isUptrend != (diff > 0))
        {
            return false;
        }
    }

    return true;
}

// 'soft safe' for puzzle 2
bool isSoftInputSafe(std::vector<int> &levelList)
{
    if (levelList.size() < 2)
    {
        return false;
    }
    // if input safe directly, dont need to go further
    if (isInputSafe(levelList))
    {
        return true;
    }

    int diff = (levelList[1] - levelList[0]);
    bool isUptrend = (diff > 0);

    for (int i = 0; i < levelList.size(); i++)
    {
        std::vector<int> softLevelList;
        softLevelList.reserve(levelList.size() - 1);
        // Try the input again if it is safe with one digit less
        for (int j = 0; j < levelList.size(); j++)
        {
            if (i != j)
            {
                softLevelList.push_back(levelList[j]);
            }
        }
        if (isInputSafe(softLevelList))
        {
            return true;
        }
    }

    return false;
}

// general function to read input and pass to count functions
std::pair<int, int> countSafeInput()
{
    std::ifstream input(INPUT_PATH);
    if (!input)
    {
        std::cerr << "Error: Failed to open puzzle_2.txt" << std::endl;
        return std::make_pair(0, 0);
    }

    std::string line;
    int safeCount = 0;
    int softSafeCount = 0;

    while (std::getline(input, line))
    {
        std::istringstream fileStream(line);
        int num = 0;
        std::vector<int> levelList;

        while (fileStream >> num)
        {
            levelList.push_back(num);
        }
        safeCount += (isInputSafe(levelList) ? 1 : 0);
        softSafeCount += (isSoftInputSafe(levelList) ? 1 : 0);
    }

    return std::make_pair(safeCount, softSafeCount);
}

int main()
{
    auto safeInputCount = countSafeInput();
    std::cout << "Safe input count is: " << safeInputCount.first << std::endl;
    std::cout << "Soft safe input count is: " << safeInputCount.second << std::endl;
    return 0;
}
