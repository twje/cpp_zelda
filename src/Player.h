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

    // Getters
    const std::string &GetStatus() const { return mStatus; }
    const sf::Texture &GetTexture() const override { return *mTexture; }
    sf::IntRect GetTextureRegion() const { return mTextureRegion; }
    FloatRect GetRect() const override { return mRect; }
    FloatRect GetHitbox() const override { return mHitbox; };
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
    sf::Texture *mTexture;
    sf::IntRect mTextureRegion;
    FloatRect mRect;
    FloatRect mHitbox;
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