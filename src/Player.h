#pragma once

#include "Sprite.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

// Forward Declarations
class SpriteGroup;

class Player : public Sprite
{
private:
    static constexpr int SPEED = 5;

public:
    Player(sf::Vector2f position, const SpriteGroup &obstacleSprites);

public:
    void Update() override;
    void Input();
    void Move();
    void Collision(Direction direction);

    // Getters
    const sf::Texture &GetTexture() const override { return *mTexture; }
    Util::FloatRect GetRect() const override { return mRect; }
    sf::Vector2f GetDirection() { return mDirection; }

    // Debug
    void DrawHitbox(sf::RenderWindow &window)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(mHitbox.GetWidth(), mHitbox.GetHeight()));
        rectangle.setPosition(sf::Vector2f(mHitbox.GetX(), mHitbox.GetY()));
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(2);

        window.draw(rectangle);
    }

    virtual void DrawRect(sf::RenderWindow &window)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(mRect.GetWidth(), mRect.GetHeight()));
        rectangle.setPosition(sf::Vector2f(mRect.GetX(), mRect.GetY()));
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setOutlineThickness(2);

        window.draw(rectangle);
    };

private:
    bool IsMovingRight() { return mDirection.x > 0; }
    bool IsMovingLeft() { return mDirection.x < 0; }
    bool IsMovingUp() { return mDirection.y < 0; }
    bool IsMovingDown() { return mDirection.y > 0; }

private:
    std::unique_ptr<sf::Texture> mTexture;
    Util::FloatRect mRect;
    Util::FloatRect mHitbox;
    sf::Vector2f mDirection;
    const SpriteGroup &mObstacleSprites;
};