#pragma once

// Core
#include "Core/Layer.h"

// Forward declarations
class Level;

class UI : public Layer
{
public:
    UI(const Level &level);

    virtual void Draw(sf::RenderWindow &window);

private:
    void ShowBar() {}
    void ShowExperience() {}
    void SelectionBox() {}
    void WeaponOverlay() {}

private:
    const Level &mLevel;
};