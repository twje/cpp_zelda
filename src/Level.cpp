#include <map>
#include <random>

// Game
#include "Level.h"

Level::Level()
{
    CreateMap();
}

void Level::Update()
{
    mVisibleSprites.Update();
}

void Level::CreateMap()
{
    mFloor = importTexture("../graphics/tilemap/ground.png");
    mInvisibleBlock = createTexture(TILESIZE, TILESIZE, sf::Color(255, 0, 0, 255));

    createTexture(TILESIZE, TILESIZE, sf::Color(100, 0, 0, 255));

    // layouts
    std::map<std::string, std::unique_ptr<CSVData>> layouts;
    layouts.emplace("boundary", readCSV("../map/map_FloorBlocks.csv"));
    layouts.emplace("grass", readCSV("../map/map_Grass.csv"));
    layouts.emplace("object", readCSV("../map/map_Objects.csv"));

    // graphics
    mGraphics.emplace("grass", importTexturesFromDirectoryRecursive("../graphics/Grass"));
    mGraphics.emplace("objects", importTexturesFromDirectoryRecursive("../graphics/objects"));

    for (const auto &layoutPair : layouts)
    {
        for (size_t rowIndex = 0; rowIndex < layoutPair.second->size(); rowIndex++)
        {
            const std::vector<std::string> &row = layoutPair.second->at(rowIndex);

            for (size_t colIndex = 0; colIndex < row.size(); colIndex++)
            {
                std::string col = row[colIndex];
                if (col == "-1")
                {
                    continue;
                }
                size_t value = std::stoul(col);

                float x = colIndex * TILESIZE;
                float y = rowIndex * TILESIZE;

                if (layoutPair.first == "boundary")
                {
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(x, y), SpriteType::INVISIBLE, *mInvisibleBlock);
                    mVisibleSprites.Add(tile);
                }

                if (layoutPair.first == "grass")
                {
                    sf::Texture &texture = getRandomElement<sf::Texture>(*mGraphics["grass"]);
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(x, y), SpriteType::GRASS, texture);
                    mVisibleSprites.Add(tile);
                    mObstacleSprites.Add(tile);
                }

                if (layoutPair.first == "object")
                {
                    sf::Texture &texture = mGraphics["objects"]->at(value);
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(x, y), SpriteType::OBJECT, texture);
                    mVisibleSprites.Add(tile);
                    mObstacleSprites.Add(tile);
                }
            }
        }
    }

    mPlayer = std::make_shared<Player>(sf::Vector2f(2000, 1430), mObstacleSprites);
    mVisibleSprites.Add(mPlayer);
}