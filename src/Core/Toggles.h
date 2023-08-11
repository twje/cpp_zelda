#pragma once

#include <SFML/Graphics.hpp>

class CooldownToggle
{
public:
    CooldownToggle(uint16_t cooldownTime, bool defaultState);

    bool Update(const sf::Time &timestamp);
    bool Value() const { return mState; }
    void ToggleForCooldownTime(bool forceToggle = false);

private:
    bool TurnOffAfterCooldownTime(const sf::Time &timestamp);
    void TurnOn() { mState = !mDefaultState; }
    bool IsOn() { return mState == !mDefaultState; }

private:
    const uint16_t mCooldownTime;
    uint16_t mElapsedTime;
    const bool mDefaultState;
    bool mState;
};