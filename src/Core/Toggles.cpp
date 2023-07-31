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
        return TurnOffAfterCooldown(timestamp);
    }
    return false;
}

void CooldownToggle::TryToggleValue()
{
    if (!IsOn())
    {
        TurnOn();
    }
}

bool CooldownToggle::TurnOffAfterCooldown(const sf::Time &timestamp)
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
