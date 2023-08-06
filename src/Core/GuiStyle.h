#pragma once

#include <fstream>

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>

class GuiStyleSerializer;

class GuiStyle
{
    friend GuiStyleSerializer;

public:
    GuiStyle() {}

    GuiStyle(
        sf::Color backgroundCol,
        sf::Color backgroundHighlightCol,
        sf::Color foregroundCol,
        sf::Color foregroundHighlightCol,
        sf::Color bodyCol,
        sf::Color bodyHighlightCol,
        sf::Color borderCol,
        sf::Color borderHighlightCol,
        sf::Color textCol,
        sf::Color textHighlightCol,
        float borderSize);

    // Resource dependencies
    void InitFont(std::string resourceID);

    // Getters
    sf::Color GetBackgroundCol() const { return mBackgroundCol; }
    sf::Color GetBackgroundHighlightCol() const { return mBackgroundHighlightCol; }
    sf::Color GetForegroundCol() const { return mForegroundCol; }
    sf::Color GetForegroundHighlightCol() const { return mBackgroundHighlightCol; }
    sf::Color GetBodyCol() const { return mBodyCol; }
    sf::Color GetBodyHighlightCol() const { return mBodyHighlightCol; }
    sf::Color GetBorderCol() const { return mBorderCol; }
    sf::Color GetBorderHighlightCol() const { return mBorderHighlightCol; }
    sf::Color GetTextCol() const { return mTextCol; }
    sf::Color GetTextHighlightCol() const { return mTextHighlightCol; }
    sf::Font *GetFont() const {}
    float GetBorderSize() const { return mBorderSize; }

private:
    sf::Color mBackgroundCol{sf::Color::Black};
    sf::Color mBackgroundHighlightCol{sf::Color::Black};
    sf::Color mForegroundCol{sf::Color::Black};
    sf::Color mForegroundHighlightCol{sf::Color::Black};
    sf::Color mBodyCol{sf::Color::Black};
    sf::Color mBodyHighlightCol{sf::Color::Black};
    sf::Color mBorderCol{sf::Color::Black};
    sf::Color mBorderHighlightCol{sf::Color::Black};
    sf::Color mTextCol{sf::Color::Black};
    sf::Color mTextHighlightCol{sf::Color::Black};
    std::string mFontResourceID{""};
    std::shared_ptr<sf::Font> mFont;
    float mBorderSize{0};
};

// ----------
// Serializer
// ----------
namespace YAML
{
    template <>
    struct convert<sf::Color>
    {
        static bool decode(const Node &node, sf::Color &color);
    };
}

class GuiStyleSerializer
{
public:
    static void Serialize(const GuiStyle &style, const std::string &filePath);
    static void Deserialize(GuiStyle &styleOut, const std::string &filePath);
};