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

namespace Factory
{
    static std::shared_ptr<Player> CreatePlayer(GroupManager& groupManager, Level& level, float x, float y, const Group &obstacles)
    {        
        return std::make_shared<Player>(groupManager, sf::Vector2f(x, y), obstacles, level);
    }

    static std::shared_ptr<Enemy> CreateEnemy(GroupManager& groupManager, Level& level, std::string name, float x, float y, const Group &obstacles)
    {        
        return std::make_shared<Enemy>(groupManager, name, sf::Vector2f(x, y), obstacles, level);
    }

    static std::shared_ptr<Tile> CreateInvisibleTile(GroupManager& groupManager, float x, float y)
    {
        return std::make_shared<Tile>(
            groupManager,
            sf::Vector2f(x, y),
            SpriteType::INVISIBLE,
            TextureManager::GetInstance().GetResource("invisible_block"));
    }

    static std::shared_ptr<Tile> CreateGrassTile(GroupManager& groupManager, const TextureMap &graphics, float x, float y)
    {
        return std::make_shared<Tile>(
            groupManager,
            sf::Vector2f(x, y),
            SpriteType::GRASS,
            getRandomElement(graphics.at("grass")));
    }

    static std::shared_ptr<Tile> CreateObjectTile(GroupManager& groupManager, const TextureMap &graphics, uint16_t objectID, float x, float y)
    {
        return std::make_shared<Tile>(
            groupManager,
            sf::Vector2f(x, y),
            SpriteType::OBJECT,
            graphics.at("objects")[objectID]);
    }
}

Level::Level()
{
    mGroupManager.TrackGroup(mEnemies);
    mGroupManager.TrackGroup(mVisibleGroup);
    mGroupManager.TrackGroup(mObstacleGroup);
    mGroupManager.TrackGroup(mAttackableGroup);
    mGroupManager.TrackGroup(mAttackGroup);

    CreateMap();
    mLevelView = std::make_unique<LevelView>(*this);
    mUI = std::make_unique<UI>(mGroupManager, *this);
}

void Level::Update(const sf::Time &timestamp)
{
    mVisibleGroup.Update(timestamp);
    mUI->Update(timestamp);
    UpdateEnemies(timestamp);
    HandlePlayerAttack();
    mGroupManager.CleanupDeadObjects();
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
    layouts.emplace("boundary", readCSV("../../map/map_FloorBlocks.csv"));
    layouts.emplace("grass", readCSV("../../map/map_Grass.csv"));
    layouts.emplace("object", readCSV("../../map/map_Objects.csv"));
    layouts.emplace("entities", readCSV("../../map/map_Entities.csv"));

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
                    std::shared_ptr<Tile> tile = Factory::CreateInvisibleTile(mGroupManager, x, y);
                    mObstacleGroup.Add(tile);
                }

                if (layoutPair.first == "grass")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateGrassTile(mGroupManager, mGraphics, x, y);
                    mVisibleGroup.Add(tile);
                    mObstacleGroup.Add(tile);
                    mAttackableGroup.Add(tile);
                }

                if (layoutPair.first == "object")
                {
                    std::shared_ptr<Tile> tile = Factory::CreateObjectTile(mGroupManager, mGraphics, value, x, y);
                    mVisibleGroup.Add(tile);
                    mObstacleGroup.Add(tile);
                }

                if (layoutPair.first == "entities")
                {
                    if (value == 394)
                    {
                        mPlayer = Factory::CreatePlayer(mGroupManager , *this, x, y, mObstacleGroup);
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
                        auto enemy = Factory::CreateEnemy(mGroupManager , *this, name, x, y, mObstacleGroup);
                        mVisibleGroup.Add(enemy);
                        mEnemies.Add(enemy);
                        mAttackableGroup.Add(enemy);
                    }
                }
            }
        }
    }
}

void Level::HandlePlayerAttack()
{        
    class InflictDemage : public EntityVisitor
    {
    public:
        InflictDemage(Player& player)
            : mPlayer(player)
        {}

        virtual void Visit(Tile& tile) override
        {
            tile.Kill();
        }
        
        virtual void Visit(Enemy& enemy) override
        {
            enemy.InflictDemage(mPlayer, mPlayer.GetFullWeaponDamage());
            if (enemy.GetHealth() <= 0)
            {
                enemy.Kill();
            }
        }

    private:
        Player& mPlayer;
    };

    for (auto& attacker : mAttackGroup)
    {
        for (auto& attacked : mAttackableGroup)
        {
            if (!attacker->CollidesWith(*attacked))
            {
                continue;
            }           

            auto entity = std::dynamic_pointer_cast<EntityBase>(attacked);
            entity->Accept(InflictDemage(*mPlayer));
        }
    }    
}

void Level::CreateAttack()
{
    mCurrentAttack = std::make_shared<Weapon>(mGroupManager, *mPlayer);
    mVisibleGroup.Add(mCurrentAttack);
    mAttackGroup.Add(mCurrentAttack);
}

void Level::DestroyAttack()
{
    if (mCurrentAttack)
    {
        mCurrentAttack->Kill();
        mCurrentAttack.reset();
    }
}

void Level::CreateMagic(std::string style, uint16_t strength, uint16_t cost)
{
    std::cout << style << std::endl;
    std::cout << strength << std::endl;
    std::cout << cost << std::endl;
}

void Level::DemagePlayer(uint16_t amount, std::string attackType)
{
    if (mPlayer->IsVulnerable())
    {
        mPlayer->TakeDemage(amount);
        mPlayer->BecomeTemporarilyInvulnerable();
    }
}
