#pragma once

#include <vector>
#include <map>
#include <string>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "Core/Base.h"
#include <iostream>
class AnimationSequence
{
public:
    AnimationSequence(float framesPerSecond)
        : mFrameTime(1.0f / framesPerSecond),
          mElapsedTime(0),
          mFrameIndex(0)
    {
    }

    void Update(const sf::Time &timestamp)
    {
        std::cout << timestamp.asSeconds() << std::endl;
        mElapsedTime += timestamp.asSeconds();
        if (mElapsedTime > mFrameTime)
        {
            mElapsedTime -= mFrameTime;
            mFrameIndex = (mFrameIndex + 1) % GetFrameCount();
        }
    }

    const sf::Texture &GetSequenceFrame() const { return *GetTextureAtIndex(mFrameIndex); }
    void Reset() { mFrameIndex = 0; }

protected:
    virtual const size_t GetFrameCount() const = 0;
    virtual const TexturePtr &GetTextureAtIndex(size_t index) const = 0;

private:
    float mFrameTime;
    float mElapsedTime;
    size_t mFrameIndex;
};

class TextureAnimationSequence : public AnimationSequence
{
public:
    TextureAnimationSequence(uint8_t framesPerSecond, const TextureVector &textures)
        : AnimationSequence(framesPerSecond),
          mTextures(textures)
    {
    }

private:
    virtual const size_t GetFrameCount() const
    {
        return mTextures.size();
    }

    const TexturePtr &GetTextureAtIndex(size_t index) const override
    {
        return mTextures.at(index);
    }

private:
    TextureVector mTextures;
};

class Animation
{
    using SequenceMap = std::map<std::string, Scope<AnimationSequence>>;

public:
    Animation()
        : mCurrentSequence(nullptr)
    {
    }

    void Update(const sf::Time &timestamp)
    {
        assert(mCurrentSequence != nullptr); // Animation sequence is not set
        mCurrentSequence->Update(timestamp);
    }

    void AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence)
    {
        assert(mSequences.find(sequenceID) == mSequences.end()); // Animation sequenceID already in use
        mSequences.emplace(sequenceID, std::move(sequence));
    }

    void SetAnimationSequence(const std::string &sequenceID)
    {
        assert(mSequences.find(sequenceID) != mSequences.end()); // Invalid Animation sequenceID
        mSequencesID = sequenceID;
        mCurrentSequence = mSequences[mSequencesID].get();
        mCurrentSequence->Reset();
    }

    const sf::Texture &GetSequenceFrame() const { return mCurrentSequence->GetSequenceFrame(); }
    const std::string &GetSequencesID() const { return mSequencesID; }

private:
    std::string mSequencesID;
    SequenceMap mSequences;
    AnimationSequence *mCurrentSequence;
};