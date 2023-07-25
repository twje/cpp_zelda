#pragma once

#include <SFML/Graphics.hpp>

#include "Rect.h"

void DrawDebugString(sf::RenderWindow &window, const std::string &info, uint16_t x = 10, uint16_t y = 10);

template <typename T>
void DrawTransparentRectangle(sf::RenderWindow &window, const sf::Rect<T> &source, sf::Color color, int thickness = 0)
{
    sf::RectangleShape target;
    target.setSize(sf::Vector2f(source.width, source.height));
    target.setPosition(sf::Vector2f(source.left, source.top));
    target.setFillColor(sf::Color::Transparent);
    target.setOutlineColor(color);
    target.setOutlineThickness(thickness);

    window.draw(target);
}