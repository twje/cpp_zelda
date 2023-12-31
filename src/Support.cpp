#include "Support.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

std::unique_ptr<CSVData> readCSV(const std::string &csvFilepath)
{
    std::ifstream file(csvFilepath);
    if (!file)
    {
        throw std::runtime_error("Failed to open the file.");
    }

    std::unique_ptr<CSVData> data = std::make_unique<CSVData>();

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> row;

        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ','))
        {
            row.push_back(value);
        }

        data->push_back(std::move(row));
    }

    return std::move(data);
}

int16_t GetRandomInt(int16_t start, int16_t end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(start, end);
    return distribution(gen);
}

bool isSubstring(const std::string &source, const std::string &substring)
{
    size_t foundPos = source.find(substring);
    return foundPos != std::string::npos;
}

void replaceSubstring(std::string &source, const std::string &substringToReplace, const std::string &newSubstring)
{
    size_t pos = source.find(substringToReplace);
    while (pos != std::string::npos)
    {
        source.replace(pos, substringToReplace.length(), newSubstring);
        pos = source.find(substringToReplace, pos + newSubstring.length());
    }
}