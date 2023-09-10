#include <sstream>

// Core
#include "Core/Sprite.h"
#include "Core/Group.h"
#include "Core/Debug.h"
#include "Core/ResourceManager/ResourceManagerUtils.h"
#include "Core/ResourceManager/TextureManager.h"
#include "Core/ResourceManager/AnimationManager.h"
#include "Core/Animation/TextureAnimationSequence.h"
#include "Core/RectUtils.h"

// Game
#include "Support.h"
#include "Player.h"
#include "Settings.h"

Player::Player(GroupManager& groupManager, sf::Vector2f position, const Group& obstacles, IPlayerCallbacks& callbacks)
    : Entity(groupManager, obstacles),
      mStatus("down"),
      mAttackStatus(AttackStatus::NONE),
      mIsAttacking(400, false),
      mCanSwitchWeapons(TOGGLE_COOLDONW_MS, true),
      mCanSwitchMagic(TOGGLE_COOLDONW_MS, true),
      mVulnerable(500, true),
      mAnimation(AnimationManager::GetInstance().LoadUnique("player")),
      mCallbacks(callbacks),
      mWeaponIndex(0),
      mMagicIndex(0),
      mHealth(PLAYER_STATS.at("health") * 0.5),
      mEnergy(PLAYER_STATS.at("energy") * 0.8),
      mSpeed(PLAYER_STATS.at("speed")),
      mAttack(PLAYER_STATS.at("attack")),
      mMagic(PLAYER_STATS.at("magic")),
      mEXP(123)
{
    mAnimation->SetAnimationSequence(mStatus);
    UpdateSequenceFrame();
    SetPosition(position);
    mHitBox = InflateRect(GetGlobalBounds(), 0, -26);
}

void Player::Update(const sf::Time &timestamp)
{
    Input();
    Cooldowns(timestamp);
    UpdateStatus();
    Animate(timestamp);
    Move(timestamp, mSpeed);
    RecoverEnergy();
}

std::string Player::GetDirection() const
{
    size_t index = mStatus.find('_');
    if (index == std::string::npos)
    {
        return mStatus;
    }
    return mStatus.substr(0, index);
}

uint16_t Player::GetFullWeaponDamage() const
{
    return mAttack + WEAPON_DATA.at(GetWeaponName()).mDamage;
}

uint16_t Player::GetFullMagicDamage() const
{
    return mMagic + MAGIC_DATA.at(GetMagicName()).mStrength;
}

void Player::AddHealth(float value)
{
    mHealth += value;
    mHealth = std::max(0.0f, std::min(mHealth, static_cast<float>(PLAYER_STATS.at("health"))));
}

void Player::AddEnergy(float value)
{
    mEnergy += value;
    mEnergy = std::max(0.0f, std::min(mEnergy, static_cast<float>(PLAYER_STATS.at("energy"))));
}

std::shared_ptr<sf::Texture> Player::GetWeaponTexture() const
{
    std::ostringstream oss;
    oss << GetWeaponName() << "_" << GetDirection();
    return TextureManager::GetInstance().GetResource(oss.str());
}

std::shared_ptr<sf::Texture> Player::GetWeaponIconTexture() const
{
    std::string direction = GetDirection();
    std::ostringstream oss;
    oss << GetWeaponName() << "_full";
    return TextureManager::GetInstance().GetResource(oss.str());
}

std::shared_ptr<sf::Texture> Player::GetMagicIconTexture() const
{
    return TextureManager::GetInstance().GetResource(GetMagicName());
}

void Player::Input()
{
    if (!mIsAttacking.Value())
    {
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            mDirection.y = -1;
            mStatus = "up";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            mDirection.y = 1;
            mStatus = "down";
        }
        else
        {
            mDirection.y = 0;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            mDirection.x = 1;
            mStatus = "right";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            mDirection.x = -1;
            mStatus = "left";
        }
        else
        {
            mDirection.x = 0;
        }

        // Attack input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {            
            CreatePhysicalAttack();
        }

        // Magic input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {            
            CreateMagicAttack();         
        }

        // Switch weapon
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mCanSwitchWeapons.Value())
        {
            mCanSwitchWeapons.ToggleForCooldownTime();
            mWeaponIndex = (mWeaponIndex + 1) % WEAPON_DATA.size();
        }

        // Switch magic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mCanSwitchMagic.Value())
        {
            mCanSwitchMagic.ToggleForCooldownTime();
            mMagicIndex = (mMagicIndex + 1) % MAGIC_DATA.size();
        }
    }
}

void Player::UpdateStatus()
{
    if (mDirection.lengthSq() == 0)
    {
        if (!isSubstring(mStatus, "idle") && !isSubstring(mStatus, "attack"))
        {
            mStatus += "_idle";
        }
    }

    if (mIsAttacking.Value())
    {
        mDirection.x = 0;
        mDirection.y = 0;
        if (!isSubstring(mStatus, "attack"))
        {
            if (isSubstring(mStatus, "idle"))
            {
                replaceSubstring(mStatus, "_idle", "_attack");
            }
            else
            {
                mStatus += "_attack";
            }
        }
    }
    else
    {
        if (isSubstring(mStatus, "attack"))
        {
            replaceSubstring(mStatus, "_attack", "");
        }
    }
}

void Player::RecoverEnergy()
{
    if (mEnergy <= PLAYER_STATS.at("energy"))
    {
        mEnergy += 0.1f * PLAYER_STATS.at("magic");
    }
    else
    {
        mEnergy = PLAYER_STATS.at("energy");
    }
}

void Player::Cooldowns(const sf::Time &timestamp)
{
    if (mIsAttacking.Update(timestamp))
    {
        mCallbacks.DestroyAttack();    
        mAttackStatus = AttackStatus::NONE;
    }

    mCanSwitchWeapons.Update(timestamp);
    mCanSwitchMagic.Update(timestamp);
    mVulnerable.Update(timestamp);    
}

void Player::Animate(const sf::Time &timestamp)
{
    if (mStatus != mAnimation->GetSequenceID())
    {
        mAnimation->SetAnimationSequence(mStatus);
    }

    mAnimation->Update(timestamp);
    UpdateSequenceFrame();
    SetPosition(GetRectCenter(mHitBox) - .5f * GetSize());

    if (mVulnerable.Value())
    {
        SetAlpha(255);
    }
    else
    {
        SetAlpha(WaveValue());
    }
}

std::string Player::GetWeaponByIndex(size_t index) const
{
    assert(index < WEAPON_DATA.size());
    auto it = WEAPON_DATA.begin();
    std::advance(it, index);
    return it->first;
}

std::string Player::GetMagicByIndex(size_t index) const
{
    assert(index < MAGIC_DATA.size());
    auto it = MAGIC_DATA.begin();
    std::advance(it, index);
    return it->first;
}

void Player::CreatePhysicalAttack()
{
    mIsAttacking.ToggleForCooldownTime();
    mCallbacks.CreateAttack();
    mAttackStatus = AttackStatus::PHYSICAL;
}

void Player::CreateMagicAttack()
{
    mIsAttacking.ToggleForCooldownTime();    
    mAttackStatus = AttackStatus::MAGIC;

    auto it = MAGIC_DATA.begin();
    std::advance(it, mMagicIndex);

    std::string style = it->first;
    float strength = it->second.mStrength + PLAYER_STATS.at("magic");
    float cost = it->second.mCost;

    if (mEnergy >= cost)
    {
        mCallbacks.CreateMagic(style, strength, cost);
    }
}

void Player::UpdateSequenceFrame()
{
    SequenceFrame &frame = mAnimation->GetSequenceFrame();
    SetTexture(frame.mTexture);
    SetTextureRect(frame.mTextureRect);
}
