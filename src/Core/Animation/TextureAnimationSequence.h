#pragma once

#include "Core/Animation/AnimationSequence.h"

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