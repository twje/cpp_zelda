#pragma once

#include "SFML/Graphics.hpp"

sf::FloatRect InflateRect(const sf::FloatRect &source, float x, float y, bool isFullInflate = false);
sf::Vector2f GetRectCenter(const sf::FloatRect &rect);
sf::Vector2f GetRectMidRight(const sf::FloatRect &rect);
sf::Vector2f GetRectMidLeft(const sf::FloatRect &rect);
sf::Vector2f GetRectMidTop(const sf::FloatRect &rect);
sf::Vector2f GetRectMidBottom(const sf::FloatRect &rect);