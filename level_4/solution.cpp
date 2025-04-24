#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define INPUT_PATH "../../rec/day_4.txt"

// Is xmas matched for puzzle one with the help of 8 directions
bool isMatched(const std::vector<std::string> &inputText, int xIn, int yIn, int xDirection, int yDirection)
{
    const std::string STR = "XMAS";
    int rowNb = inputText.size();
    int colNb = inputText[0].size();

    for (int i = 0; i < STR.length(); i++)
    {
        int x = xIn + i * xDirection;
        int y = yIn + i * yDirection;

        if (x < 0 || y < 0 || x >= rowNb || y >= colNb)
        {
            return false;
        }

        if (inputText[x][y] != STR[i])
        {
            return false;
        }
    }

    return true;
}

// cout xmas number by go through each letter for puzzle 1
int xmasCount(const std::vector<std::string> &inputText, const std::vector<std::pair<int, int>> &directions)
{
    int count = 0;
    int rowNb = inputText.size();
    int colNb = inputText[0].size();

    for (int i = 0; i < rowNb; i++)
    {
        for (int j = 0; j < colNb; j++)
        {
            for (const auto &[xDirection, yDirection] : directions)
            {
                if (isMatched(inputText, i, j, xDirection, yDirection))
                {
                    ++count;
                }
            }
        }
    }

    return count;
}

bool isX(const std::string &s)
{
    return s == "MAS" || s == "SAM";
}

// cout xmas number by go through each letter starting from the second letter of row and col for puzzle 2
int xShapeCount(const std::vector<std::string> &inputText)
{
    int count = 0;
    int rows = inputText.size();
    int cols = inputText[0].size();

    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            // Build the two words
            std::string mas = "";
            mas += inputText[i - 1][j - 1];
            mas += inputText[i][j];
            mas += inputText[i + 1][j + 1];

            std::string sam = "";
            sam += inputText[i - 1][j + 1];
            sam += inputText[i][j];
            sam += inputText[i + 1][j - 1];

            if (isX(mas) && isX(sam))
            {
                ++count;
            }
        }
    }

    return count;
}

std::pair<int, int> counters(const std::vector<std::pair<int, int>> &directions)
{
    std::ifstream file(INPUT_PATH);
    if (!file)
    {
        std::cerr << "Failed to open input file!" << std::endl;
        return std::pair(0, 0);
    }

    std::vector<std::string> text;
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
            text.push_back(line);
    }

    int result = xmasCount(text, directions);
    int resultX = xShapeCount(text);
    return std::pair(result, resultX);
}

int main()
{
    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, // down
        {0, 1}, // right

        {-1, 0}, // up
        {0, -1}, // left

        {1, 1},  // down right
        {1, -1}, // down left

        {-1, -1}, // up left
        {-1, 1},  // up right
    };

    auto res = counters(directions);
    std::cout << "Total XMAS matches: " << res.first << std::endl;
    std::cout << "Total X-MAS matches: " << res.second << std::endl;

    return 0;
}
