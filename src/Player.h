#pragma once

#include <map>
#include <functional>

#include <SFML/Graphics.hpp>

// Core
#include "Core/Animation/Animation.h"
#include "Core/Base.h"
#include "Core/Toggles.h"

// Game
#include "Support.h"
#include "Settings.h"
#include "Entity.h"

// Forward Declarations
class Group;

class Player : public Entity
{
    using CreateAttackCB = std::function<void()>;
    using CreateMagicCB = std::function<void(std::string, uint16_t, uint16_t)>;
    using DestroyAttackCB = std::function<void()>;

private:
    static constexpr int TOGGLE_COOLDONW_MS = 200;

public:
    Player(sf::Vector2f position, const Group &obstacles, CreateAttackCB createAttack, CreateMagicCB createMagic, DestroyAttackCB destroyAttack);

    void Update(const sf::Time &timestamp) override;
    bool CanSwitchWeapon() const { return mCanSwitchWeapons.Value(); }
    bool CanSwitchMagic() const { return mCanSwitchMagic.Value(); }
    void BecomeTemporarilyInvulnerable() { mVulnerable.ToggleForCooldownTime(); }
    void TakeDemage(uint16_t amount) { mHealth = std::max(0, int(mHealth - amount)); }

    // Getters
    virtual sf::FloatRect GetHitbox() const override { return mHitBox; }
    std::string GetDirection() const;
    uint16_t GetHealth() const { return mHealth; }
    uint16_t GetEnergy() const { return mEnergy; }
    uint16_t GetEXP() const { return mEXP; }
    uint16_t GetFullWeaponDamage() const;
    bool IsVulnerable() const { return mVulnerable.Value(); }

    std::shared_ptr<sf::Texture> Player::GetWeaponTexture() const;
    std::shared_ptr<sf::Texture> GetWeaponIconTexture() const;
    std::shared_ptr<sf::Texture> GetMagicIconTexture() const;

private:
    void Input();
    void Cooldowns(const sf::Time &timestamp);
    void UpdateStatus();
    void Animate(const sf::Time &timestamp);

    std::string GetWeaponName() const { return GetWeaponByIndex(mWeaponIndex); }
    std::string GetMagicName() const { return GetMagicByIndex(mMagicIndex); }
    std::string GetWeaponByIndex(size_t index) const;
    std::string GetMagicByIndex(size_t index) const;
    void CreateMagicAttack();
    void UpdateSequenceFrame();

private:
    std::string mStatus;
    CooldownToggle mIsAttacking;
    CooldownToggle mCanSwitchWeapons;
    CooldownToggle mCanSwitchMagic;
    CooldownToggle mVulnerable;
    std::unique_ptr<Animation> mAnimation;
    CreateAttackCB mCreateAttack;
    CreateMagicCB mCreateMagic;
    DestroyAttackCB mDestroyAttack;
    size_t mWeaponIndex;
    size_t mMagicIndex;
    float mHealth;
    float mEnergy;
    float mEXP;
    float mAttack;
    float mSpeed;
};