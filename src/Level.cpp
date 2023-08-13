#include <map>
#include <random>
#include <filesystem>
#include <iostream>

// Core
#include "Core/ResourceManager/ResourceManagerUtils.h"
#include "Core/ResourceManager/TextureManager.h"

// Game
#include "Level.h"

namespace Factory
{
    std::shared_ptr<Player> LevelFriend::CreatePlayer(Level *level, float x, float y, const Group &obstacles)
    {
        using namespace std::placeholders;

        return std::make_shared<Player>(
            sf::Vector2f(x, y),
            obstacles,
            std::bind(&Level::CreateAttack, level),
            std::bind(&Level::CreateMagic, level, _1, _2, _3),
            std::bind(&Level::DestroyAttack, level));
    }

    static std::shared_ptr<Tile>
    CreateInvisibleTile(float x, float y)
    {
        return std::make_shared<Tile>(
            sf::Vector2f(x, y),
            SpriteType::INVISIBLE,
            TextureManager::GetInstance().GetResource("invisible_block"));
    }

    static std::shared_ptr<Tile> CreateGrassTile(const TextureMap &graphics, float x, float y)
    {
        return std::make_shared<Tile>(
            sf::Vector2f(x, y),
            SpriteType::GRASS,
            getRandomElement(graphics.at("grass")));
    }

    static std::shared_ptr<Tile> CreateObjectTile(const TextureMap &graphics, uint16_t objectID, float x, float y)
    {
        return std::make_shared<Tile>(
            sf::Vector2f(x, y),
            SpriteType::OBJECT,
            graphics.at("objects")[objectID]);
    }
}

Level::Level()
{
    CreateMap();
    mLevelView = std::make_unique<LevelView>(*this);
    mUI = std::make_unique<UI>(*this);
}

void Level::Update(const sf::Time &timestamp)
{
    mVisibleSpriteGroup.Update(timestamp);
    mUI->Update(timestamp);
}

void Level::Draw(sf::RenderWindow &window)
{
    mLevelView->Draw(window);
    mUI->Draw(window);
}

void Level::OnWindowResize(sf::Vector2u size)
{
    mLevelView->OnWindowResize(size);
    mUI->OnWindowResize(size);
}

void Level::CreateMap()
{
    auto &textureManager = TextureManager::GetInstance();

    // graphics
    TextureMap textureMap = GroupResourcesByPrefix(textureManager);
    mGraphics.emplace("grass", textureMap["grass"]);
    mGraphics.emplace("objects", textureMap["objects"]);

    mFloor = textureManager.GetResource("ground");
    mInvisibleBlock = textureManager.GetResource("invisible_block");

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
                    std::shared_ptr<Tile> tile = Factory::CreateInvisibleTile(x, y);
                    mObstacleSpriteGroup.Add(tile);
                }

                if (layoutPair.first == "grass")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateGrassTile(mGraphics, x, y);
                    mVisibleSpriteGroup.Add(tile);
                    mObstacleSpriteGroup.Add(tile);
                }

                if (layoutPair.first == "object")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateObjectTile(mGraphics, value, x, y);
                    mVisibleSpriteGroup.Add(tile);
                    mObstacleSpriteGroup.Add(tile);
                }
            }
        }
    }

    mPlayer = Factory::LevelFriend::CreatePlayer(this, 2000, 1430, mObstacleSpriteGroup);
    mVisibleSpriteGroup.Add(mPlayer);
}

void Level::CreateAttack()
{
    mCurrentAttack = std::make_shared<Weapon>(*mPlayer);
    mVisibleSpriteGroup.Add(mCurrentAttack);
}

void Level::CreateMagic(std::string style, uint16_t strength, uint16_t cost)
{
    std::cout << style << std::endl;
    std::cout << strength << std::endl;
    std::cout << cost << std::endl;
}

void Level::DestroyAttack()
{
    if (mCurrentAttack)
    {
        mCurrentAttack->Kill();
        mCurrentAttack.reset();
    }
}
