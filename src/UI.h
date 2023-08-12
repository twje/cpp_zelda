#pragma once

// Core
#include "Core/Layer.h"
#include "Core/RectUtils.h"
#include "Core/UI/InflatableTextBox.h"
#include "Core/UI/TextureOverlay.h"
#include "Core/UI/Bar.h"

// Forward declarations
class Level;
class Player;

class UI : public Layer
{
public:
    UI(const Level &level);

    virtual void Update(const sf::Time &timestamp);
    virtual void Draw(sf::RenderWindow &window);
    virtual void OnWindowResize(sf::Vector2u size);

private:
    const Level &mLevel;
    std::unique_ptr<Bar> mHealthBar;
    std::unique_ptr<Bar> mEnergyBar;
    std::unique_ptr<InflatableTextBox> mPlayerExp;
    std::unique_ptr<TextureOverlay> mWeaponOverlay;
    std::unique_ptr<TextureOverlay> mMagicOverlay;
    sf::View mView;
};