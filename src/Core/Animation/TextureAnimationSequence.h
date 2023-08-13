#pragma once

#include "Core/Animation/AnimationSequence.h"

// Forward declarations
class FrameGenerator;

class TextureAnimationSequence : public AnimationSequence
{
public:
    TextureAnimationSequence(uint8_t framesPerSecond, std::unique_ptr<FrameGenerator> frameGenerator);

    void Serialize() override;

private:
    virtual const size_t GetFrameCount() const { return mTextures.size(); }
    SequenceFrame GetTextureAtIndex(size_t index) const override;

private:
    TextureVector mTextures;
    std::unique_ptr<FrameGenerator> mFrameGenerator;
};
