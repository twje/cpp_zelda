#pragma once

#include "Settings.h"
#include "SpriteGroup.h"
#include "Tile.h"
#include "Player.h"

// Forward declare classes
namespace sf
{
    class RenderWindow;
}

class Level
{
public:
    Level(sf::RenderWindow &window)
        : mWindow(window)
    {
        CreateMap();
    }

    void Run()
    {
        mVisibleSprites.Draw(mWindow);
    }

private:
    void CreateMap()
    {
        for (size_t y = 0; y < ROWS; y++)
        {
            for (size_t x = 0; x < COLS; x++)
            {
                size_t xTile = x * TILESIZE;
                size_t yTile = y * TILESIZE;

                size_t index = x + (y * COLS);
                if (WORLD_MAP[index] == 'x')
                {
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(xTile, yTile));
                    mVisibleSprites.Add(tile);
                    mObstacleSprites.Add(tile);
                }

                if (WORLD_MAP[index] == 'p')
                {
                    std::shared_ptr<Player> tile = std::make_shared<Player>(sf::Vector2f(xTile, yTile));
                    mVisibleSprites.Add(tile);
                }
            }
        }
    }

private:
    sf::RenderWindow &mWindow;
    SpriteGroup mVisibleSprites;
    SpriteGroup mObstacleSprites;
};