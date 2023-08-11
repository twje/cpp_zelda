#include "Core/InflatableTextBox.h"

// Core
#include "Core/RectUtils.h"

InflatableTextBox::InflatableTextBox(const std::shared_ptr<GuiStyle> &style, float inflateX, float inflateY, const std::string &text)
    : mStyle(style),
      mInflateX(inflateX),
      mInflateY(inflateY),
      mText(style->GetFont(), text, style->GetTextSize())
{
    mText.setFillColor(mStyle->GetTextCol());
    SetBounds();
}

void InflatableTextBox::Draw(sf::RenderWindow &window)
{
    sf::RectangleShape backgroundRect;
    backgroundRect.setSize(sf::Vector2f(mBackground.width, mBackground.height));
    backgroundRect.setPosition(sf::Vector2f(mBackground.left, mBackground.top));
    backgroundRect.setFillColor(mStyle->GetBackgroundCol());
    backgroundRect.setOutlineColor(mStyle->GetBorderCol());
    backgroundRect.setOutlineThickness(mStyle->GetBorderSize());

    window.draw(backgroundRect, GetTransform());
    window.draw(mText, GetTransform());
}

void InflatableTextBox::SetText(const std::string &text)
{
    mText.setString(text);
    SetBounds();
}

void InflatableTextBox::SetBounds()
{
    // Global bounds for text is required for text layout - work around
    mText.setPosition(sf::Vector2f());
    sf::FloatRect textBounds = mText.getGlobalBounds();

    float borderSize = 2 * mStyle->GetBorderSize();
    float inflateWithBorderX = mInflateX + borderSize;
    float inflateWithBorderY = mInflateY + borderSize;

    mLocalBounds = InflateRect(textBounds, inflateWithBorderX, inflateWithBorderY);
    mLocalBounds.left = 0;
    mLocalBounds.top = 0;
    mBackground = InflateRect(mLocalBounds, -borderSize, -borderSize);
    mText.setPosition(GetRectCenter(mLocalBounds) - GetRectCenter(textBounds));
}
