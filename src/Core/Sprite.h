#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

// Forward class declaration
class SpriteGroup;

class Sprite : public sf::Sprite
{
    using SpriteGroupVector = std::vector<SpriteGroup *>;
    friend SpriteGroup;

    static const sf::Texture PLACEHOLDER_TEXTURE;

public:
    Sprite(const sf::Texture &texture)
        : sf::Sprite(texture)
    {
    }

    Sprite()
        : sf::Sprite(Sprite::PLACEHOLDER_TEXTURE)
    {
    }

    virtual void Update(const sf::Time &timestamp){};
    void Kill();

    // Getters
    sf::Vector2f GetSize() const { return getGlobalBounds().getSize(); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetGlobalBounds() const { return getGlobalBounds(); }
    sf::FloatRect GetLocalBounds() const { return getLocalBounds(); }
    virtual sf::FloatRect GetHitbox() const { return getGlobalBounds(); }

private:
    SpriteGroupVector mSpriteGroups;
};
