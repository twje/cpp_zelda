// Core
#include "Core/Sprite.h"
#include "Core/Rect.h"
#include "Core/SpriteGroup.h"
#include "Core/Debug.h"
#include "Support.h"

#include "Player.h"

Player::Player(sf::Vector2f position, const SpriteGroup &obstacleSprites)
    : Sprite(),
      mDirection(0, 0),
      mObstacleSprites(obstacleSprites),
      mStatus("down"),
      mIsAttacking(false),
      mAttackCooldown(400),
      mAttackTime(0),
      mFrameIndex(0),
      mAnimationSpeed(0.15)
{
    mData.mTexture = importTexture("../graphics/test/player.png").release();
    mData.mTextureRegion = sf::IntRect(sf::Vector2i(), sf::Vector2i(mData.mTexture->getSize()));
    mData.mBoundingBox = FloatRect(position, sf::Vector2f(mData.mTexture->getSize()));
    mData.mHitBox = mData.mBoundingBox.Inflate(0, -26);
    ImportPlayerAssets();
}

void Player::Update(const sf::Time &timestamp)
{
    Input();
    Cooldowns(timestamp);
    UpdateStatus();
    Animate();
    Move();
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

void Player::Animate()
{
    Textures &animation = *mAnimations[mStatus];

    mFrameIndex += mAnimationSpeed;
    if (mFrameIndex >= animation.size())
    {
        mFrameIndex = 0;
    }

    mData.mTexture = &animation[mFrameIndex];
    mData.mBoundingBox = FloatRect(sf::Vector2f(0, 0), sf::Vector2f(mData.mTexture->getSize()));
    mData.mBoundingBox.AnchorPosition(Anchor::CENTER, mData.mHitBox.GetCenter());
}

void Player::Move()
{
    if (mDirection.lengthSq() != 0)
    {
        mDirection = mDirection.normalized();
    }

    mData.mHitBox.MoveHorizontally(mDirection.x * SPEED);
    Collision(Direction::HORIZONTAL);
    mData.mHitBox.MoveVertically(mDirection.y * SPEED);
    Collision(Direction::VERTICAL);
    mData.mBoundingBox.AnchorPosition(Anchor::CENTER, mData.mHitBox.GetCenter());
}

void Player::Collision(Direction direction)
{
    if (direction == Direction::HORIZONTAL)
    {
        for (const auto &sprite : mObstacleSprites.GetSprites())
        {
            auto result = sprite->GetSpriteData().GetHitBox().FindIntersection(mData.mHitBox);
            if (result.has_value())
            {
                const auto spriteHitbox = sprite->GetSpriteData().GetHitBox();
                if (IsMovingRight())
                {
                    mData.mHitBox.SetRight(spriteHitbox.GetLeft());
                }

                if (IsMovingLeft())
                {
                    mData.mHitBox.SetLeft(spriteHitbox.GetRight());
                }
            }
        }
    }

    if (direction == Direction::VERTICAL)
    {
        for (const auto &sprite : mObstacleSprites.GetSprites())
        {
            auto result = sprite->GetSpriteData().GetHitBox().FindIntersection(mData.mHitBox);
            if (result.has_value())
            {
                const auto spriteRect = sprite->GetSpriteData().GetHitBox();
                if (IsMovingDown())
                {
                    mData.mHitBox.SetBottom(spriteRect.GetTop());
                }

                if (IsMovingUp())
                {
                    mData.mHitBox.SetTop(spriteRect.GetBottom());
                }
            }
        }
    }
}

void Player::ImportPlayerAssets()
{
    const std::string characterPath = "../graphics/player/";
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
        mAnimations.emplace(animation, importTexturesFromDirectoryRecursive(characterPath + animation));
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