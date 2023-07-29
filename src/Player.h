#pragma once

#include <map>

#include <SFML/Graphics.hpp>

// Core
#include "Core/Base.h"
#include "Core/Sprite.h"
#include "Core/Animation.h"

// Game
#include "Constants.h"
#include "Support.h"

// Forward Declarations
class SpriteGroup;

class Player : public Sprite
{
private:
    static constexpr int SPEED = 5;
    static constexpr int ANIMATION_FRAMES_PER_SECOND = 8;

public:
    Player(sf::Vector2f position, const SpriteGroup &obstacleSprites);

    void Update(const sf::Time &timestamp) override;
    virtual sf::FloatRect GetHitbox() const override { return mHitBox; }
    std::string GetStatus() const { return mAnimation.GetSequencesID(); }

private:
    void ImportPlayerAssets();
    void Input();
    void Cooldowns(const sf::Time &timestamp);
    void UpdateStatus();
    void Animate(const sf::Time &timestamp);
    void Move();
    void Collision(Direction direction);

    // Helper Methods
    bool IsMovingRight() { return mDirection.x > 0; }
    bool IsMovingLeft() { return mDirection.x < 0; }
    bool IsMovingUp() { return mDirection.y < 0; }
    bool IsMovingDown() { return mDirection.y > 0; }
    Scope<TextureAnimationSequence> CreateAnimationSequence(const std::string &sequenceID);

private:
    const SpriteGroup &mObstacleSprites;
    std::string mStatus;
    sf::Vector2f mDirection;
    bool mIsAttacking;
    sf::FloatRect mHitBox;
    uint16_t mAttackCooldown;
    uint16_t mAttackTime;
    Animation mAnimation;
};