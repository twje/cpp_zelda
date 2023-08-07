
#include "GamePlay.h"

GamePlay::GamePlay()
{
    mLevel = std::make_unique<Level>();
    mLevelView = std::make_unique<LevelView>(*mLevel);
    mUI = std::make_unique<UI>(*mLevel);
}

void GamePlay::Update(const sf::Time &timestamp)
{
    mLevel->Update(timestamp);
}

void GamePlay::Draw(sf::RenderWindow &window)
{
    mLevelView->Draw(window);
    mUI->Draw(window);
}