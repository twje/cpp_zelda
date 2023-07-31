#include "Core/RectUtils.h"

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

sf::Vector2f GetRectMidRight(const sf::FloatRect &rect)
{
    return sf::Vector2f(rect.left + rect.width, rect.top + rect.height / 2);
}

sf::Vector2f GetRectMidLeft(const sf::FloatRect &rect)
{
    return sf::Vector2f(rect.left, rect.top + rect.height / 2);
}

sf::Vector2f GetRectMidTop(const sf::FloatRect &rect)
{
    return sf::Vector2f(rect.left + rect.width / 2, rect.top);
}

sf::Vector2f GetRectMidBottom(const sf::FloatRect &rect)
{
    return sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);
}