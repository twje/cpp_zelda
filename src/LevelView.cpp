#include "LevelView.h"
#include "Level.h"
#include "Player.h"

LevelView::LevelView(const Level &level)
    : mLevel(level)
{
}

void LevelView::Draw(sf::RenderWindow &window)
{
    for (const auto &internalSprite : mLevel.GetVisibleSpriteGroup().GetSprites())
    {
        Util::FloatRect rect = internalSprite->GetRect();
        sf::Sprite sprite(internalSprite->GetTexture());
        sprite.setPosition(sf::Vector2f(rect.GetX(), rect.GetY()));
        window.draw(sprite);
    }

    const Player &player = mLevel.GetPlayer();
    Debug(window, ToString(player.GetDirection()));
    player.DebugDraw(window);
}