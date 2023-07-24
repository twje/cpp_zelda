// Core
#include "Core/Debug.h"
#include "Core/OstreamOverloads.h"

// Game
#include "LevelView.h"
#include "Level.h"
#include "Player.h"

#include "Core/OstreamOverloads.h"
#include <iostream>

LevelView::LevelView(sf::RenderWindow &window, const Level &level)
    : mWindow(window),
      mLevel(level),
      mView(sf::Vector2f(), sf::Vector2f(window.getSize()))
{
}

void LevelView::Draw(sf::RenderWindow &window)
{
    const Player &player = mLevel.GetPlayer();
    mView.setCenter(player.GetSpriteData().GetBoundingBox().GetCenter());
    mWindow.setView(mView);

    mSortedSpriteGroup = mLevel.GetVisibleSpriteGroup();
    mSortedSpriteGroup.YSortSprites();

    // Draw floor
    sf::Sprite floorSprite(mLevel.GetFloorTexture());
    floorSprite.setPosition(sf::Vector2f());
    window.draw(floorSprite);

    // Draw Tiles
    for (const auto &internalSprite : mSortedSpriteGroup.GetSprites())
    {
        const SpriteDataView &data = internalSprite->GetSpriteData();
        sf::Sprite sprite(data.GetTexture());
        sprite.setTextureRect(data.GetTextureRegion());
        sprite.setPosition(data.GetBoundingBox().GetPosition());
        window.draw(sprite);
    }

    DebugDraw(window);
    window.setView(window.getDefaultView());
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
    DrawTransparentRectangle(window, player.GetSpriteData().GetBoundingBox(), sf::Color::White, 2);
    DrawDebugString(window, player.GetStatus());
}

void LevelView::DebugHitbox(sf::RenderWindow &window)
{
    for (const auto &sprite : mSortedSpriteGroup.GetSprites())
    {
        DrawTransparentRectangle(window, sprite->GetSpriteData().GetHitBox(), sf::Color::Red, 2);
    }
}