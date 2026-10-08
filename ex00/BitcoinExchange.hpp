#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <cstdlib>

class BitcoinExchange
{
private:
    std::map<std::string, float> _database;

    bool isValidDate(const std::string &date) const;
    bool isValidValue(const std::string &valueStr, float &value) const;
    void loadDatabase(const std::string &dbFilename);

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void evaluateInput(const std::string &filename);
};

#endif