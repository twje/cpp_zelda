#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

// Forward class declaration
class SpriteGroup;

class Sprite : public sf::Sprite
{
    using SpriteGroupVector = std::vector<SpriteGroup *>;
    friend SpriteGroup;

public:
    Sprite(const sf::Texture &texture)
        : sf::Sprite(texture)
    {
    }

    Sprite()
        : sf::Sprite(GetPlaceholderTexture())
    {
    }

    virtual void Update(const sf::Time &timestamp){};
    void Kill();

    // Setters
    void SetTexture(const sf::Texture &texture, bool resetRect = false) { setTexture(texture, resetRect); }
    void SetTextureRect(const sf::IntRect &rectangle) { setTextureRect(rectangle); }

    // Getters
    sf::Vector2f GetSize() const { return getGlobalBounds().getSize(); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetGlobalBounds() const { return getGlobalBounds(); }
    sf::FloatRect GetLocalBounds() const { return getLocalBounds(); }
    virtual sf::FloatRect GetHitbox() const { return getGlobalBounds(); }

private:
    static const sf::Texture &GetPlaceholderTexture();

private:
    SpriteGroupVector mSpriteGroups;
};
