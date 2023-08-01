#include "Core/Application.h"

#include <memory>

#include <SFML/Graphics.hpp>

// Core
#include "Core/LayerStack.h"
#include "Core/Layer.h"

Application::Application(uint16_t width, uint16_t height, uint16_t bpp, std::string caption)
    : mWindow(sf::VideoMode(sf::Vector2u(width, height), bpp), caption)
{
}

void Application::Run()
{
    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }

        mWindow.clear();
        mLayers.Update(mClock.restart());
        mLayers.Draw(mWindow);
        mWindow.display();
    }
}

void Application::PushLayer(std::unique_ptr<Layer> layer)
{
    mLayers.PushLayer(std::move(layer));
}
