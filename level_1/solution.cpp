#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <unordered_map>

#define INPUT_PATH "../../rec/day_1.txt"

// Calculate the distence for puzzle 1
int distance(std::vector<int> &left, std::vector<int> &right)
{
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int totalDistance = 0;
    for (size_t i = 0; i < left.size(); i++)
    {
        totalDistance += std::abs(left[i] - right[i]);
    }

    return totalDistance;
}

// Calculate the similarity for puzzle 2
int similarityScore(std::vector<int> &left, std::vector<int> &right)
{
    int similarity = 0;

    std::unordered_map<int, int> rightOccurance;
    for (int elm : right)
    {
        ++rightOccurance[elm];
    }

    for (int elm : left)
    {
        similarity += elm * rightOccurance[elm];
    }

    return similarity;
}

// get the integers from the input text
bool getIntegers(std::vector<int> &left, std::vector<int> &right)
{
    std::ifstream input(INPUT_PATH);
    if (!input)
    {
        std::cerr << "Error: Failed to open puzzle_1.txt" << std::endl;
        return false;
    }

    std::string line;

    while (std::getline(input, line))
    {
        std::istringstream fileStream(line);
        int col1 = 0, col2 = 0;
        if (!(fileStream >> col1 >> col2))
        {
            std::cerr << "Error: Failed to read line n: " << line << std::endl;
            return false;
        }
        left.push_back(col1);
        right.push_back(col2);
    }

    if (left.size() != right.size())
    {
        std::cerr << "Error: Left and right vector dont have the same size!" << std::endl;
        return false;
    }

    return true;
}

int main()
{
    std::vector<int> left, right;
    bool haveInput = getIntegers(left, right);
    if (haveInput)
    {
        int totalDistance = distance(left, right);
        std::cout << "Total distance: " << totalDistance << std::endl;

        int similarity = similarityScore(left, right);
        std::cout << "Similarity: " << similarity << std::endl;
    }

    return 0;
}
