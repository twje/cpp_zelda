#include "PlayerStatus.h"

PlayerStatus::PlayerStatus(PlayerDirection playerDirection) :
	mPlayerDirection(playerDirection),
	mPlayerActiveStatus(PlayerActiveStatus::IDLE)
{
}

PlayerDirection PlayerStatus::GetPlayerDirection() const {
	return mPlayerDirection;
}

PlayerActiveStatus PlayerStatus::GetPlayerActiveStatus() const {
	return mPlayerActiveStatus;
}

void PlayerStatus::UpdatePlayerDirection(PlayerDirection playerDirection)
{
	mPlayerActiveStatus = PlayerActiveStatus::MOVING;
	mPlayerDirection = playerDirection;
}

void PlayerStatus::SetPlayerToIdle()
{
	mPlayerActiveStatus = PlayerActiveStatus::IDLE;
}

void PlayerStatus::SetPlayerToAttacking()
{
	mPlayerActiveStatus = PlayerActiveStatus::ATTACKING;
}

std::string PlayerStatus::GetDirectionAsString() const {
	switch (mPlayerDirection) {
	case PlayerDirection::UP: return "up";
	case PlayerDirection::DOWN: return "down";
	case PlayerDirection::LEFT: return "left";
	case PlayerDirection::RIGHT: return "right";
	}
	// What do?
	return "up";
}

std::string PlayerStatus::GetPlayerActoveStatusPostfix() const {
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
		break;
	}
	return "";
}

std::string PlayerStatus::AsCompatString() const {
	return GetDirectionAsString() + GetPlayerActoveStatusPostfix();
}
