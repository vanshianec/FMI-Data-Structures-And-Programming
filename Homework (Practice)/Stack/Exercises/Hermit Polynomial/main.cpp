#include <iostream>
#include <stack>

struct HermitValues
{
    int n;
    double multiplier;
};

double hermit(int n, double x)
{
    if (n == 0)
    {
        return 1;
    }

    if (n == 1)
    {
        return 2 * x;
    }

    return 2 * x * hermit(n - 1, x) + 2 * (n - 1) * hermit(n - 2, x);
}

double hermitIterative(int n, double x)
{
    std::stack<HermitValues> stack;
    stack.push(HermitValues{n, 1});
    double totalSum = 0;

    while (!stack.empty())
    {
        HermitValues current = stack.top();
        stack.pop();

        if (current.n == 0)
        {
            totalSum += 1 * current.multiplier;
        }
        else if (current.n == 1)
        {
            totalSum += 2 * x * current.multiplier;
        }
        else
        {
            stack.push(HermitValues{current.n - 2, 2 * (current.n - 1) * current.multiplier});
            stack.push(HermitValues{current.n - 1, 2 * x * current.multiplier});
        }
    }

    return totalSum;
}

int main()
{
    double x = 3;
    int n = 7;
    std::cout << hermit(n, x) << std::endl;
    std::cout << hermitIterative(n, x) << std::endl;


}
