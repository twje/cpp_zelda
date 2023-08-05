#include "Game.h"

#include <memory>

#include <SFML/Graphics.hpp>

// Core
#include "Core/TextureManager.h"

// Game
#include "GamePlay.h"

Game::Game()
    : Application(WIDTH, HEIGHT, BPP, CAPTION)
{
}

void Game::Setup()
{
    TextureManager::Create("../config/textures.cfg");

    auto gamePlay = std::make_unique<GamePlay>(GetRenderWindow());
    PushLayer(std::move(gamePlay));
}
