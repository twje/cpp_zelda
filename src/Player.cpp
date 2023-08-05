// Core
#include "Core/Sprite.h"
#include "Core/Group.h"
#include "Core/Debug.h"
#include "Core/ResourceManagerUtils.h"
#include "Core/TextureManager.h"
#include "Core/RectUtils.h"

// Game
#include "Support.h"
#include "Player.h"
#include "Settings.h"

Player::Player(sf::Vector2f position, const Group &obstacleSpriteGroup, Callback createAttack, Callback destroyAttack)
    : Sprite(),
      mObstacleSpriteGroup(obstacleSpriteGroup),
      mDirection(0, 0),
      mStatus("down"),
      mIsAttacking(400, false),
      mCanSwitchWeapons(200, true),
      mCreateAttack(createAttack),
      mDestroyAttack(destroyAttack),
      mWeaponIndex(0)
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
        }

        // Switch weapons
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mCanSwitchWeapons.Value())
        {
            mCanSwitchWeapons.ToggleForCooldownTime();
            mWeaponIndex = (mWeaponIndex + 1) % WEAPON_DATA.size();
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

    mHitBox.left += mDirection.x * SPEED * timestamp.asSeconds();
    Collision(Direction::HORIZONTAL);
    mHitBox.top += mDirection.y * SPEED * timestamp.asSeconds();
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

void Player::UpdateSequenceFrame()
{
    SequenceFrame &frame = mAnimation.GetSequenceFrame();
    SetTexture(frame.mTexture);
    SetTextureRect(frame.mTextureRect);
}

void Player::InitAnimation()
{
    auto &textureManager = TextureManager::GetInstance();

    IndexResourcesViaPrefix resourceCollector(textureManager);
    for (const auto &playerData : PLAYER_DATA)
    {
        resourceCollector.AddResource(playerData.first);
    }

    for (const auto &entry : resourceCollector.GetResources())
    {
        auto sequence = CreateScope<TextureAnimationSequence>(ANIMATION_FRAMES_PER_SECOND, entry.second);
        mAnimation.AddAnimationSequence(entry.first, std::move(sequence));
    }
}
