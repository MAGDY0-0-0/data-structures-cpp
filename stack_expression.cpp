// ============================================================
//  stack_expression.cpp
//  Demonstrates TWO classic stack algorithms:
//    1. Infix -> Postfix  (Shunting-Yard algorithm)
//    2. Postfix Evaluation
//
//  Supports: multi-digit numbers, + - * / ^ ( )
//  Right-associativity of ^ is handled correctly.
// ============================================================

#include <cmath>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

int getPrecedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

string infixToPostfix(const string &infix)
{
    stack<char> opStack;
    string postfix;

    for (int i = 0; i < static_cast<int>(infix.size()); ++i)
    {
        char ch = infix[i];
        if (ch == ' ')
            continue;

        if (isdigit(ch))
        {
            string num;
            while (i < static_cast<int>(infix.size()) && isdigit(infix[i]))
            {
                num += infix[i];
                ++i;
            }
            --i;
            postfix += num + ' ';
        }
        else if (ch == '(')
        {
            opStack.push(ch);
        }
        else if (ch == ')')
        {
            while (!opStack.empty() && opStack.top() != '(')
            {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            if (!opStack.empty())
                opStack.pop();
        }
        else
        {
            while (!opStack.empty() &&
                   opStack.top() != '(' &&
                   (getPrecedence(opStack.top()) > getPrecedence(ch) ||
                    (getPrecedence(opStack.top()) == getPrecedence(ch) && ch != '^')))
            {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(ch);
        }
    }

    while (!opStack.empty())
    {
        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
    }

    if (!postfix.empty() && postfix.back() == ' ')
        postfix.pop_back();

    return postfix;
}

int evaluatePostfix(const string &postfix)
{
    stack<int> valStack;
    istringstream tokens(postfix);
    string token;

    while (tokens >> token)
    {
        if (isdigit(token[0]))
        {
            valStack.push(stoi(token));
        }
        else
        {
            int operand1 = valStack.top();
            valStack.pop();
            int operand2 = valStack.top();
            valStack.pop();

            int result = 0;
            switch (token[0])
            {
            case '+':
                result = operand2 + operand1;
                break;
            case '-':
                result = operand2 - operand1;
                break;
            case '*':
                result = operand2 * operand1;
                break;
            case '/':
                result = operand2 / operand1;
                break;
            case '^':
                result = static_cast<int>(pow(static_cast<double>(operand2), static_cast<double>(operand1)));
                break;
            default:
                break;
            }

            valStack.push(result);
        }
    }

    return valStack.top();
}

int main()
{
    const string expressions[] = {
        "3+4*5-2",
        "(300+20/5)*(43-21)",
        "2^3^2"};

    const string expectedPostfix[] = {
        "3 4 5 * + 2 -",
        "300 20 5 / + 43 21 - *",
        "2 3 2 ^ ^"};

    const int expectedResults[] = {21, 6688, 512};

    const int caseCount = static_cast<int>(sizeof(expressions) / sizeof(expressions[0]));

    for (int i = 0; i < caseCount; ++i)
    {
        string infix = expressions[i];
        string postfix = infixToPostfix(infix);
        int result = evaluatePostfix(postfix);

        cout << "Infix:     " << infix << "\n";
        cout << "Postfix:   " << postfix << "\n";
        cout << "Expected:  " << expectedPostfix[i] << "\n";
        cout << "Result:    " << result << "\n";
        cout << "Expected result: " << expectedResults[i] << "\n";
        cout << "----------------------------------------\n";
    }

    return 0;
}
