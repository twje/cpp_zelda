#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{
    enum class RectCorner
    {
        TOP_LEFT
    };

    sf::FloatRect GetRect(sf::Vector2u size, sf::Vector2f position, RectCorner anchor);
}
