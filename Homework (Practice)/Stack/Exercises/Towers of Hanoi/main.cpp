#include <iostream>
#include <stack>

struct HanoiData
{
    int k;
    char source, temp, dest;
};

void hanoi(int k, char source, char temp, char dest)
{
    if (k == 1)
    {
        std::cout << "Put disk from " << source << " to " << dest << std::endl;
        return;
    }

    hanoi(k - 1, source, dest, temp);
    hanoi(1, source, temp, dest);
    hanoi(k - 1, temp, source, dest);
}

void hanoiIter(int k, char source, char temp, char dest)
{
    std::stack<HanoiData> stack;
    stack.push(HanoiData{k, source, temp, dest});

    while (!stack.empty())
    {
        HanoiData current = stack.top();
        stack.pop();
        if (current.k == 1)
        {
            std::cout << "Put disk from " << current.source << " to " << current.dest << std::endl;
        }
        else
        {
            stack.push(HanoiData{current.k - 1, current.temp, current.source, current.dest});
            stack.push(HanoiData{1, current.source, current.temp, current.dest});
            stack.push(HanoiData{current.k - 1, current.source, current.dest, current.temp});
        }
    }
}

int main()
{
    hanoi(3, 'A', 'B', 'C');
    std::cout << std::endl;
    hanoiIter(3, 'A', 'B', 'C');
    return 0;
}
