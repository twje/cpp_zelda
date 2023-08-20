#pragma once

#include <yaml-cpp/yaml.h>

class Serializable
{
public:
    virtual void Serialize(YAML::Emitter &emitter) = 0;
    virtual void Deserialize(const YAML::Node &node) = 0;
};