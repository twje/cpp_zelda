#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Component.h"

// Forward class declaration
class Group;

using GroupVector = std::vector<Group *>;

class GameObject : private sf::Transformable
{
    friend Group;

public:
    bool CollidesWith(const GameObject &other);

    // Components
    void AddComponent(std::unique_ptr<Component> component);

    template <typename ComponentType>
    ComponentType *GetComponent();

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
    void RegisterGroup(Group *group) { mGroups.emplace_back(group); };

private:
    GroupVector mGroups;
    std::vector<std::unique_ptr<Component>> mCmponents;
};

// -------------------------------
// Template Method Implementations
// -------------------------------
template <typename ComponentType>
ComponentType *GameObject::GetComponent()
{
    for (auto &component : mCmponents)
    {
        if (auto typedComponent = dynamic_cast<ComponentType *>(component.get()))
        {
            return typedComponent;
        }
    }
    return nullptr;
}