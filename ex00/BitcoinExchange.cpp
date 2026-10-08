#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    _database = other._database;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, float &value) const
{
    char *end;
    value = std::strtof(valueStr.c_str(), &end);
    
    if (*end != '\0' && *end != '\n' && *end != '\r')
        return false;
    if (value < 0.0f)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000.0f)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::loadDatabase(const std::string &dbFilename)
{
    std::ifstream file(dbFilename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open database file " << dbFilename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = line.substr(0, commaPos);
            float rate = std::strtof(line.substr(commaPos + 1).c_str(), NULL);
            _database[date] = rate;
        }
    }
}

void BitcoinExchange::evaluateInput(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, pipePos - 1);
        std::string valueStr = line.substr(pipePos + 2);
        
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        float value;
        if (!isValidValue(valueStr, value))
            continue;

        std::map<std::string, float>::iterator it = _database.lower_bound(date);
        
        if (it != _database.begin() && (it == _database.end() || it->first != date))
            --it;

        if (it != _database.end())
            std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
}