#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &other) : _operands(other._operands)
{
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _operands = other._operands;
    return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(const std::string &token) const
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

void RPN::performOperation(const std::string &op)
{
    if (_operands.size() < 2)
        throw std::runtime_error("Error");

    int right = _operands.top();
    _operands.pop();
    int left = _operands.top();
    _operands.pop();

    if (op == "+")
        _operands.push(left + right);
    else if (op == "-")
        _operands.push(left - right);
    else if (op == "*")
        _operands.push(left * right);
    else if (op == "/")
    {
        if (right == 0)
            throw std::runtime_error("Error");
        _operands.push(left / right);
    }
}

void RPN::calculate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    try
    {
        while (iss >> token)
        {
            if (isOperator(token))
                performOperation(token);
            else
            {
                char *end;
                int value = std::strtol(token.c_str(), &end, 10);
                
                if (*end != '\0' || value >= 10 || value < 0)
                    throw std::runtime_error("Error");
                _operands.push(value);
            }
        }

        if (_operands.size() != 1)
            throw std::runtime_error("Error");
        
        std::cout << _operands.top() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}