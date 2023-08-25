#pragma once

// Core
#include "Core/Animation/Animation.h"
#include "Core/Toggles.h"

// Game
#include "Entity.h"

class Player;
class Group;

class Enemy : public Entity
{
public:
    Enemy(const std::string &name, sf::Vector2f position, const Group &obstacles);

    void Update(const sf::Time &timestamp) override;
    void Animate(const sf::Time &timestamp);
    void UpdateSequenceFrame();
    void Cooldown(const sf::Time &timestamp);
    void EnemyUpdate(const Player &player);

    // Getters
    virtual sf::FloatRect GetHitbox() const override { return mHitBox; }

private:
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
};