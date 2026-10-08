#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <string>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <iomanip>

class PmergeMe
{
private:
    std::vector<int> _vec;
    std::deque<int> _deq;

    void fordJohnsonVector(std::vector<int> &arr);
    void fordJohnsonDeque(std::deque<int> &arr);
    
    template<typename T>
    void printContainer(const T &container) const
    {
        typename T::const_iterator it;
        for (it = container.begin(); it != container.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    bool parseInput(int argc, char **argv);
    void execute();
};

#endif