#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <list>
# include <sstream>
# include <cstdlib>

class RPN
{
private:
    std::stack<int, std::list<int> > _operands;

    bool isOperator(const std::string &token) const;
    void performOperation(const std::string &op);

public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();

    void calculate(const std::string &expression);
};

#endif