#include "Core/LayerStack.h"
#include "Core/Layer.h"

void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
{
    mLayers.emplace_back(std::move(layer));
}

void LayerStack::Update(const sf::Time &timestamp)
{
    for (auto &layer : mLayers)
    {
        layer->Update(timestamp);
    }
}

void LayerStack::Draw(sf::RenderWindow &window)
{
    for (auto &layer : mLayers)
    {
        layer->Draw(window);
    }
}

void LayerStack::OnWindowResize(sf::Vector2u size)
{
    for (auto &layer : mLayers)
    {
        layer->OnWindowResize(size);
    }
}