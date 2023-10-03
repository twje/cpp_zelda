#include "PlayerStatus.h"
#include <stdexcept>

PlayerStatus::PlayerStatus(PlayerDirection playerDirection) :
	mPlayerDirection(playerDirection),
	mPlayerActiveStatus(PlayerActiveStatus::IDLE)
{
}

void PlayerStatus::UpdatePlayerDirection(PlayerDirection playerDirection)
{
	mPlayerActiveStatus = PlayerActiveStatus::MOVING;
	mPlayerDirection = playerDirection;
}

std::string PlayerStatus::GetDirectionAsString() const
{
	switch (mPlayerDirection) {
	case PlayerDirection::UP: return "up";
	case PlayerDirection::DOWN: return "down";
	case PlayerDirection::LEFT: return "left";
	case PlayerDirection::RIGHT: return "right";
	default: 
		throw std::runtime_error("Unexpected enum value in GetDirectionAsString");
	}
}

std::string PlayerStatus::GetPlayerActiveStatusPostfix() const
{
	switch (mPlayerActiveStatus)
	{
	case PlayerActiveStatus::IDLE:
		return "_idle";
	case PlayerActiveStatus::MOVING:
		return "";
	case PlayerActiveStatus::ATTACKING:
		return "_attack";
		break;
	default:
		throw std::runtime_error("Unexpected enum value in GetPlayerActiveStatusPostfix");
	}
}

std::string PlayerStatus::AsCompatString() const
{
	return GetDirectionAsString() + GetPlayerActiveStatusPostfix();
}
