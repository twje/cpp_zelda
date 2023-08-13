#include "Core/Animation/FrameGenerators.h"

#include "Core/ResourceManager/TextureManager.h"

ListFrameGenerator::ListFrameGenerator(const std::vector<std::string> &frames)
    : mFrames(frames)
{
}

std::vector<std::shared_ptr<sf::Texture>> ListFrameGenerator::GetFrames() const
{
    std::vector<std::shared_ptr<sf::Texture>> result;
    for (const std::string &frame : mFrames)
    {
        result.emplace_back(TextureManager::GetInstance().GetResource(frame));
    }
    return result;
}
