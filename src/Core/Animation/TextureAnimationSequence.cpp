#include "Core/Animation/TextureAnimationSequence.h"
#include "Core/Animation/FrameGenerators.h"

TextureAnimationSequence::TextureAnimationSequence(uint8_t framesPerSecond, std::unique_ptr<FrameGenerator> frameGenerator)
    : AnimationSequence(framesPerSecond),
      mTextures(frameGenerator->GetFrames()),
      mFrameGenerator(std::move(frameGenerator))
{
}

SequenceFrame TextureAnimationSequence::GetTextureAtIndex(size_t index) const
{
    TexturePtr texturePtr = mTextures.at(index);
    sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(texturePtr->getSize()));
    return {texturePtr, textureRect};
}

void TextureAnimationSequence::Serialize()
{
    mFrameGenerator->Serialize();
}
