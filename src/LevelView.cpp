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
        sf::Vector2f offsetPos(internalSprite->GetRect().GetLeft() - mCameraOffset.x,
                               internalSprite->GetRect().GetTop() - mCameraOffset.y);

        sf::Sprite sprite(internalSprite->GetTexture());
        sprite.setPosition(offsetPos);
        window.draw(sprite);
    }
    DebugDraw(window);
}

sf::Vector2f LevelView::GetFixedCenterCameraOffset(sf::RenderWindow &window, const Sprite &relativeTo)
{
    return sf::Vector2f(relativeTo.GetRect().GetCenterX() - window.getSize().x / 2,
                        relativeTo.GetRect().GetCenterY() - window.getSize().y / 2);
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
    FloatRect rect = player.GetRect();
    rect.SetPosition(rect.GetLeft() - mCameraOffset.x, rect.GetTop() - mCameraOffset.y);
    DrawTransparentRectangle(window, rect, sf::Color::White, 2);

    // Player Direction
    DrawDebugString(window, player.GetStatus());
}

void LevelView::DebugHitbox(sf::RenderWindow &window)
{
    for (const auto &internalSprite : mSortedSpriteGroup.GetSprites())
    {
        sf::Vector2f offsetPos(internalSprite->GetRect().GetLeft() - mCameraOffset.x,
                               internalSprite->GetRect().GetTop() - mCameraOffset.y);

        FloatRect hitBox = internalSprite->GetHitbox();
        hitBox.SetPosition(hitBox.GetLeft() - mCameraOffset.x, hitBox.GetTop() - mCameraOffset.y);
        DrawTransparentRectangle(window, hitBox, sf::Color::Red, 2);
    }

    // FloatRect hitBox = player.GetHitbox();
    // hitBox.SetPosition(hitBox.GetLeft() - mCameraOffset.x, hitBox.GetTop() - mCameraOffset.y);
    // DrawTransparentRectangle(window, hitBox, sf::Color::Red, 2);
}