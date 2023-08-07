#pragma once

#include <SFML/Graphics.hpp>

class Layer
{
public:
    virtual void Update(const sf::Time &timestamp) {}
    virtual void Draw(sf::RenderWindow &window) {}
    virtual void OnWindowResize(sf::Vector2u size) {}
};