#pragma once

#include <SFML/Graphics.hpp>

#include "Core/GroupManager.h"

// TEMP CODE
class Player;
class GameObject;

class GameObject : private sf::Transformable
{
    friend Group;

public:
    GameObject(GroupManager& groupManager);
    virtual ~GameObject() = default;

    bool CollidesWith(const GameObject &other);

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
    sf::Vector2f GetPosition() { return getPosition(); }

    // Resource management
    void Kill();
    bool IsMarkedForDeletion() { return mIsMarkedForDeletion; }

private:
    GroupManager& mGroupManager;        
    bool mIsMarkedForDeletion{ false };
};