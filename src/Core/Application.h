#pragma once

#include <SFML/Graphics.hpp>

// Core
#include "Core/LayerStack.h"

class Application
{
public:
    Application(uint16_t width, uint16_t height, uint16_t bpp, std::string caption);

    virtual void Setup() {}
    void Run();
    void PushLayer(std::unique_ptr<Layer> layer);
    sf::RenderWindow &GetRenderWindow() { return mWindow; }

private:
    sf::Clock mClock;
    sf::RenderWindow mWindow;
    LayerStack mLayers;
};