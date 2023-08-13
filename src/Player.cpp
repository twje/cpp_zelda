#include <sstream>

// Core
#include "Core/Sprite.h"
#include "Core/Group.h"
#include "Core/Debug.h"
#include "Core/ResourceManager/ResourceManagerUtils.h"
#include "Core/ResourceManager/TextureManager.h"
#include "Core/Animation/TextureAnimationSequence.h"
#include "Core/Animation/FrameGenerators.h"
#include "Core/RectUtils.h"

// Game
#include "Support.h"
#include "Player.h"
#include "Settings.h"

Player::Player(sf::Vector2f position, const Group &obstacleSpriteGroup, CreateAttackCB createAttack, CreateMagicCB createMagic, DestroyAttackCB destroyAttack)
    : Sprite(),
      mObstacleSpriteGroup(obstacleSpriteGroup),
      mDirection(0, 0),
      mStatus("down"),
      mIsAttacking(400, false),
      mCanSwitchWeapons(TOGGLE_COOLDONW_MS, true),
      mCanSwitchMagic(TOGGLE_COOLDONW_MS, true),
      mCreateAttack(createAttack),
      mCreateMagic(createMagic),
      mDestroyAttack(destroyAttack),
      mWeaponIndex(0),
      mMagicIndex(0),
      mHealth(PLAYER_STATS.at("health") * 0.5),
      mEnergy(PLAYER_STATS.at("energy") * 0.8),
      mSpeed(PLAYER_STATS.at("speed")),
      mEXP(123)
{
    InitAnimation();
    mAnimation.SetAnimationSequence(mStatus);
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
    Move(timestamp);
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
            mIsAttacking.ToggleForCooldownTime();
            mCreateAttack();
        }

        // Magic input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            mIsAttacking.ToggleForCooldownTime();
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

void Player::Cooldowns(const sf::Time &timestamp)
{
    if (mIsAttacking.Update(timestamp))
    {
        mDestroyAttack();
    }
    mCanSwitchWeapons.Update(timestamp);
    mCanSwitchMagic.Update(timestamp);
}

void Player::Animate(const sf::Time &timestamp)
{
    if (mStatus != mAnimation.GetSequenceID())
    {
        mAnimation.SetAnimationSequence(mStatus);
    }

    mAnimation.Update(timestamp);
    UpdateSequenceFrame();
    SetPosition(GetRectCenter(mHitBox) - .5f * GetSize());
}

void Player::Move(const sf::Time &timestamp)
{
    if (mDirection.lengthSq() != 0)
    {
        mDirection = mDirection.normalized();
    }

    float speed = mSpeed * FPS * timestamp.asSeconds();
    mHitBox.left += mDirection.x * speed;
    Collision(Direction::HORIZONTAL);
    mHitBox.top += mDirection.y * speed;
    Collision(Direction::VERTICAL);
    SetPosition(GetRectCenter(mHitBox) - .5f * GetSize());
}

void Player::Collision(Direction direction)
{
    if (direction == Direction::HORIZONTAL)
    {
        for (const auto &sprite : mObstacleSpriteGroup.GetGameObjects())
        {
            auto result = sprite->GetHitbox().findIntersection(mHitBox);
            if (result.has_value())
            {
                const auto spriteHitbox = sprite->GetHitbox();
                if (IsMovingRight())
                {
                    mHitBox.left = spriteHitbox.left - mHitBox.width;
                }

                if (IsMovingLeft())
                {
                    mHitBox.left = spriteHitbox.left + spriteHitbox.width;
                }
            }
        }
    }

    if (direction == Direction::VERTICAL)
    {
        for (const auto &sprite : mObstacleSpriteGroup.GetGameObjects())
        {
            auto result = sprite->GetHitbox().findIntersection(mHitBox);
            if (result.has_value())
            {
                const auto spriteHitbox = sprite->GetHitbox();
                if (IsMovingDown())
                {
                    mHitBox.top = spriteHitbox.top - mHitBox.height;
                }

                if (IsMovingUp())
                {
                    mHitBox.top = spriteHitbox.top + spriteHitbox.height;
                }
            }
        }
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

void Player::CreateMagicAttack()
{
    auto it = MAGIC_DATA.begin();
    std::advance(it, mMagicIndex);

    std::string style = it->first;
    float strength = it->second.mStrength + PLAYER_STATS.at("magic");
    float cost = it->second.mCost;
    mCreateMagic(style, strength, cost);
}

void Player::UpdateSequenceFrame()
{
    SequenceFrame &frame = mAnimation.GetSequenceFrame();
    SetTexture(frame.mTexture);
    SetTextureRect(frame.mTextureRect);
}

void Player::InitAnimation()
{
    std::map<std::string, std::vector<std::string>> textureMap = GroupResources(TextureManager::GetInstance());
    for (const auto &entry : textureMap)
    {
        auto sequence = CreateScope<TextureAnimationSequence>(ANIMATION_FRAMES_PER_SECOND, std::make_unique<ListFrameGenerator>(entry.second));
        mAnimation.AddAnimationSequence(entry.first, std::move(sequence));
    }
}
