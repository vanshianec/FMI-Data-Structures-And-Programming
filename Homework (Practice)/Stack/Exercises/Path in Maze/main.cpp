#include <iostream>
#include <stack>

const int labSize = 8;
int lab[labSize][labSize] = {0, 1, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 1, 0, 0, 0,
                             1, 1, 0, 0, 1, 0, 0, 0,
                             0, 0, 0, 0, 1, 0, 0, 0,
                             1, 0, 1, 0, 1, 0, 0, 0,
                             0, 0, 1, 0, 1, 0, 0, 0,
                             0, 0, 1, 0, 1, 0, 0, 0,
                             0, 0, 1, 0, 1, 0, 0, 0};

struct position
{
    int row, col;

    position down() const { return position{row - 1, col}; }

    position up() const { return position{row + 1, col}; }

    position left() const { return position{row, col - 1}; }

    position right() const { return position{row, col + 1}; }

    bool operator==(const position& other) const { return row == other.row && col == other.col; }

    bool operator!=(const position& other) const { return !(*this == other); }
};

bool isViable(const position& pos)
{
    return pos.row >= 0 &&
           pos.row < labSize &&
           pos.col >= 0 &&
           pos.col < labSize &&
           lab[pos.row][pos.col] == 0;
}

bool way(const position& current, const position& goal)
{
    if (!isViable(current))
    {
        return false;
    }

    if (current == goal)
    {
        return true;
    }

    lab[current.row][current.col] = -1;

    bool found = way(current.down(), goal);

    if (!found)
    {
        found = way(current.up(), goal);
    }

    if (!found)
    {
        found = way(current.right(), goal);
    }

    if (!found)
    {
        found = way(current.left(), goal);
    }

    lab[current.row][current.col] = 0;

    return found;
}

bool wayIter(position start, position goal)
{
    std::stack<position> stack;
    stack.push(start);
    while (!stack.empty() && stack.top() != goal)
    {
        position current = stack.top(); stack.pop();
        if(isViable(current))
        {
           lab[current.row][current.col] = -1;
           stack.push(current.down());
           stack.push(current.up());
           stack.push(current.right());
           stack.push(current.left());
        }
    }

    return !stack.empty();
}

int main()
{
    std::cout << way({0, 0}, {7, 7}) << std::endl;
    std::cout << wayIter({0, 0}, {7, 7}) << std::endl;

}
