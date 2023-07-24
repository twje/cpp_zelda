// Core
#include "Core/Debug.h"
#include "Core/OstreamOverloads.h"

// Game
#include "LevelView.h"
#include "Level.h"
#include "Player.h"

#include "Core/OstreamOverloads.h"
#include <iostream>

LevelView::LevelView(const Level &level)
    : mLevel(level)
{
}

void LevelView::Draw(sf::RenderWindow &window)
{
    mSortedSpriteGroup = mLevel.GetVisibleSpriteGroup();
    mSortedSpriteGroup.YSortSprites();

    const Player &player = mLevel.GetPlayer();
    mCameraOffset = GetFixedCenterCameraOffset(window, player);

    // Draw floor
    sf::Sprite floorSprite(mLevel.GetFloorTexture());
    floorSprite.setPosition(sf::Vector2f(-mCameraOffset.x, -mCameraOffset.y));
    window.draw(floorSprite);

    // Draw Tiles
    for (const auto &internalSprite : mSortedSpriteGroup.GetSprites())
    {
        const SpriteData &data = internalSprite->GetSpriteData();

        sf::Vector2f offsetPos(data.GetBoundingBox().GetLeft() - mCameraOffset.x,
                               data.GetBoundingBox().GetTop() - mCameraOffset.y);

        sf::Sprite sprite(data.GetTexture());
        sprite.setTextureRect(data.GetTextureRegion());
        sprite.setPosition(offsetPos);
        window.draw(sprite);
    }
    DebugDraw(window);
}

sf::Vector2f LevelView::GetFixedCenterCameraOffset(sf::RenderWindow &window, const Sprite &relativeTo)
{
    return sf::Vector2f(relativeTo.GetSpriteData().GetBoundingBox().GetCenterX() - window.getSize().x / 2,
                        relativeTo.GetSpriteData().GetBoundingBox().GetCenterY() - window.getSize().y / 2);
}

void LevelView::DebugDraw(sf::RenderWindow &window)
{
#ifdef DEBUG_BUILD
    DebugDrawPlayer(window);
    DebugHitbox(window);
#endif
}

void LevelView::DebugDrawPlayer(sf::RenderWindow &window)
{
    const Player &player = mLevel.GetPlayer();

    // Draw Bounding Box
    FloatRect rect = player.GetSpriteData().GetBoundingBox();
    rect.SetPosition(rect.GetLeft() - mCameraOffset.x, rect.GetTop() - mCameraOffset.y);
    DrawTransparentRectangle(window, rect, sf::Color::White, 2);

    // Player Direction
    DrawDebugString(window, player.GetStatus());
}

void LevelView::DebugHitbox(sf::RenderWindow &window)
{
    for (const auto &internalSprite : mSortedSpriteGroup.GetSprites())
    {
        sf::Vector2f offsetPos(internalSprite->GetSpriteData().GetBoundingBox().GetLeft() - mCameraOffset.x,
                               internalSprite->GetSpriteData().GetBoundingBox().GetTop() - mCameraOffset.y);

        FloatRect hitBox = internalSprite->GetSpriteData().GetHitBox();
        hitBox.SetPosition(hitBox.GetLeft() - mCameraOffset.x, hitBox.GetTop() - mCameraOffset.y);
        DrawTransparentRectangle(window, hitBox, sf::Color::Red, 2);
    }
}