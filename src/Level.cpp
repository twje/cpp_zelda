#include <map>
#include <random>
#include <filesystem>
#include <iostream>

// Core
#include "Core/TextureManager.h"

// Game
#include "Level.h"

Level::Level()
{
    CreateMap();
}

void Level::Update(const sf::Time &timestamp)
{
    mVisibleSpriteGroup.Update(timestamp);
}

void Level::CreateMap()
{
    auto &textureManager = TextureManager::GetInstance();

    // graphics
    textureManager.LoadTexture("ground", "../graphics/tilemap/ground.png");
    textureManager.LoadTextures("grass", "../graphics/Grass");
    textureManager.LoadTextures("objects", "../graphics/objects");

    mGraphics.emplace("grass", textureManager.GetTextures("grass"));
    mGraphics.emplace("objects", textureManager.GetTextures("objects"));

    mFloor = textureManager.GetTexture("ground");
    mInvisibleBlock = createTexture(TILESIZE, TILESIZE, sf::Color(0, 0, 0, 0));

    for (const auto &weaponData : WEAPON_DATA)
    {
        textureManager.LoadTextures(TextureIDGeneratorPresets::ExtractLastDirectoryWithFilename, weaponData.second.mGraphics);
    }

    for (const auto &playerData : PLAYER_DATA)
    {
        textureManager.LoadTextures(playerData.first, playerData.second.mGraphics);
    }

    // layouts
    std::map<std::string, std::unique_ptr<CSVData>> layouts;
    layouts.emplace("boundary", readCSV("../map/map_FloorBlocks.csv"));
    layouts.emplace("grass", readCSV("../map/map_Grass.csv"));
    layouts.emplace("object", readCSV("../map/map_Objects.csv"));

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
                    mObstacleSpriteGroup.Add(tile);
                }

                if (layoutPair.first == "grass")
                {
                    TexturePtr &texture = getRandomElement(mGraphics["grass"]);
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(x, y), SpriteType::GRASS, *texture);
                    mVisibleSpriteGroup.Add(tile);
                    mObstacleSpriteGroup.Add(tile);
                }

                if (layoutPair.first == "object")
                {
                    TexturePtr &texture = mGraphics["objects"].at(value);
                    std::shared_ptr<Tile> tile = std::make_shared<Tile>(sf::Vector2f(x, y), SpriteType::OBJECT, *texture);
                    mVisibleSpriteGroup.Add(tile);
                    mObstacleSpriteGroup.Add(tile);
                }
            }
        }
    }

    mPlayer = std::make_shared<Player>(sf::Vector2f(2000, 1430), mObstacleSpriteGroup, std::bind(&Level::CreateAttack, this), std::bind(&Level::DestroyAttack, this));
    mVisibleSpriteGroup.Add(mPlayer);
}

void Level::CreateAttack()
{
    mCurrentAttack = std::make_shared<Weapon>(*mPlayer);
    mVisibleSpriteGroup.Add(mCurrentAttack);
}

void Level::DestroyAttack()
{
    if (mCurrentAttack)
    {
        mCurrentAttack->Kill();
        mCurrentAttack.reset();
    }
}
