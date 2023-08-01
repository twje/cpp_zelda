#include "Game.h"

#include <memory>

#include <SFML/Graphics.hpp>

// Game
#include "Settings.h"
#include "Level.h"
#include "LevelView.h"
#include "UI.h"

Game::Game()
    : Application(WIDTH, HEIGHT, BPP, CAPTION)
{
}

void Game::Setup()
{
    auto level = std::make_unique<Level>();
    auto levelView = std::make_unique<LevelView>(GetRenderWindow(), *level);
    auto ui = std::make_unique<UI>(*level);

    PushLayer(std::move(level));
    PushLayer(std::move(levelView));
    PushLayer(std::move(ui));
}
