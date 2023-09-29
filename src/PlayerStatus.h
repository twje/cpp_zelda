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
    MOVING, // Should this be "moving"?
    ATTACKING
};

class PlayerStatus {
private:
    PlayerDirection mPlayerDirection;
    PlayerActiveStatus mPlayerActiveStatus;
    std::string PlayerStatus::GetPlayerActoveStatusPostfix() const;

public:

    PlayerStatus(PlayerDirection playerDirection);
    PlayerDirection GetPlayerDirection() const;
    PlayerActiveStatus GetPlayerActiveStatus() const;
    void UpdatePlayerDirection(PlayerDirection playerDirection);
    void SetPlayerToIdle();
    void SetPlayerToAttacking();
    std::string PlayerStatus::GetDirectionAsString() const;
    std::string PlayerStatus::AsCompatString() const;
};



