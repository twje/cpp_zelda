#include "Rect.h"

namespace Util
{
    FloatRect GetRect(sf::Vector2u size, sf::Vector2f position, RectCorner anchor)
    {
        return FloatRect(position.x, position.y, size.x, size.y);
    }
}