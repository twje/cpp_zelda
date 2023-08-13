#pragma once

#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

class FrameGenerator
{
public:
    virtual std::vector<std::shared_ptr<sf::Texture>> GetFrames() const = 0;
    virtual void Serialize() = 0;
};

class ListFrameGenerator : public FrameGenerator
{
public:
    ListFrameGenerator() = default;
    ListFrameGenerator(const std::vector<std::string> &frames);

    std::vector<std::shared_ptr<sf::Texture>> GetFrames() const override;

    void Serialize() override
    {
        ;
    }

private:
    std::vector<std::string> mFrames;
};
