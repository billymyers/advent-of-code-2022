#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
using std::uint32_t;

bool visible(const std::vector<std::string> &grid, size_t x, size_t y)
{
    char value = grid[y][x];
    if(x == 0 || y == 0)
        return true;

    if(x == grid.size() - 1 || y == grid.size() - 1)
        return true;

    // need to check all four directions - if one direction is visible, then true

    bool up, down, left, right;
    up = down = left = right = true;

    // look up first
    for (auto i = 0; i < y; ++i)
    {
        if(grid[i][x] >= value)
        {
            up = false;
            break;
        }
    }

    if(up)
        return true;

    // down
    for (auto i = grid.size() - 1; i > y; --i)
    {
        if(grid[i][x] >= value)
        {
            down = false;
            break;
        }
    }

    if(down)
        return true;

    // left
    for (auto i = 0; i < x; ++i)
    {
        if(grid[y][i] >= value)
        {
            left = false;
            break;
        }
    }

    if(left)
        return true;

    // right
    for (auto i = grid.size() - 1; i > x; --i)
    {
        if(grid[y][i] >= value)
        {
            right = false;
            break;
        }
    }

    return right;
}

uint32_t scenicScore(const std::vector<std::string> &grid, size_t x, size_t y)
{
    char value = grid[y][x];
    uint32_t result = 0;
    uint32_t temp = 1;

    if(x == 0 || y == 0 || x == grid.size() - 1 || y == grid.size() - 1)
        return 0;

    // Up first
    for (auto i = 1; i <= y; i++)
    {
        temp = i;
        if(grid[y-i][x] >= value)
            break;
    }

    result = temp;

    // Down
    for (auto i = 1; i <= (grid.size() - y - 1); i++)
    {
        temp = i;
        if(grid[y+i][x] >= value)
            break;
    }

    result *= temp;

    // Left
    for (auto i = 1; i <= x; i++)
    {
        temp = i;
        if(grid[y][x-i] >= value)
            break;
    }

    result *= temp;

    // Right
    for (auto i = 1; i <= (grid.size() - x - 1); i++)
    {
        temp = i;
        if(grid[y][x+i] >= value)
            break;
    }

    result *= temp;

    return result;
}

int main(void) {

    auto start = Clock::now();
    // Read file
    std::ifstream in("input.txt");
    std::string str;
    std::vector<std::string> grid;
    std::size_t columns;

    // Create grid
    while(std::getline(in, str))
    {
        auto len = str.size();
        columns = len;
        grid.push_back(str);
    }

    in.close();
    auto readFile = Clock::now();

    uint32_t visibleTreeCount = 0;
    uint32_t bestScenicScore = 0;

    // Process grid - double for loops :(
    for (auto i = 0; i < grid.size(); i++)
    {
        for (auto j = 0; j < columns; j++)
        {
            auto vis = visible(grid, j, i);
            visibleTreeCount += static_cast<uint32_t>(vis);

            auto score = scenicScore(grid, j, i);
            bestScenicScore = (score < bestScenicScore) ? bestScenicScore : score;
        }
    }

    auto stop = Clock::now();

    std::cout << "Part 1 total: " << visibleTreeCount << std::endl;
    std::cout << "Part 2 score: " << bestScenicScore << std::endl;
    std::cout << "Total time for program: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " us" << std::endl;
    std::cout << "File read: " << std::chrono::duration_cast<std::chrono::microseconds>(readFile - start).count() << " us" << std::endl;
    std::cout << "Processing: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - readFile).count() << " us" << std::endl;
}