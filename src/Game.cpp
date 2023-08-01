#include <iostream>

// Game
#include "Game.h"
#include "Settings.h"
#include "UI.h"

Game::Game()
    : mWindow(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT), BPP), CAPTION),
      mLevel(),
      mLevelView(mWindow, mLevel, mUI)
{
    mWindow.setFramerateLimit(FPS);
}

void Game::Run()
{
    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }

        mWindow.clear();
        mLevel.Update(mClock.restart());
        mLevelView.Draw(mWindow);
        mWindow.display();
    }
}