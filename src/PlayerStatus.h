#pragma once
#include <string>

enum class PlayerDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class PlayerActiveStatus {
    IDLE,
    MOVING,
    ATTACKING
};

class PlayerStatus {
private:
    PlayerDirection mPlayerDirection;
    PlayerActiveStatus mPlayerActiveStatus;
    std::string PlayerStatus::GetPlayerActiveStatusPostfix() const;

public:

    PlayerStatus(PlayerDirection playerDirection);
    PlayerDirection GetPlayerDirection() const { return mPlayerDirection; };
    PlayerActiveStatus GetPlayerActiveStatus() const { return mPlayerActiveStatus; };
    void UpdatePlayerDirection(PlayerDirection playerDirection);
    void SetPlayerToIdle() { mPlayerActiveStatus = PlayerActiveStatus::IDLE; };
    void SetPlayerToAttacking() { mPlayerActiveStatus = PlayerActiveStatus::ATTACKING; };
    std::string PlayerStatus::GetDirectionAsString() const;
    std::string PlayerStatus::AsCompatString() const;
};



