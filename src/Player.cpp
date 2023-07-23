// Core
#include "Core/Sprite.h"
#include "Core/Rect.h"
#include "Core/SpriteGroup.h"
#include "Core/Debug.h"
#include "Support.h"

// Game
#include "Player.h"

Player::Player(sf::Vector2f position, const SpriteGroup &obstacleSprites)
    : Sprite(),
      mTexture(importTexture("../graphics/test/player.png")),
      mDirection(0, 0),
      mObstacleSprites(obstacleSprites)
{
    mRect = FloatRect(position, sf::Vector2f(mTexture->getSize()));
    mHitbox = mRect.Inflate(0, -26);
}

void Player::Update()
{
    Input();
    Move();
}

void Player::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        mDirection.y = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        mDirection.y = 1;
    }
    else
    {
        mDirection.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        mDirection.x = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        mDirection.x = -1;
    }
    else
    {
        mDirection.x = 0;
    }
}

void Player::Move()
{
    if (mDirection.lengthSq() != 0)
    {
        mDirection = mDirection.normalized();
    }

    mHitbox.MoveHorizontally(mDirection.x * SPEED);
    Collision(Direction::HORIZONTAL);
    mHitbox.MoveVertically(mDirection.y * SPEED);
    Collision(Direction::VERTICAL);
    mRect.SetCenter(mHitbox.GetCenterX(), mHitbox.GetCenterY());
}

void Player::Collision(Direction direction)
{
    if (direction == Direction::HORIZONTAL)
    {
        for (const auto &sprite : mObstacleSprites.GetSprites())
        {
            auto result = sprite->GetRect().FindIntersection(mHitbox);
            if (result.has_value())
            {
                const auto spriteRect = sprite->GetRect();
                if (IsMovingRight())
                {
                    mHitbox.SetRight(spriteRect.GetLeft());
                }

                if (IsMovingLeft())
                {
                    mHitbox.SetLeft(spriteRect.GetRight());
                }
            }
        }
    }

    if (direction == Direction::VERTICAL)
    {
        for (const auto &sprite : mObstacleSprites.GetSprites())
        {
            auto result = sprite->GetRect().FindIntersection(mHitbox);
            if (result.has_value())
            {
                const auto spriteRect = sprite->GetRect();
                if (IsMovingDown())
                {
                    mHitbox.SetBottom(spriteRect.GetTop());
                }

                if (IsMovingUp())
                {
                    mHitbox.SetTop(spriteRect.GetBottom());
                }
            }
        }
    }
}