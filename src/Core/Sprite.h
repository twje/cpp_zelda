#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

// Core
#include "Core/GameObject.h"

class Sprite : public GameObject
{
public:
    Sprite(const std::shared_ptr<sf::Texture> &texture);
    Sprite();

    void Draw(sf::RenderWindow &window) override { window.draw(mSprite, GetTransform()); }

    // Setters
    void SetTexture(const std::shared_ptr<sf::Texture> &texture, bool resetRect = false);
    void SetTextureRect(const sf::IntRect &rectangle) { mSprite.setTextureRect(rectangle); }
    void SetAlpha(uint8_t value);

    // Getters
    sf::FloatRect GetLocalBounds() const override { return mSprite.getLocalBounds(); }

private:
    static const sf::Texture &GetPlaceholderTexture();

private:
    sf::Sprite mSprite;
    std::shared_ptr<sf::Texture> mTexture;
};