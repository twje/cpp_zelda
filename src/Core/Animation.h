#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Core/Base.h"
#include "Core/AnimationSequence.h"

class Animation
{
    using SequenceMap = std::map<std::string, Scope<AnimationSequence>>;

public:
    Animation();

    void Update(const sf::Time &timestamp);
    void AddAnimationSequence(const std::string &sequenceID, Scope<AnimationSequence> sequence);
    void SetAnimationSequence(const std::string &sequenceID);
    SequenceFrame GetSequenceFrame() const { return mCurrentSequence->GetSequenceFrame(); }
    const std::string &GetSequenceID() const { return mSequenceID; }

private:
    std::string mSequenceID;
    SequenceMap mSequences;
    AnimationSequence *mCurrentSequence;
};