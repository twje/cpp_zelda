#pragma once

#include <SFML/Graphics.hpp>

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite(const sf::Texture &texture)
        : mSprite(texture)
    {
    }

    Sprite()
        : mSprite(mPlaceholderTexture)
    {
    }

    virtual void Update(const sf::Time &timestamp){};
    virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
    void Kill()
    {
        // implement
    }

    // Setters
    void setTexture(const sf::Texture &texture, bool setDefaultTextureRect = false);
    void setTextureRect(const sf::IntRect &rectangle) { mSprite.setTextureRect(rectangle); }

    // Getters
    sf::Vector2f GetSize() const { return sf::Vector2f(mSprite.getLocalBounds().width, mSprite.getLocalBounds().height); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetGlobalBounds() const { return getTransform().transformRect(mSprite.getLocalBounds()); }
    sf::FloatRect GetLocalBounds() const { return mSprite.getLocalBounds(); }
    virtual sf::FloatRect GetHitbox() const { return GetGlobalBounds(); }

private:
    sf::Texture mPlaceholderTexture;
    sf::Sprite mSprite;
};
