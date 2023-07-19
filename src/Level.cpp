#include "Level.h"

void Level::CreateMap()
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
                mPlayer = std::make_shared<Player>(sf::Vector2f(xTile, yTile), mObstacleSprites);
                mVisibleSprites.Add(mPlayer);
            }
        }
    }
}