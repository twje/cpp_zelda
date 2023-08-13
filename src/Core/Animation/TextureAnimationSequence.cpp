#include "Core/Animation/TextureAnimationSequence.h"

TextureAnimationSequence::TextureAnimationSequence(uint8_t framesPerSecond, const TextureVector &textures)
    : AnimationSequence(framesPerSecond),
      mTextures(textures)
{
}

SequenceFrame TextureAnimationSequence::GetTextureAtIndex(size_t index) const
{
    TexturePtr texturePtr = mTextures.at(index);
    sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(texturePtr->getSize()));
    return {texturePtr, textureRect};
}