#include "Core/UI/TextureOverlay.h"

// Core
#include "Core/RectUtils.h"

TextureOverlay::TextureOverlay(const std::shared_ptr<GuiStyle> &style, std::shared_ptr<sf::Texture> texture, float width, float height)
    : mStyle(style),
      mTexture(texture),
      mSprite(*texture),
      mIsActive(false)
{
    float borderSize = 2 * mStyle->GetBorderSize();
    mLocalBounds = sf::FloatRect(sf::Vector2f(), sf::Vector2f(width, height));
    mBackground = InflateRect(mLocalBounds, -borderSize, -borderSize);
    CenterSprite();
}

void TextureOverlay::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape backgroundRect;
    backgroundRect.setSize(sf::Vector2f(mBackground.width, mBackground.height));
    backgroundRect.setPosition(sf::Vector2f(mBackground.left, mBackground.top));
    backgroundRect.setFillColor(mStyle->GetBackgroundCol());
    backgroundRect.setOutlineColor(mIsActive ? mStyle->GetBorderHighlightCol() : mStyle->GetBorderCol());
    backgroundRect.setOutlineThickness(mStyle->GetBorderSize());

    window.draw(backgroundRect, GetTransform());
    window.draw(mSprite, GetTransform());
}

void TextureOverlay::SetTexture(const std::shared_ptr<sf::Texture> &texture)
{
    mTexture = texture;
    mSprite.setTexture(*mTexture, true);
    CenterSprite();
}

void TextureOverlay::CenterSprite()
{
    sf::FloatRect spriteBounds = mSprite.getLocalBounds();
    mSprite.setPosition(GetRectCenter(mLocalBounds) - GetRectCenter(spriteBounds));
}