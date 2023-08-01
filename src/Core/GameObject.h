#pragma once

#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual void Draw(sf::RenderWindow &window) {}
    virtual void Update(const sf::Time &timestamp){};
};