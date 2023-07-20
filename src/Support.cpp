#include "Support.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

std::unique_ptr<CSVData> readCSV(const std::string &foo)
{
    std::ifstream file("../map/map_FloorBlocks.csv");
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

void foo(const std::string &csvFilePath)
{
}