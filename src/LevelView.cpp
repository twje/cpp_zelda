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
    mView.setCenter(player.GetCenter());
    mWindow.setView(mView);

    mSortedSpriteGroup = mLevel.GetVisibleSpriteGroup();
    mSortedSpriteGroup.YSortSprites();

    // Draw floor
    sf::Sprite floorSprite(mLevel.GetFloorTexture());
    floorSprite.setPosition(sf::Vector2f());
    window.draw(floorSprite);

    // Draw Tiles
    for (const auto &sprite : mSortedSpriteGroup.GetSprites())
    {
        window.draw(*sprite);
    }

    DebugWorldDraw(window);
    window.setView(window.getDefaultView());
    DebugHUDDraw(window);
}

void LevelView::DebugWorldDraw(sf::RenderWindow &window)
{
#ifdef DEBUG_BUILD
    DebugDrawPlayer(window);
    DebugHitbox(window);
#endif
}

void LevelView::DebugDrawPlayer(sf::RenderWindow &window)
{
    const Player &player = mLevel.GetPlayer();
    DrawTransparentRectangle(window, player.GetGlobalBounds(), sf::Color::White, 2);
}

void LevelView::DebugHitbox(sf::RenderWindow &window)
{
    for (const auto &sprite : mSortedSpriteGroup.GetSprites())
    {
        DrawTransparentRectangle(window, sprite->GetHitbox(), sf::Color::Red, 2);
    }
}

void LevelView::DebugHUDDraw(sf::RenderWindow &window)
{
#ifdef DEBUG_BUILD
    const Player &player = mLevel.GetPlayer();
    DrawDebugString(window, player.GetAnimationGetSequenceID());
#endif
}