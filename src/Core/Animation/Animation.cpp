#include "Core/Animation/Animation.h"
#include "Core/Animation/TextureAnimationSequence.h"

#include <cassert>
#include <functional>
#include <memory>

#include <iostream>

Animation::Animation()
    : mCurrentSequence(nullptr)
{
}

void Animation::Update(const sf::Time &timestamp)
{
    assert(mCurrentSequence != nullptr); // Animation sequence is not set
    mCurrentSequence->Update(timestamp);
}

void Animation::AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence)
{
    assert(mSequences.find(sequenceID) == mSequences.end()); // Animation sequenceID already in use
    mSequences.emplace(sequenceID, std::move(sequence));
}

void Animation::SetAnimationSequence(const std::string &sequenceID)
{
    assert(mSequences.find(sequenceID) != mSequences.end()); // Invalid Animation sequenceID
    mSequenceID = sequenceID;
    mCurrentSequence = mSequences[mSequenceID].get();
    mCurrentSequence->Reset();
}

// ----------
// Serializer
// ----------
void Animation::LoadFromFile(const std::string &filePath)
{
    YAML::Node node = YAML::LoadFile(filePath);
    Deserialize(node);
}

void Animation::SaveToFile(const std::string &filePath)
{
    YAML::Emitter emitter;
    Serialize(emitter);
    std::ofstream file(filePath);
    file << emitter.c_str();
}

void Animation::Serialize(YAML::Emitter &emitter)
{
    emitter << YAML::BeginSeq;
    for (const auto &sequence : mSequences)
    {
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "key";
        emitter << YAML::Value << sequence.first;
        emitter << YAML::Key << "frames" << YAML::Value;
        sequence.second->Serialize(emitter);
        emitter << YAML::EndMap;
    }
    emitter << YAML::EndSeq;
}

void Animation::Deserialize(const YAML::Node &node)
{
    using AnimationSequenceFactory = std::unique_ptr<AnimationSequence> (*)(const YAML::Node &);

    AnimationSequenceFactory textureAnimationSequence = [](const YAML::Node &node) -> std::unique_ptr<AnimationSequence>
    {
        auto sequence = std::make_unique<TextureAnimationSequence>();
        sequence->Deserialize(node);
        return sequence;
    };

    std::map<std::string, AnimationSequenceFactory> animationSequenceFactories{
        {"TextureAnimationSequence", textureAnimationSequence}};

    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
    {
        std::string key = (*it)["key"].as<std::string>();
        for (const auto &frames : (*it)["frames"])
        {
            std::string sequenceType = frames.first.as<std::string>();
            std::unique_ptr<AnimationSequence> sequence = animationSequenceFactories[sequenceType](frames.second);
            AddAnimationSequence(key, std::move(sequence));
        }
    }
}
