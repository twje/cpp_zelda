#pragma once

#include <SFML/Graphics.hpp>

class CooldownToggle
{
public:
    CooldownToggle(uint16_t cooldownTime, bool defaultState);

    bool Update(const sf::Time &timestamp);
    bool Value() { return mState; }
    void TryToggleValue();

private:
    bool TurnOffAfterCooldown(const sf::Time &timestamp);
    void TurnOff();
    void TurnOn() { mState = !mDefaultState; }
    bool IsOn() { return mState == !mDefaultState; }

private:
    const uint16_t mCooldownTime;
    uint16_t mElapsedTime;
    const bool mDefaultState;
    bool mState;
};