#pragma once

#include <memory>

// Core
#include "Core/Layer.h"

// Game
#include "Level.h"
#include "LevelView.h"
#include "UI.h"

class GamePlay : public Layer
{
public:
    GamePlay();
    void Update(const sf::Time &timestamp) override;
    void Draw(sf::RenderWindow &window) override;
    void OnWindowResize(sf::Vector2u size) override { mLevelView->OnWindowResize(size); }

private:
    std::unique_ptr<Level> mLevel;
    std::unique_ptr<LevelView> mLevelView;
    std::unique_ptr<UI> mUI;
};