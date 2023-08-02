#pragma once

#include <SFML/Graphics.hpp>

// Forward class declaration
class SpriteGroup;

using SpriteGroupVector = std::vector<SpriteGroup *>;

class GameObject : private sf::Transformable
{
    friend SpriteGroup;

public:
    // Hooks
    virtual void Draw(sf::RenderWindow &window) {}
    virtual void Update(const sf::Time &timestamp) {}
    virtual sf::FloatRect GetLocalBounds() const { return sf::FloatRect(); }
    virtual sf::FloatRect GetHitbox() const { return GetGlobalBounds(); }

    // Setters
    void SetPosition(const sf::Vector2f &position) { setPosition(position); }
    void Move(const sf::Vector2f &offset) { move(offset); }

    // Getters
    sf::Vector2f GetSize() const { return GetGlobalBounds().getSize(); }
    sf::Vector2f GetCenter() const { return getPosition() + 0.5f * GetSize(); }
    sf::FloatRect GetGlobalBounds() const { return getTransform().transformRect(GetLocalBounds()); }
    const sf::Transform &GetTransform() const { return getTransform(); };

    // Resource management
    void Kill();

private:
    virtual void RegisterGroup(SpriteGroup *group) { mSpriteGroups.emplace_back(group); };

private:
    SpriteGroupVector mSpriteGroups;
};