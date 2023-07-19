#include "LevelView.h"
#include "Level.h"
#include "Player.h"

LevelView::LevelView(const Level &level)
    : mLevel(level)
{
}

void LevelView::Draw(sf::RenderWindow &window)
{
    const Player &player = mLevel.GetPlayer();

    SpriteGroup sortedSpriteGroup = mLevel.GetVisibleSpriteGroup();
    sortedSpriteGroup.YSortSprites();

    sf::Vector2f offset(player.GetRect().GetCenterX() - window.getSize().x / 2,
                        player.GetRect().GetCenterY() - window.getSize().y / 2);

    for (const auto &internalSprite : sortedSpriteGroup.GetSprites())
    {
        sf::Vector2f offsetPos(internalSprite->GetRect().GetLeft() - offset.x,
                               internalSprite->GetRect().GetTop() - offset.y);

        sf::Sprite sprite(internalSprite->GetTexture());
        sprite.setPosition(offsetPos);
        window.draw(sprite);
    }
}