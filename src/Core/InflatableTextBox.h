#pragma once

#include <memory>
#include <string>

// Core
#include "Core/GameObject.h"
#include "Core/GuiStyle.h"

class InflatableTextBox : public GameObject
{
public:
    InflatableTextBox(const std::shared_ptr<GuiStyle> &style, float inflateX, float inflateY, const std::string &text);

    virtual void Draw(sf::RenderWindow &window);

    // Setters
    void SetText(const std::string &text);

    // Getters
    virtual sf::FloatRect GetLocalBounds() const { return mLocalBounds; }

private:
    void SetBounds();

private:
    std::shared_ptr<GuiStyle> mStyle;
    sf::Text mText;
    sf::FloatRect mLocalBounds;
    sf::FloatRect mBackground;
    float mInflateX;
    float mInflateY;
};