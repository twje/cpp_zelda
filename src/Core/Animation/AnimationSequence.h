#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>

#include "Core/Base.h"
#include "Core/Serializable.h"
#include "Core/ResourceManager/TextureManager.h"

struct SequenceFrame
{
    TexturePtr mTexture;
    sf::IntRect mTextureRect;
};

class AnimationSequence : public Serializable
{
public:
    AnimationSequence() = default;
    AnimationSequence(float framesPerSecond);

    void Update(const sf::Time &timestamp);
    SequenceFrame GetSequenceFrame() const { return GetTextureAtIndex(mFrameIndex); }
    void Reset();

    // Serializable
    void Serialize(YAML::Emitter &emitter) override;
    void Deserialize(const YAML::Node &node) override;

protected:
    virtual const size_t
    GetFrameCount() const = 0;
    virtual SequenceFrame GetTextureAtIndex(size_t index) const = 0;

private:
    uint16_t mFramesPerSecond{0};
    float mFrameTime{0.0f};
    float mElapsedTime{0.0f};
    size_t mFrameIndex{0};
};
