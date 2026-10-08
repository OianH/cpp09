#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    PmergeMe sorter;
    
    if (!sorter.parseInput(argc, argv))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    sorter.execute();

    return 0;
}