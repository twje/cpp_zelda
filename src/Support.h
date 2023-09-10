#pragma once

#include <string>
#include <memory>
#include <vector>
#include <filesystem>
#include <random>

#include "SFML/Graphics.hpp"

using CSVData = std::vector<std::vector<std::string>>;
using Textures = std::vector<sf::Texture>;

namespace fs = std::filesystem;

std::unique_ptr<CSVData> readCSV(const std::string &csvFilepath);

template <typename T>
const T &getRandomElement(const std::vector<T> &vec)
{    
    if (vec.empty())
    {
        throw std::runtime_error("Error: Vector is empty.");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, vec.size() - 1); 

    return vec[distribution(gen)];
}

int16_t GetRandomInt(int16_t start, int16_t end);

bool isSubstring(const std::string &source, const std::string &substring);

void replaceSubstring(std::string &source, const std::string &substringToReplace, const std::string &newSubstring);