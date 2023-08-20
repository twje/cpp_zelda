#include "Core/Animation/TextureAnimationSequence.h"
#include "Core/ResourceManager/TextureManager.h"

#include <iostream>

TextureAnimationSequence::TextureAnimationSequence()
    : AnimationSequence()
{
}

TextureAnimationSequence::TextureAnimationSequence(uint8_t framesPerSecond, std::vector<std::string> frameIDs)
    : AnimationSequence(framesPerSecond)
{
    for (const std::string &frameID : frameIDs)
    {
        AddFrame(frameID);
    }
}

void TextureAnimationSequence::AddFrame(std::string frameID)
{
    auto frame = std::make_pair(frameID, TextureManager::GetInstance().GetResource(frameID));
    mFrames.emplace_back(frame);
}

SequenceFrame TextureAnimationSequence::GetTextureAtIndex(size_t index) const
{
    auto frame = mFrames.at(index);
    sf::IntRect textureRect(sf::Vector2i(), sf::Vector2i(frame.second->getSize()));
    return {frame.second, textureRect};
}

// ------------
// Serializable
// ------------
void TextureAnimationSequence::Serialize(YAML::Emitter &emitter)
{
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "TextureAnimationSequence" << YAML::Value;
    emitter << YAML::BeginMap;
    AnimationSequence::Serialize(emitter);
    emitter << YAML::Key << "textures" << YAML::Value;
    emitter << YAML::BeginSeq;
    for (const auto &frame : mFrames)
    {
        emitter << frame.first;
    }
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
}

void TextureAnimationSequence::Deserialize(const YAML::Node &node)
{
    AnimationSequence::Deserialize(node);
    auto &instance = TextureManager::GetInstance();
    for (const auto &frameID : node["textures"])
    {
        AddFrame(frameID.as<std::string>());
    }
}