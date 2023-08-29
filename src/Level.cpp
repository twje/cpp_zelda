#include <map>
#include <random>
#include <filesystem>
#include <iostream>

// Core
#include "Core/ResourceManager/ResourceManagerUtils.h"
#include "Core/ResourceManager/TextureManager.h"

// Game
#include "Level.h"
#include "Enemy.h"
#include "Components.h"

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

    std::shared_ptr<Enemy> LevelFriend::CreateEnemy(Level *level, std::string name, float x, float y, const Group &obstacles)
    {
        using namespace std::placeholders;

        return std::make_shared<Enemy>(
            name,
            sf::Vector2f(x, y),
            obstacles,
            std::bind(&Level::DemagePlayer, level, _1, _2));
    }

    static std::shared_ptr<Tile> CreateInvisibleTile(float x, float y)
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
    mVisibleGroup.Update(timestamp);
    mUI->Update(timestamp);
    UpdateEnemies(timestamp);
    HandlePlayerAttack();
}

void Level::UpdateEnemies(const sf::Time &timestamp)
{
    for (auto &gameObject : mEnemies.GetGameObjects())
    {
        auto enemy = std::static_pointer_cast<Enemy>(gameObject);
        enemy->EnemyUpdate(*mPlayer);
    }
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
    layouts.emplace("entities", readCSV("../map/map_Entities.csv"));

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
                    mObstacleGroup.Add(tile);
                }

                if (layoutPair.first == "grass")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateGrassTile(mGraphics, x, y);
                    mVisibleGroup.Add(tile);
                    mObstacleGroup.Add(tile);
                    mAttackableGroup.Add(tile);
                }

                if (layoutPair.first == "object")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateObjectTile(mGraphics, value, x, y);
                    mVisibleGroup.Add(tile);
                    mObstacleGroup.Add(tile);
                }

                if (layoutPair.first == "entities")
                {
                    if (value == 394)
                    {
                        mPlayer = Factory::LevelFriend::CreatePlayer(this, x, y, mObstacleGroup);
                        mVisibleGroup.Add(mPlayer);
                    }
                    else
                    {
                        std::string name = "squid";
                        switch (value)
                        {
                        case 390:
                            name = "bamboo";
                            break;
                        case 391:
                            name = "spirit";
                            break;
                        case 392:
                            name = "raccoon";
                            break;
                        }
                        auto enemy = Factory::LevelFriend::CreateEnemy(this, name, x, y, mObstacleGroup);
                        mVisibleGroup.Add(enemy);
                        mEnemies.Add(enemy);
                        mAttackableGroup.Add(enemy);
                    }
                }
            }
        }
    }
}

void Level::CreateAttack()
{
    mCurrentAttack = std::make_shared<Weapon>(*mPlayer);
    mVisibleGroup.Add(mCurrentAttack);
    mAttackGroup.Add(mCurrentAttack);
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

void Level::HandlePlayerAttack()
{
    std::vector<GameObject *> killed;

    // Detect killed sprites
    for (auto &attacker : mAttackGroup)
    {
        for (auto &attacked : mAttackableGroup)
        {
            if (!attacker->CollidesWith(*attacked))
            {
                continue;
            }

            if (auto attackableComponent = attacked->GetComponent<AttackableComponent>())
            {
                attackableComponent->InflictDemage(*mPlayer, *attacker);
                if (attackableComponent->IsDead())
                {
                    killed.emplace_back(attacked.get());
                }
            }
        }
    }

    // Kill sprites
    for (GameObject *attacked : killed)
    {
        attacked->Kill();
    }
}

void Level::DemagePlayer(uint16_t amount, std::string attackType)
{
    if (mPlayer->IsVulnerable())
    {
        mPlayer->TakeDemage(amount);
        mPlayer->BecomeTemporarilyInvulnerable();
    }
}