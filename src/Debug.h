#pragma once

#include <SFML/Graphics.hpp>
#include "Rect.h"

void Debug(sf::RenderWindow &window, const std::string &info, uint16_t x = 10, uint16_t y = 10);

template <typename T>
void DrawTransparentRectangle(sf::RenderWindow &window, const Util::Rect<T> &source, sf::Color color, int thickness = 0)
{
    sf::RectangleShape target;
    target.setSize(sf::Vector2f(source.GetWidth(), source.GetHeight()));
    target.setPosition(sf::Vector2f(source.GetX(), source.GetY()));
    target.setFillColor(sf::Color::Transparent);
    target.setOutlineColor(color);
    target.setOutlineThickness(thickness);

    window.draw(target);
}