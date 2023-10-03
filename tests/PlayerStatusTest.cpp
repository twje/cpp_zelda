#include <gtest/gtest.h>
#include "PlayerStatus.h"

TEST(PlayerStatus, WhenPlayersDirectionIsDown_ThePlayerIsMovingDown)
{
    PlayerStatus playerStatus(PlayerDirection::DOWN);
    playerStatus.UpdatePlayerDirection(PlayerDirection::DOWN);

    EXPECT_EQ(playerStatus.GetDirectionAsString(), "down");
    EXPECT_EQ(playerStatus.AsCompatString(), "down");
}

TEST(PlayerStatus, WhenPlayersDirectionIsLeft_ThePlayerIsMovingLeft)
{
    PlayerStatus playerStatus(PlayerDirection::LEFT);
    playerStatus.UpdatePlayerDirection(PlayerDirection::LEFT);

    EXPECT_EQ(playerStatus.GetDirectionAsString(), "left");
    EXPECT_EQ(playerStatus.AsCompatString(), "left");
}


TEST(PlayerStatus, WhenPlayersDirectionIsRight_ThePlayerIsMovingRight)
{
    PlayerStatus playerStatus(PlayerDirection::RIGHT);
    playerStatus.UpdatePlayerDirection(PlayerDirection::RIGHT);

    EXPECT_EQ(playerStatus.GetDirectionAsString(), "right");
    EXPECT_EQ(playerStatus.AsCompatString(), "right");
}

TEST(PlayerStatus, WhenPlayersDirectionIsUp_ThePlayerIsMovingUp)
{
    PlayerStatus playerStatus(PlayerDirection::UP);
    playerStatus.UpdatePlayerDirection(PlayerDirection::UP);

    EXPECT_EQ(playerStatus.GetDirectionAsString(), "up");
    EXPECT_EQ(playerStatus.AsCompatString(), "up");
}

TEST(PlayerStatus, WhenPlayersWasMovingLeftAndHasSinceBecomeIdle_ThePlayerCompatStringIsLeftIdle)
{
    PlayerStatus playerStatus(PlayerDirection::LEFT);
    playerStatus.UpdatePlayerDirection(PlayerDirection::LEFT);
    playerStatus.SetPlayerToIdle();

    EXPECT_EQ(playerStatus.AsCompatString(), "left_idle");
}

TEST(PlayerStatus, WhenPlayersIsAttackingRight_ThePlayerCompatStringIsRightAttack)
{
    PlayerStatus playerStatus(PlayerDirection::LEFT);
    playerStatus.UpdatePlayerDirection(PlayerDirection::RIGHT);
    playerStatus.SetPlayerToAttacking();

    EXPECT_EQ(playerStatus.AsCompatString(), "right_attack");
}