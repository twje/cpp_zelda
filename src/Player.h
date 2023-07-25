#pragma once

#include <map>

#include <SFML/Graphics.hpp>

// Core
#include "Core/Sprite.h"

// Game
#include "Constants.h"
#include "Support.h"

// Forward Declarations
class SpriteGroup;

class Player : public Sprite
{
private:
    static constexpr int SPEED = 5;

public:
    Player(sf::Vector2f position, const SpriteGroup &obstacleSprites);
    ~Player() {}

public:
    void Update(const sf::Time &timestamp) override;
    void Draw(sf::RenderWindow &window) override;

    // Getters
    const SpriteDataView &GetSpriteData() const { return mData.GetDataView(); }
    const std::string &GetStatus() const { return mStatus; }
    sf::Vector2f GetDirection() const { return mDirection; }

private:
    void Input();
    void Cooldowns(const sf::Time &timestamp);
    void Animate();
    void Move();
    void Collision(Direction direction);
    void ImportPlayerAssets();
    void UpdateStatus();
    bool IsMovingRight() { return mDirection.x > 0; }
    bool IsMovingLeft() { return mDirection.x < 0; }
    bool IsMovingUp() { return mDirection.y < 0; }
    bool IsMovingDown() { return mDirection.y > 0; }

private:
    SpriteData mData;
    std::string mStatus;
    sf::Vector2f mDirection;
    const SpriteGroup &mObstacleSprites;
    std::map<std::string, std::unique_ptr<Textures>> mAnimations;
    bool mIsAttacking;
    uint16_t mAttackCooldown;
    uint16_t mAttackTime;
    float mFrameIndex;
    float mAnimationSpeed;
};