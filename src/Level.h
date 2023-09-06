#pragma once

#include <sstream>

#include <map>
#include <memory>

// Core
#include "Core/Layer.h"
#include "Core/GroupManager.h"
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

class Level : public Layer, public IPlayerCallbacks, public IEnemyCallbacks
{
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
    void HandlePlayerAttack();

    // IPlayerCallbacks
    virtual void CreateAttack() override;
    virtual void DestroyAttack() override;
    virtual void CreateMagic(std::string style, uint16_t strength, uint16_t cost) override;

    // IEntityCallbacks
    virtual void DemagePlayer(uint16_t amount, std::string attackType) override;

private:
    Ref<Player> mPlayer;
    Ref<Weapon> mCurrentAttack;
    GroupManager mGroupManager;
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