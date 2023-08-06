#include "Game.h"

#include <memory>

#include <SFML/Graphics.hpp>

// Core
#include "Core/FontManager.h"
#include "Core/TextureManager.h"
#include "Core/GUIStyleManager.h"

// Game
#include "GamePlay.h"
#include "Core/GuiStyle.h"

Game::Game()
    : Application(WIDTH, HEIGHT, BPP, CAPTION)
{
}

void Game::Setup()
{
    FontManager::Create("../config/fonts.cfg");
    TextureManager::Create("../config/textures.cfg");
    GUIStyleManager::Create("../config/styles.cfg");

    auto gamePlay = std::make_unique<GamePlay>(GetRenderWindow());
    PushLayer(std::move(gamePlay));
}
