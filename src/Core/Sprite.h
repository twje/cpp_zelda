#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

// Core
#include "Core/GameObject.h"

// Forward class declaration
class SpriteGroup;

class Sprite : public GameObject
{
    using SpriteGroupVector = std::vector<SpriteGroup *>;
    friend SpriteGroup;

public:
    Sprite(const sf::Texture &texture);
    Sprite();

    void Draw(sf::RenderWindow &window) override { window.draw(mSprite, GetTransform()); }
    void Kill();

    // Setters
    void SetTexture(const sf::Texture &texture, bool resetRect = false) { mSprite.setTexture(texture, resetRect); }
    void SetTextureRect(const sf::IntRect &rectangle) { mSprite.setTextureRect(rectangle); }

    // Getters
    sf::FloatRect GetLocalBounds() const override { return mSprite.getLocalBounds(); }

private:
    static const sf::Texture &GetPlaceholderTexture();

private:
    sf::Sprite mSprite;
    SpriteGroupVector mSpriteGroups;
};