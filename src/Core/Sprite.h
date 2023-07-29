#pragma once

#include <SFML/Graphics.hpp>

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite(const sf::Texture &texture)
        : mSprite(texture)
    {
    }

    Sprite(const sf::IntRect &textureRect)
        : mSprite(mDefaultTexture)
    {
        mSprite.setTextureRect(textureRect);
    }

    virtual void Update(const sf::Time &timestamp){};
    virtual void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    // Setters
    void setTexture(const sf::Texture &texture) { mSprite.setTexture(texture); }
    void setTextureRect(const sf::IntRect &rectangle) { mSprite.setTextureRect(rectangle); }

    // Getters
    sf::Vector2f GetSize() const { return sf::Vector2f(mSprite.getLocalBounds().width, mSprite.getLocalBounds().height); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetBoundingBox() const { return getTransform().transformRect(mSprite.getLocalBounds()); }
    virtual sf::FloatRect GetHitbox() const { return GetBoundingBox(); }

private:
    sf::Texture mDefaultTexture;
    sf::Sprite mSprite;
};
