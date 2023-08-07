#include "Game.h"

#include <memory>

#include <SFML/Graphics.hpp>

// Core
#include "Core/ResourceManager/FontManager.h"
#include "Core/ResourceManager/TextureManager.h"
#include "Core/ResourceManager/GUIStyleManager.h"

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

    auto gamePlay = std::make_unique<GamePlay>();
    PushLayer(std::move(gamePlay));
}
