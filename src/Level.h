#pragma once

#include <sstream>

#include <map>
#include <memory>

// Core
#include "Core/Layer.h"
#include "Core/Group.h"
#include "Core/Debug.h"

// Game
#include "Settings.h"
#include "Support.h"
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "LevelView.h"
#include "UI.h"

namespace Factory
{
    class LevelFriend
    {
    public:
        static std::shared_ptr<Player> CreatePlayer(Level *level, float x, float y, const Group &obstacles);
        static std::shared_ptr<Enemy> CreateEnemy(Level *level, std::string name, float x, float y, const Group &obstacles);
    };
}

class Level : public Layer
{
    friend class Factory::LevelFriend;

public:
    Level();

    void Update(const sf::Time &timestamp) override;
    void UpdateEnemies(const sf::Time &timestamp);
    void Draw(sf::RenderWindow &window) override;
    void OnWindowResize(sf::Vector2u size) override;

    // Getters
    const Player &GetPlayer() const { return *mPlayer; }
    const Group &GetVisibleSpriteGroup() const { return mVisibleGroup; }
    const sf::Texture &GetFloorTexture() const { return *mFloor; }

private:
    void CreateMap();

    // Callbacks
    void CreateAttack();
    void CreateMagic(std::string style, uint16_t strength, uint16_t cost);
    void DestroyAttack();
    void HandlePlayerAttack();
    void DemagePlayer(uint16_t amount, std::string attackType);

private:
    Ref<Player> mPlayer;
    Ref<Weapon> mCurrentAttack;
    Group mEnemies;
    Group mVisibleGroup;
    Group mObstacleGroup;
    Group mAttackableGroup;
    Group mAttackGroup;
    TextureMap mGraphics;
    TexturePtr mInvisibleBlock;
    TexturePtr mFloor;
    std::unique_ptr<LevelView> mLevelView;
    std::unique_ptr<UI> mUI;
};