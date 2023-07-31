#include "Core/Toggles.h"

CooldownToggle::CooldownToggle(uint16_t cooldownTime, bool defaultState)
    : mCooldownTime(cooldownTime),
      mElapsedTime(0),
      mDefaultState(defaultState),
      mState(defaultState)
{
}

bool CooldownToggle::Update(const sf::Time &timestamp)
{
    if (IsOn())
    {
        return TurnOffAfterCooldownTime(timestamp);
    }
    return false;
}

void CooldownToggle::ToggleForCooldownTime(bool forceToggle)
{
    if (forceToggle || !IsOn())
    {
        TurnOn();
    }
}

bool CooldownToggle::TurnOffAfterCooldownTime(const sf::Time &timestamp)
{
    mElapsedTime += timestamp.asMilliseconds();
    if (mElapsedTime > mCooldownTime)
    {
        mState = mDefaultState;
        mElapsedTime = 0;
        return true;
    }
    return false;
}
