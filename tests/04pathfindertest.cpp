#include <iostream>

#include "../include/Pathfinder.hpp"

int main() 
{
    std::cout << "# Testing Pathfinder" << std::endl;

    int g_width = 10;
    int g_height = 10;

    Pathfinder pf(g_width, g_height);

    std::vector<std::pair<int, int>> result;

    std::vector<int> grid;

    grid.resize(g_width * g_height);
    std::fill(grid.begin(), grid.end(), 1);
    grid[pf.gridIndex(0,1)] = 0;
    grid[pf.gridIndex(5,0)] = 0;
    grid[pf.gridIndex(5,1)] = 0;
    grid[pf.gridIndex(5,2)] = 0;
    grid[pf.gridIndex(5,3)] = 0;
    grid[pf.gridIndex(5,4)] = 0;
    grid[pf.gridIndex(5,5)] = 0;
    grid[pf.gridIndex(5,6)] = 0;
    grid[pf.gridIndex(5,7)] = 0;
    grid[pf.gridIndex(5,8)] = 0;

    int start_i = 1;
    int start_j = 2;
    int end_i = 9;
    int end_j = 5;

    pf.setGrid(grid);
    
    bool found = pf.searchAStar(start_i, start_j, end_i, end_j, true, result);

    // for (auto &node : result) 
    // {
    //     std::cout << node.first << ", " << node.second << "\n";
    // }

    pf.printGrid(start_i, start_j, end_i, end_j, result);
    std::cout << "Path " << (found ? "" : "not ") << "found after " << pf.getRuns() << " runs." << "\n";

    return 0;
}