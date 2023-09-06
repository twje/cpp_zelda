#include "UI.h"
#include "Level.h"

// Core
#include "Core/ResourceManager/GUIStyleManager.h"
#include "Core/ResourceManager/TextureManager.h"

// Game
#include "Settings.h"
#include "Weapon.h"

namespace Factory
{
    static std::unique_ptr<Bar> CreateHealthBar(GroupManager& groupManager, const Player &player)
    {
        return std::make_unique<Bar>(
            groupManager,
            GUIStyleManager::GetInstance().GetResource("health_bar"),
            HEALTH_BAR_WIDTH,
            BAR_HEIGHT,
            player.GetHealth(),
            PLAYER_STATS.at("health"));
    }

    static std::unique_ptr<Bar> CreateEnergyBar(GroupManager& groupManager, const Player &player)
    {
        return std::make_unique<Bar>(
            groupManager,
            GUIStyleManager::GetInstance().GetResource("energy_bar"),
            ENERGY_BAR_WIDTH,
            BAR_HEIGHT,
            player.GetEnergy(),
            PLAYER_STATS.at("energy"));
    }

    static std::unique_ptr<InflatableTextBox> CreateEXPTextbox(GroupManager& groupManager, const Player &player)
    {
        return std::make_unique<InflatableTextBox>(
            groupManager,
            GUIStyleManager::GetInstance().GetResource("player_exp_textbox"),
            20.0f,
            20.0f,
            std::to_string(player.GetEXP()));
    }

    static std::unique_ptr<TextureOverlay> CreateWeaponOverlay(GroupManager& groupManager, const Player &player)
    {
        return std::make_unique<TextureOverlay>(
            groupManager,
            GUIStyleManager::GetInstance().GetResource("overlay"),
            player.GetWeaponIconTexture(),
            ITEM_BOX_SIZE,
            ITEM_BOX_SIZE);
    }

    static std::unique_ptr<TextureOverlay> CreateMagicOverlay(GroupManager& groupManager, const Player &player)
    {
        return std::make_unique<TextureOverlay>(
            groupManager,
            GUIStyleManager::GetInstance().GetResource("overlay"),
            player.GetMagicIconTexture(),
            ITEM_BOX_SIZE,
            ITEM_BOX_SIZE);
    }
}

UI::UI(GroupManager& groupManager, const Level &level)
    : mLevel(level),
      mHealthBar(Factory::CreateHealthBar(groupManager, level.GetPlayer())),
      mEnergyBar(Factory::CreateEnergyBar(groupManager, level.GetPlayer())),
      mPlayerExp(Factory::CreateEXPTextbox(groupManager, level.GetPlayer())),
      mWeaponOverlay(Factory::CreateWeaponOverlay(groupManager, level.GetPlayer())),
      mMagicOverlay(Factory::CreateMagicOverlay(groupManager, level.GetPlayer()))
{
}

void UI::Update(const sf::Time &timestamp)
{
    const Player &player = mLevel.GetPlayer();
    if (player.CanSwitchWeapon())
    {
        mWeaponOverlay->SetActive(false);
    }
    else
    {
        mWeaponOverlay->SetActive(true);
    }

    if (player.CanSwitchMagic())
    {
        mMagicOverlay->SetActive(false);
    }
    else
    {
        mMagicOverlay->SetActive(true);
    }

    mWeaponOverlay->SetTexture(player.GetWeaponIconTexture());
    mMagicOverlay->SetTexture(player.GetMagicIconTexture());
    mHealthBar->SetCurrentValue(player.GetHealth());
    mEnergyBar->SetCurrentValue(player.GetEnergy());
    mPlayerExp->SetText(std::to_string(player.GetEXP()));
}

void UI::Draw(sf::RenderWindow &window)
{
    window.setView(mView);

    mHealthBar->Draw(window);
    mEnergyBar->Draw(window);
    mPlayerExp->Draw(window);
    mWeaponOverlay->Draw(window);
    mMagicOverlay->Draw(window);
}

void UI::OnWindowResize(sf::Vector2u size)
{
    mView.setSize(sf::Vector2f(size));
    mView.setCenter(sf::Vector2f(size) / 2.f);

    mHealthBar->SetPosition(sf::Vector2f(10, 10));
    mEnergyBar->SetPosition(sf::Vector2f(10, 34));
    mPlayerExp->SetPosition(sf::Vector2f(size) - mPlayerExp->GetSize() - sf::Vector2f(10, 10));
    mWeaponOverlay->SetPosition(sf::Vector2f(10, 630));
    mMagicOverlay->SetPosition(sf::Vector2f(80, 635));
}
