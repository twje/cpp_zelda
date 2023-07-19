#include "Debug.h"

void DrawDebugString(sf::RenderWindow &window, const std::string &info, uint16_t x, uint16_t y)
{
    sf::Font font;
    if (!font.loadFromFile("../graphics/font/joystix.ttf"))
    {
        // Error handling for font loading
        return;
    }

    // Text
    sf::Text text(font, info);
    text.setCharacterSize(24);
    text.setPosition(sf::Vector2f(x, y));

    // Text Background
    sf::FloatRect textBounds = text.getGlobalBounds();
    sf::RectangleShape background(sf::Vector2f(textBounds.width, textBounds.height));
    background.setPosition(sf::Vector2f(textBounds.left, textBounds.top));
    background.setFillColor(sf::Color::Black);

    window.draw(background);
    window.draw(text);
}