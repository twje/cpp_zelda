#include "UI.h"
#include "Level.h"

// Core
#include "Core/ResourceManager/GUIStyleManager.h"

UI::UI(const Level &level)
    : mLevel(level)
{
    auto &manager = GUIStyleManager::GetInstance();

    mHealthBar = Bar(manager.GetResource("health_bar"), HEALTH_BAR_WIDTH, BAR_HEIGHT, 50, 100);
    mHealthBar.SetPosition(sf::Vector2f(10, 10));

    mEnergyBar = Bar(manager.GetResource("energy_bar"), ENERGY_BAR_WIDTH, BAR_HEIGHT, 48, 60);
    mEnergyBar.SetPosition(sf::Vector2f(10, 34));
}

void UI::Draw(sf::RenderWindow &window)
{
    mHealthBar.Draw(window);
    mEnergyBar.Draw(window);
}