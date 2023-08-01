#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/Layer.h"

// Game
#include "Level.h"

class UI : public Layer
{
public:
    UI(const Level &level)
        : mLevel(level)
    {
    }

    virtual void Draw(sf::RenderWindow &window)
    {
    }

private:
    void ShowBar() {}
    void ShowExperience() {}
    void SelectionBox() {}
    void WeaponOverlay() {}

private:
    const Level &mLevel;
};