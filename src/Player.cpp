// Core
#include "Core/Sprite.h"
#include "Core/SpriteGroup.h"
#include "Core/Debug.h"
#include "Core/TextureManager.h"

// Game
#include "Support.h"
#include "Player.h"

Player::Player(sf::Vector2f position, const SpriteGroup &obstacleSprites)
    : Sprite(sf::IntRect(sf::Vector2i(), sf::Vector2i(TILESIZE, TILESIZE))),
      mObstacleSprites(obstacleSprites),
      mDirection(0, 0),
      mStatus("down"),
      mIsAttacking(false),
      mAttackCooldown(400),
      mAttackTime(0)
{
    setPosition(position);
    mHitBox = InflateRect(GetBoundingBox(), 0, -26);
    ImportPlayerAssets();
}

void Player::Update(const sf::Time &timestamp)
{
    Input();
    Cooldowns(timestamp);
    UpdateStatus();
    Animate(timestamp);
    Move(timestamp);
}

void Player::ImportPlayerAssets()
{
    for (const std::string &animation : {
             "up",
             "down",
             "left",
             "right",
             "up_idle",
             "down_idle",
             "left_idle",
             "right_idle",
             "up_attack",
             "down_attack",
             "left_attack",
             "right_attack"})
    {
        mAnimation.AddAnimationSequence(animation, std::move(CreateAnimationSequence(animation)));
    }
    mAnimation.SetAnimationSequence(mStatus);
}

void Player::Input()
{
    if (!mIsAttacking)
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
            mIsAttacking = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            mIsAttacking = true;
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

    if (mIsAttacking)
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
    if (mIsAttacking)
    {
        mAttackTime += timestamp.asMilliseconds();
        if (mAttackTime > mAttackCooldown)
        {
            mIsAttacking = false;
            mAttackTime = 0;
        }
    }
}

void Player::Animate(const sf::Time &timestamp)
{
    if (mStatus != mAnimation.GetSequenceID())
    {
        mAnimation.SetAnimationSequence(mStatus);
    }
    mAnimation.Update(timestamp);
    setTexture(mAnimation.GetSequenceFrame());
    setPosition(GetRectCenter(mHitBox) - .5f * GetSize());
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
    setPosition(GetRectCenter(mHitBox) - .5f * GetSize());
}

void Player::Collision(Direction direction)
{
    if (direction == Direction::HORIZONTAL)
    {
        for (const auto &sprite : mObstacleSprites.GetSprites())
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
        for (const auto &sprite : mObstacleSprites.GetSprites())
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

Scope<TextureAnimationSequence> Player::CreateAnimationSequence(const std::string &sequenceID)
{
    const std::string characterPath = "../graphics/player/";
    auto &textureManager = TextureManager::GetInstance();
    textureManager.LoadTextures(sequenceID, characterPath + sequenceID);
    return CreateScope<TextureAnimationSequence>(ANIMATION_FRAMES_PER_SECOND, textureManager.GetTextures(sequenceID));
}