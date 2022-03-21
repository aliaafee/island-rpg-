#include <iostream>

using namespace std;

int main()
{
    std::cout << "# Testing Diagonal" << std::endl;

    int cols = 10;

    for (int d = 0; d < cols; d++)
    {
        for (int j = 0; j < d + 1; j++)
        {
            int i = d - j;
            cout << i << "," << j << "\n";
        }
    }
    for (int d = 1; d < cols; d++)
    {
        for (int j = d; j < cols; j++)
        {
            cout << cols + d - j - 1 << "," << j << "\n";
        }
    }

    cout << "\n";

    DiagonalIterateGrid iterg(10);

    int i, j;
    while (iterg.next(i, j))
    {
        cout << i << "," << j << "\n";
    }
}