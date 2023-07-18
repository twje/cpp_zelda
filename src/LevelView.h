#pragma once

#include <SFML/Graphics.hpp>

// Forward declarations
class Level;

class LevelView
{
public:
    LevelView(const Level &view);

    void Draw(sf::RenderWindow &window);

private:
    const Level &mLevel;
};
