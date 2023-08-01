#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

// Core
#include "Core/GameObject.h"

// Forward class declaration
class SpriteGroup;

class Sprite : public GameObject, public sf::Transformable
{
    using SpriteGroupVector = std::vector<SpriteGroup *>;
    friend SpriteGroup;

public:
    Sprite(const sf::Texture &texture);
    Sprite();

    void Draw(sf::RenderWindow &window) override { window.draw(mSprite, getTransform()); }
    void Kill();

    // Setters
    void SetTexture(const sf::Texture &texture, bool resetRect = false) { mSprite.setTexture(texture, resetRect); }
    void SetTextureRect(const sf::IntRect &rectangle) { mSprite.setTextureRect(rectangle); }
    void SetPosition(const sf::Vector2f &position) { setPosition(position); }
    void Move(const sf::Vector2f &offset) { move(offset); }

    // Getters
    sf::Vector2f GetSize() const { return GetGlobalBounds().getSize(); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetGlobalBounds() const { return getTransform().transformRect(mSprite.getLocalBounds()); }
    sf::FloatRect GetLocalBounds() const { return mSprite.getLocalBounds(); }
    virtual sf::FloatRect GetHitbox() const { return GetGlobalBounds(); }

private:
    static const sf::Texture &GetPlaceholderTexture();

private:
    sf::Sprite mSprite;
    SpriteGroupVector mSpriteGroups;
};