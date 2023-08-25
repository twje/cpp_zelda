#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// Core
#include "Core/Base.h"
#include "Core/Serializable.h"
#include "Core/Animation/AnimationSequence.h"

class Animation : public Serializable
{
    using SequenceMap = std::map<std::string, Scope<AnimationSequence>>;

public:
    Animation();

    void Update(const sf::Time &timestamp);
    void AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence);
    void SetAnimationSequence(const std::string &sequenceID);
    SequenceFrame GetSequenceFrame() const { return mCurrentSequence->GetSequenceFrame(); }
    const std::string &GetSequenceID() const { return mSequenceID; }
    bool IsAllFramesPlayed() { return mCurrentSequence->IsAllFramesPlayed(); }

    // Serializable
    void LoadFromFile(const std::string &filePath);
    void SaveToFile(const std::string &filePath);
    void Serialize(YAML::Emitter &emitter) override;
    void Deserialize(const YAML::Node &node) override;

private:
    std::string mSequenceID;
    SequenceMap mSequences;
    AnimationSequence *mCurrentSequence;
};
