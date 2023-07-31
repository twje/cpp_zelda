#pragma once

#include <map>
#include <functional>

#include <SFML/Graphics.hpp>

// Core
#include "Core/Base.h"
#include "Core/Sprite.h"
#include "Core/Animation.h"
#include "Core/Toggles.h"

// Game
#include "Support.h"
#include "Settings.h"

// Forward Declarations
class SpriteGroup;

class Player : public Sprite
{
    using Callback = std::function<void()>;

private:
    static constexpr int SPEED = 300;
    static constexpr int ANIMATION_FRAMES_PER_SECOND = 8;

public:
    Player(sf::Vector2f position, const SpriteGroup &obstacleSprites, Callback createAttack, Callback destroyAttack);

    void Update(const sf::Time &timestamp) override;
    virtual sf::FloatRect GetHitbox() const override { return mHitBox; }
    std::string GetAnimationGetSequenceID() const { return mAnimation.GetSequenceID(); }
    std::string GetDirection() const;
    std::string GetWeapon() const { return GetWeaponByIndex(mWeaponIndex); }

private:
    void Input();
    void Cooldowns(const sf::Time &timestamp);
    void UpdateStatus();
    void Animate(const sf::Time &timestamp);
    void Move(const sf::Time &timestamp);
    void Collision(Direction direction);

    // Helper Methods
    bool IsMovingRight() { return mDirection.x > 0; }
    bool IsMovingLeft() { return mDirection.x < 0; }
    bool IsMovingUp() { return mDirection.y < 0; }
    bool IsMovingDown() { return mDirection.y > 0; }
    std::string GetWeaponByIndex(size_t index) const;
    void UpdateSequenceFrame();
    Scope<TextureAnimationSequence> CreateAnimationSequence(const std::string &sequenceID);

private:
    const SpriteGroup &mObstacleSprites;
    std::string mStatus;
    sf::Vector2f mDirection;
    sf::FloatRect mHitBox;
    CooldownToggle mIsAttacking;
    CooldownToggle mCanSwitchWeapons;
    Animation mAnimation;
    Callback mCreateAttack;
    Callback mDestroyAttack;
    size_t mWeaponIndex;
};