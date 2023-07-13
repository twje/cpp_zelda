#include "Rect.h"

namespace Util
{
    sf::FloatRect GetRect(sf::Vector2u size, sf::Vector2f position, RectCorner anchor)
    {
        sf::FloatRect rect(position, sf::Vector2f(size.x, size.y));
        return rect;
    }
}