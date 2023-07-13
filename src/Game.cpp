#include "Game.h"
#include "Settings.h"

Game::Game()
    : mWindow(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT), BPP), CAPTION),
      mLevel(mWindow)
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
        mLevel.Run();
        mWindow.display();
    }
}