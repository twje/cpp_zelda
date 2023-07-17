#pragma once

#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "Constants.h"

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
    void DrawHitbox(sf::RenderWindow &window) override;
    void DrawRect(sf::RenderWindow &window) override;

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