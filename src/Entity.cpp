#include "Entity.h"

// Core
#include "Core/RectUtils.h"
#include "Core/Group.h"

class Moveable
{
};

Entity::Entity(GroupManager& groupManager, const Group& obstacles)
    : EntityBase(groupManager),
      mObstacles(obstacles),
      mDirection(0, 0)
{
}

void Entity::Move(const sf::Time &timestamp, float pixelsPerFrame)
{
    if (mDirection.lengthSq() != 0)
    {
        mDirection = mDirection.normalized();
    }

    float speed = pixelsPerFrame * FPS * timestamp.asSeconds();
    mHitBox.left += mDirection.x * speed;
    Collision(Direction::HORIZONTAL);
    mHitBox.top += mDirection.y * speed;
    Collision(Direction::VERTICAL);
    SetPosition(GetRectCenter(mHitBox) - .5f * GetSize());
}

void Entity::Collision(Direction direction)
{
    if (direction == Direction::HORIZONTAL)
    {
        for (const auto &sprite : mObstacles.GetGameObjects())
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
        for (const auto &sprite : mObstacles.GetGameObjects())
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

uint8_t Entity::WaveValue()
{
    double value = std::sin(mWaveClock.getElapsedTime().asMicroseconds());
    return value >= 0 ? 255 : 0;
}