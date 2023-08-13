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
class Group;

class Player : public Sprite
{
    // Type aliases
    template <typename... Args>
    using Callback = std::function<void(Args...)>;

    using CreateAttackCB = Callback<>;
    using CreateMagicCB = Callback<std::string, uint16_t, uint16_t>;
    using DestroyAttackCB = Callback<>;

private:
    static constexpr int ANIMATION_FRAMES_PER_SECOND = 8;

public:
    Player(sf::Vector2f position, const Group &obstacleSpriteGroup, CreateAttackCB createAttack, CreateMagicCB mCreateMagic, DestroyAttackCB destroyAttack);

    void Update(const sf::Time &timestamp) override;
    bool CanSwitchWeapon() const { return mCanSwitchWeapons.Value(); }
    bool CanSwitchMagic() const { return mCanSwitchMagic.Value(); }

    // Getters
    virtual sf::FloatRect GetHitbox() const override { return mHitBox; }
    std::string GetAnimationGetSequenceID() const { return mAnimation.GetSequenceID(); }
    std::string GetDirection() const;
    uint16_t GetHealth() const { return mHealth; }
    uint16_t GetEnergy() const { return mEnergy; }
    uint16_t GetEXP() const { return mEXP; }
    std::string GetWeaponName() const { return GetWeaponByIndex(mWeaponIndex); }
    std::string GetMagicName() const { return GetMagicByIndex(mMagicIndex); }
    std::shared_ptr<sf::Texture> Player::GetWeaponTexture() const;
    std::shared_ptr<sf::Texture> GetWeaponIconTexture() const;
    std::shared_ptr<sf::Texture> GetMagicIconTexture() const;

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
    std::string GetMagicByIndex(size_t index) const;
    void CreateMagicAttack();
    void UpdateSequenceFrame();
    void InitAnimation();

private:
    const Group &mObstacleSpriteGroup;
    std::string mStatus;
    sf::Vector2f mDirection;
    sf::FloatRect mHitBox;
    CooldownToggle mIsAttacking;
    CooldownToggle mCanSwitchWeapons;
    CooldownToggle mCanSwitchMagic;
    Animation mAnimation;
    CreateAttackCB mCreateAttack;
    CreateMagicCB mCreateMagic;
    DestroyAttackCB mDestroyAttack;
    size_t mWeaponIndex;
    size_t mMagicIndex;
    float mHealth;
    float mEnergy;
    float mEXP;
    float mSpeed;
};