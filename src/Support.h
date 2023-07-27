#pragma once

#include <string>
#include <memory>
#include <vector>
#include <filesystem>

#include "SFML/Graphics.hpp"

sf::FloatRect InflateRect(const sf::FloatRect &source, float x, float y);

sf::Vector2f GetRectCenter(const sf::FloatRect &rect);

using CSVData = std::vector<std::vector<std::string>>;
using Textures = std::vector<sf::Texture>;

namespace fs = std::filesystem;

std::unique_ptr<sf::Texture> createTexture(uint16_t width, uint16_t height, sf::Color color);

std::unique_ptr<CSVData> readCSV(const std::string &csvFilepath);

template <typename T>
T &getRandomElement(std::vector<T> &vec)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (vec.empty())
    {
        throw std::runtime_error("Error: Vector is empty.");
    }

    std::size_t randomIndex = std::rand() % vec.size();

    return vec[randomIndex];
}

bool isSubstring(const std::string &source, const std::string &substring);

void replaceSubstring(std::string &source, const std::string &substringToReplace, const std::string &newSubstring);