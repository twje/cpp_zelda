#pragma once

#include "Core/Animation/AnimationSequence.h"

class TextureAnimationSequence : public AnimationSequence
{
    using TexturePair = std::pair<std::string, std::shared_ptr<sf::Texture>>;

public:
    TextureAnimationSequence();
    TextureAnimationSequence(uint8_t framesPerSecond, std::vector<std::string> frameIDs);
    void AddFrame(std::string frameID);

    // Serializable
    void Serialize(YAML::Emitter &emitter) override;
    void Deserialize(const YAML::Node &node) override;

private:
    virtual const size_t GetFrameCount() const { return mFrames.size(); }
    SequenceFrame GetTextureAtIndex(size_t index) const override;

private:
    std::vector<TexturePair> mFrames;
};
