#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

// Forward declaration
class Layer;

class LayerStack
{
public:
    void PushLayer(std::unique_ptr<Layer> layer);
    void Update(const sf::Time &timestamp);
    void Draw(sf::RenderWindow &window);

private:
    std::vector<std::unique_ptr<Layer>> mLayers;
};