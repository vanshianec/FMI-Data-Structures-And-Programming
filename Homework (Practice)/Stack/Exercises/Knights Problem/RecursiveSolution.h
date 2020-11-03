#include <iostream>

const int size = 3;
char board[size][size] = {{'-', '-', '-'},
                          {'-', '-', '-'},
                          {'-', '-', '-'}};

bool isPositionTaken(int row, int col)
{
    return board[row][col] == 'H';
}

bool isPositionValid(int row, int col)
{
    return row >= 0 && row < size && col >= 0 && col < size;
}

bool canAttackPosition(int row, int col)
{
    return isPositionValid(row, col) && isPositionTaken(row, col);
}

bool canKnightAttack(int row, int col)
{
    int currentRow = row - 2, currentCol = col + 1;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row - 2;
    currentCol = col - 1;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row - 1;
    currentCol = col + 2;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row - 1;
    currentCol = col - 2;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row + 2;
    currentCol = col + 1;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row + 2;
    currentCol = col - 1;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row + 1;
    currentCol = col - 2;
    if (canAttackPosition(currentRow, currentCol))
    {
        return true;
    }
    currentRow = row + 1;
    currentCol = col + 2;

    return canAttackPosition(currentRow, currentCol);
}

bool canPlaceKnight(int row, int col)
{
    return isPositionValid(row, col) && !isPositionTaken(row, col) && !canKnightAttack(row, col);
}

void print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void solve(int k, int count, int index)
{
    if (count == k)
    {
        print();
        std::cout << std::endl;
        return;
    }

    for (int i = index; i < size * size; i++)
    {
        int currentRow = i / size, currentCol = i % size;
        if (canPlaceKnight(currentRow, currentCol))
        {
            board[currentRow][currentCol] = 'H';
            solve(k, count + 1, i + 1);
            board[currentRow][currentCol] = '-';
        }
    }
}
