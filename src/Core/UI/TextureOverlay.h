#pragma once

#include <memory>

// Core
#include "Core/GameObject.h"
#include "Core/GuiStyle.h"

class TextureOverlay : public GameObject
{
public:
    TextureOverlay(GroupManager& groupManager, const std::shared_ptr<GuiStyle> &style, std::shared_ptr<sf::Texture> texture, float width, float height);

    virtual void Draw(sf::RenderWindow &window);

    // Setters
    void SetActive(bool value) { mIsActive = value; }
    void TextureOverlay::SetTexture(const std::shared_ptr<sf::Texture> &texture);

    // Getters
    virtual sf::FloatRect GetLocalBounds() const { return mLocalBounds; }

private:
    void CenterSprite();

private:
    std::shared_ptr<GuiStyle> mStyle;
    std::shared_ptr<sf::Texture> mTexture;
    sf::Sprite mSprite;
    sf::FloatRect mLocalBounds;
    sf::FloatRect mBackground;
    bool mIsActive;
};