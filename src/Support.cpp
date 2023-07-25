#include "Support.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

sf::FloatRect InflateRect(const sf::FloatRect &source, float x, float y)
{
    sf::FloatRect target = source;
    target.left = source.left - x / 2;
    target.width = source.width + x;
    target.top = source.top - y / 2;
    target.height = source.height + y;
    return target;
}

sf::Vector2f GetRectCenter(const sf::FloatRect &rect)
{
    return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height / 2);
}

std::unique_ptr<sf::Texture> createTexture(uint16_t width, uint16_t height, sf::Color color)
{
    sf::Image image;
    image.create(sf::Vector2u(width, height), color);
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromImage(image))
    {
        throw std::runtime_error("Failed to create texture");
    }

    return texture;
}

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

std::unique_ptr<sf::Texture> importTexture(const std::string &filepath)
{
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filepath))
    {
        throw std::runtime_error("Failed to load texture: " + filepath);
    }
    return texture;
}

std::unique_ptr<Textures> importTexturesFromDirectoryRecursive(const fs::path &directoryPath)
{
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        fs::path relativePath = fs::relative(directoryPath);
        std::string errorMessage = "Invalid directory path or not a directory: " + relativePath.string();
        throw std::runtime_error(errorMessage);
    }

    auto textures = std::make_unique<Textures>();
    importTexturesFromDirectoryRecursiveImpl(textures, directoryPath);

    return textures;
}

void importTexturesFromDirectoryRecursiveImpl(std::unique_ptr<Textures> &texturesOut, const fs::path &directoryPath)
{
    for (const auto &entry : fs::directory_iterator(directoryPath))
    {
        const fs::path &entryPath = entry.path();

        if (fs::is_regular_file(entryPath))
        {
            sf::Texture texture;
            if (!texture.loadFromFile(entryPath.string()))
            {
                throw std::runtime_error("Failed to load texture: " + entryPath.string());
            }
            texturesOut->push_back(std::move(texture));
        }
        else if (fs::is_directory(entryPath))
        {
            importTexturesFromDirectoryRecursiveImpl(texturesOut, entryPath);
        }
    }
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