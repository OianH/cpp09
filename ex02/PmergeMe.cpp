#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

bool PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string token = argv[i];
        if (token.empty() || token.find_first_not_of("0123456789") != std::string::npos)
            return false;
        int num = std::atoi(token.c_str());
        if (num < 0)
            return false;
        _vec.push_back(num);
        _deq.push_back(num);
    }
    return true;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &arr)
{
    if (arr.size() < 2)
        return;

    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> mainChain;

    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        mainChain.push_back(pairs.back().first);
    }

    fordJohnsonVector(mainChain);

    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == mainChain[i])
            {
                pend.push_back(pairs[j].second);
                pairs[j].first = -1;
                break;
            }
        }
    }

    std::vector<int> result;
    result.push_back(pend[0]);
    result.push_back(mainChain[0]);

    for (size_t i = 1; i < mainChain.size(); ++i)
        result.push_back(mainChain[i]);

    size_t pendSize = pend.size();
    size_t last_jacob = 1;
    size_t next_jacob = 3;

    while (last_jacob < pendSize)
    {
        size_t max_idx = next_jacob;
        if (max_idx > pendSize)
            max_idx = pendSize;

        for (size_t i = max_idx; i > last_jacob; --i)
        {
            int valToInsert = pend[i - 1];
            std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), valToInsert);
            result.insert(it, valToInsert);
        }
        
        size_t tmp = next_jacob;
        next_jacob = next_jacob + 2 * last_jacob;
        last_jacob = tmp;
    }

    if (hasStraggler)
    {
        std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), straggler);
        result.insert(it, straggler);
    }

    arr = result;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &arr)
{
    if (arr.size() < 2)
        return;

    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;

    if (hasStraggler)
    {
        straggler = arr.back();
        arr.pop_back();
    }

    std::deque<std::pair<int, int> > pairs;
    std::deque<int> mainChain;

    for (size_t i = 0; i < arr.size(); i += 2)
    {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        mainChain.push_back(pairs.back().first);
    }

    fordJohnsonDeque(mainChain);

    std::deque<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == mainChain[i])
            {
                pend.push_back(pairs[j].second);
                pairs[j].first = -1;
                break;
            }
        }
    }

    std::deque<int> result;
    result.push_back(pend[0]);
    result.push_back(mainChain[0]);

    for (size_t i = 1; i < mainChain.size(); ++i)
        result.push_back(mainChain[i]);

    size_t pendSize = pend.size();
    size_t last_jacob = 1;
    size_t next_jacob = 3;

    while (last_jacob < pendSize)
    {
        size_t max_idx = next_jacob;
        if (max_idx > pendSize)
            max_idx = pendSize;

        for (size_t i = max_idx; i > last_jacob; --i)
        {
            int valToInsert = pend[i - 1];
            std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), valToInsert);
            result.insert(it, valToInsert);
        }
        
        size_t tmp = next_jacob;
        next_jacob = next_jacob + 2 * last_jacob;
        last_jacob = tmp;
    }

    if (hasStraggler)
    {
        std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), straggler);
        result.insert(it, straggler);
    }

    arr = result;
}

void PmergeMe::execute()
{
    std::cout << "Before: ";
    printContainer(_vec);

    clock_t startVec = clock();
    fordJohnsonVector(_vec);
    clock_t endVec = clock();

    clock_t startDeq = clock();
    fordJohnsonDeque(_deq);
    clock_t endDeq = clock();

    std::cout << "After: ";
    printContainer(_vec);

    double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << timeDeq << " us" << std::endl;
}