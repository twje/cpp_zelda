#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "Core/Base.h"
#include "Core/ResourceManager/TextureManager.h"

struct SequenceFrame
{
    TexturePtr mTexture;
    sf::IntRect mTextureRect;
};

class AnimationSequence
{
public:
    AnimationSequence(float framesPerSecond);

    void Update(const sf::Time &timestamp);
    SequenceFrame GetSequenceFrame() const { return GetTextureAtIndex(mFrameIndex); }
    void Reset() { mFrameIndex = 0; }

protected:
    virtual const size_t GetFrameCount() const = 0;
    virtual SequenceFrame GetTextureAtIndex(size_t index) const = 0;

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
    SequenceFrame GetTextureAtIndex(size_t index) const override;

private:
    TextureVector mTextures;
};