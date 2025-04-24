#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

#define INPUT_PATH "../../rec/day_3.txt"

// Get the multilplication for puzzle 1
int resLine(std::string &line, std::regex &format)
{
    int res = 0;

    auto begin = std::sregex_iterator(line.begin(), line.end(), format);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        int a = std::stoi((*it)[1].str());
        int b = std::stoi((*it)[2].str());
        res += a * b;
    }

    return res;
}

// Get the multilplication with enable and disable for puzzle 2
int resLineWithEnable(std::string &line, std::regex &format)
{
    int res = 0;

    auto begin = std::sregex_iterator(line.begin(), line.end(), format);
    auto end = std::sregex_iterator();
    bool enable = true;

    for (auto it = begin; it != end; ++it)
    {
        std::string str = (*it).str();

        if (str == "do()")
        {
            enable = true;
        }
        else if (str == "don't()")
        {
            enable = false;
        }
        else
        {
            if (enable)
            {
                int a = std::stoi((*it)[1].str());
                int b = std::stoi((*it)[2].str());
                res += a * b;
            }
        }
    }

    return res;
}

// general function to get all the multiplication for puzzle 1 and 2
std::pair<int, int> mulAll()
{
    std::ifstream input(INPUT_PATH);
    if (!input)
    {
        std::cerr << "Error: Failed to open puzzle_3.txt" << std::endl;
        return std::make_pair(0, 0);
    }

    std::string line;
    std::string allInput;
    while (std::getline(input, line))
    {
        allInput += line;
    }

    std::regex format(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    std::regex formatWithEnable(R"(do\(\)|don't\(\)|mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    int ans = resLine(allInput, format);
    int ansWithEnable = resLineWithEnable(allInput, formatWithEnable);

    return std::make_pair(ans, ansWithEnable);
}

int main()
{
    auto safeInputCount = mulAll();
    std::cout << "Multiplication answer: " << safeInputCount.first << std::endl;
    std::cout << "Multiplication with enable answer: " << safeInputCount.second << std::endl;

    return 0;
}
