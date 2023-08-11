#include "Bar.h"

Bar::Bar(const std::shared_ptr<GuiStyle> &style, uint16_t width, uint16_t height, float currentValue, float maxValue)
    : mStyle(style),
      mLocalBounds(sf::FloatRect(sf::Vector2f(), sf::Vector2f(width, height))),
      mBackground(InflateRect(mLocalBounds, -style->GetBorderSize() * 2, -style->GetBorderSize() * 2)),
      mForeground(mBackground),
      mCurrentValue(currentValue),
      mMaxValue(maxValue)
{
    SetCurrentValue(mCurrentValue);
}

void Bar::SetCurrentValue(float value)
{
    mCurrentValue = value;
    mForeground.width = mBackground.width * (mCurrentValue / mMaxValue);
}

void Bar::SetCurrentValuePercent(float value)
{
    mCurrentValue = value;
    mForeground.width = mBackground.width * value;
}

void Bar::Draw(sf::RenderWindow &window)
{
    // Background
    sf::RectangleShape backgroundRect;
    backgroundRect.setSize(sf::Vector2f(mBackground.width, mBackground.height));
    backgroundRect.setPosition(sf::Vector2f(mBackground.left, mBackground.top));
    backgroundRect.setFillColor(mStyle->GetBackgroundCol());
    backgroundRect.setOutlineColor(mStyle->GetBorderCol());
    backgroundRect.setOutlineThickness(mStyle->GetBorderSize());

    // Foreground
    sf::RectangleShape foregroundRect;
    foregroundRect.setSize(sf::Vector2f(mForeground.width, mForeground.height));
    foregroundRect.setPosition(sf::Vector2f(mForeground.left, mForeground.top));
    foregroundRect.setFillColor(mStyle->GetBodyCol());

    window.draw(backgroundRect, GetTransform());
    window.draw(foregroundRect, GetTransform());
}