#pragma once

#include <iostream>

// Core
#include "Core/Animation/Animation.h"
#include "Core/Toggles.h"

// Game
#include "Entity.h"
#include "Components.h"

class Group;
class Enemy;

class EnemyAttackableComponent : public AttackableComponent
{
public:
    EnemyAttackableComponent(Enemy &owner);
    void InflictDemage(const Player &player, GameObject &attacker) override;
    bool IsDead() override;

private:
    Enemy &mOwner;
};

class IEnemyCallbacks
{
public:
    virtual void DemagePlayer(uint16_t amount, std::string attackType) = 0;
};

class Enemy : public Entity
{
    friend EnemyAttackableComponent;    

public:
    Enemy(GroupManager& groupManager, const std::string &name, sf::Vector2f position, const Group &obstacles, IEnemyCallbacks& callbacks);

    void Update(const sf::Time &timestamp) override;
    void HitReaction();
    void Animate(const sf::Time &timestamp);
    void UpdateSequenceFrame();
    void Cooldown(const sf::Time &timestamp);
    void EnemyUpdate(const Player &player);

    // Getter
    sf::FloatRect GetHitbox() const override { return mHitBox; }
    uint16_t GetHealth() { return mHealth; }

private:
    void InflictDemage(const Player &player, uint16_t demage);
    bool IsAttackAnimationPlaying();
    bool IsAllowedToAttack();
    std::pair<float, sf::Vector2f> GetPlayerDistanceDirection(const Player &player);
    void GetStatus(const Player &player);
    void Actions(const Player &player);

private:
    std::string mName;
    SpriteType mSpriteType;
    std::unique_ptr<Animation> mAnimation;
    std::string mStatus;
    uint16_t mHealth;
    uint16_t mExp;
    uint16_t mSpeed;
    uint16_t mAttackDamage;
    uint16_t mResistance;
    uint16_t mAttackRadius;
    uint16_t mNoticeRadius;
    std::string mAttackType;
    CooldownToggle mCanAttack;
    CooldownToggle mIsVulnerable;
    IEnemyCallbacks& mCallbacks;
};