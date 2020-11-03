#include <iostream>
#include <stack>


bool areBracketsMatching(const std::string& str)
{
    std::stack<char> brackets;
    for(char c : str)
    {
        if(c == '(')
        {
            brackets.push(c);
        }
        else if(c == ')')
        {
            if(brackets.empty())
            {
                return false;
            }

            brackets.pop();
        }
    }

    return brackets.empty();
}

int main()
{


    std::string valid = "(x+(y+(1+2)))";
    std::string inValid = "(x+y)*3)+(x+(1+2)";
    std::cout<<areBracketsMatching(valid) << std::endl;
    std::cout<<areBracketsMatching(inValid);

}
