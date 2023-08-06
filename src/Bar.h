
#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/GameObject.h"
#include "Core/GuiStyle.h"
#include "Core/RectUtils.h"

class Bar : public GameObject
{
public:
    Bar(const GuiStyle &style, uint16_t width, uint16_t height, float currentValue, float maxValue);

    virtual void Draw(sf::RenderWindow &window);

    // Setters
    void SetCurrentValue(float value);
    void SetCurrentValuePercent(float value);

    // Getters
    virtual sf::FloatRect GetLocalBounds() const { return mLocalBounds; }

private:
    GuiStyle mStyle;
    sf::FloatRect mLocalBounds;
    sf::FloatRect mBackground;
    sf::FloatRect mForeground;
    float mCurrentValue;
    float mMaxValue;
};