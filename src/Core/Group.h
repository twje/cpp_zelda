#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include <Core/GameObject.h>
#include <iostream>

// Type Alias
using GameObjectVector = std::vector<std::shared_ptr<GameObject>>;

// Iterator
class GroupIterator
{
public:
    GroupIterator(typename GameObjectVector::iterator iter, typename GameObjectVector::iterator end)
        : mIter(iter), mEnd(end)
    {
        AdvanceIteratorToNextAliveObject();
    }

    auto& operator*()
    {
        return *mIter;
    }

    GroupIterator& operator++()
    {
        ++mIter;
        AdvanceIteratorToNextAliveObject();
        return *this;
    }

    bool operator!=(const GroupIterator& other) const
    {
        return mIter != other.mIter;
    }

private:
    void AdvanceIteratorToNextAliveObject()
    {
        while (mIter != mEnd && !(*mIter)->IsAlive()) {
            ++mIter;
        }
    }

private:
    GameObjectVector::iterator mIter;
    GameObjectVector::iterator mEnd;
};

class Group
{
public:    
    void Group::Add(std::shared_ptr<GameObject> sprite);
    const GameObjectVector &GetGameObjects() const { return mGameObjects; }
    GameObjectVector &GetGameObjects() { return mGameObjects; }
    void YSortGameObjects();
    void Update(const sf::Time &timestamp);
    void RemoveSprite(const GameObject &sprite);

    // Iterator
    GroupIterator begin() { return GroupIterator(mGameObjects.begin(), mGameObjects.end()); }
    GroupIterator end() { return GroupIterator(mGameObjects.end(), mGameObjects.end()); }

private:
    GameObjectVector mGameObjects;
};
