#pragma once

#include <vector>
#include <map>
#include <string>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "Core/Base.h"

class AnimationSequence
{
public:
    AnimationSequence(float framesPerSecond);

    void Update(const sf::Time &timestamp);
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
    TextureAnimationSequence(uint8_t framesPerSecond, const TextureVector &textures);

private:
    virtual const size_t GetFrameCount() const { return mTextures.size(); }
    const TexturePtr &GetTextureAtIndex(size_t index) const override { return mTextures.at(index); }

private:
    TextureVector mTextures;
};

class Animation
{
    using SequenceMap = std::map<std::string, Scope<AnimationSequence>>;

public:
    Animation();

    void Update(const sf::Time &timestamp);
    void AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence);
    void SetAnimationSequence(const std::string &sequenceID);
    const sf::Texture &GetSequenceFrame() const { return mCurrentSequence->GetSequenceFrame(); }
    const std::string &GetSequencesID() const { return mSequencesID; }

private:
    std::string mSequencesID;
    SequenceMap mSequences;
    AnimationSequence *mCurrentSequence;
};