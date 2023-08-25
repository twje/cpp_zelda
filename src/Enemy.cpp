#include "Enemy.h"

#pragma once

#include <iostream>

// Core
#include "Core/Group.h"
#include "Core/ResourceManager/AnimationManager.h"
#include "Core/RectUtils.h"

// Game
#include "Settings.h"
#include "Player.h"

Enemy::Enemy(const std::string &name, sf::Vector2f position, const Group &obstacles)
    : Entity(obstacles),
      mName(name),
      mSpriteType(SpriteType::ENEMY),
      mAnimation(AnimationManager::GetInstance().LoadUnique(name)),
      mStatus("idle"),
      mHealth(MONSTER_DATA.at(name).health),
      mExp(MONSTER_DATA.at(name).exp),
      mSpeed(MONSTER_DATA.at(name).speed),
      mAttackDamage(MONSTER_DATA.at(name).damage),
      mResistance(MONSTER_DATA.at(name).resistance),
      mAttackRadius(MONSTER_DATA.at(name).attack_radius),
      mNoticeRadius(MONSTER_DATA.at(name).notice_radius),
      mAttackType(MONSTER_DATA.at(name).attack_type),
      mCanAttack(400, true)
{
    mAnimation->SetAnimationSequence(mStatus);
    UpdateSequenceFrame();
    SetPosition(position);
    mHitBox = InflateRect(GetGlobalBounds(), 0, -10);
}

void Enemy::Update(const sf::Time &timestamp)
{
    Move(timestamp, mSpeed);
    Animate(timestamp);
    Cooldown(timestamp);
}

void Enemy::Animate(const sf::Time &timestamp)
{
    if (mStatus != mAnimation->GetSequenceID())
    {
        mAnimation->SetAnimationSequence(mStatus);
    }

    mAnimation->Update(timestamp);
    UpdateSequenceFrame();
    SetPosition(GetRectCenter(mHitBox) - .5f * GetSize());
}

void Enemy::UpdateSequenceFrame()
{
    SequenceFrame &frame = mAnimation->GetSequenceFrame();
    SetTexture(frame.mTexture);
    SetTextureRect(frame.mTextureRect);
}

void Enemy::Cooldown(const sf::Time &timestamp)
{
    mCanAttack.Update(timestamp);
}

void Enemy::EnemyUpdate(const Player &player)
{
    GetStatus(player);
    Actions(player);
}

bool Enemy::IsAttackAnimationPlaying()
{
    return mAnimation->GetSequenceID() == "attack" && !mAnimation->IsAllFramesPlayed();
}

bool Enemy::IsAllowedToAttack()
{
    return IsAttackAnimationPlaying() || mCanAttack.Value();
}

std::pair<float, sf::Vector2f> Enemy::GetPlayerDistanceDirection(const Player &player)
{
    sf::Vector2f enemyVec{GetRectCenter(GetGlobalBounds())};
    sf::Vector2f playerVec{GetRectCenter(player.GetGlobalBounds())};
    float distance = (playerVec - enemyVec).length();

    sf::Vector2f direction;
    if (distance > 0)
    {
        direction = (playerVec - enemyVec);
    }

    return {distance, direction};
}

void Enemy::GetStatus(const Player &player)
{
    float distance = GetPlayerDistanceDirection(player).first;
    if (distance <= mAttackRadius && IsAllowedToAttack())
    {
        mStatus = "attack";
    }
    else if (distance <= mNoticeRadius)
    {
        mStatus = "move";
    }
    else
    {
        mStatus = "idle";
    }
}

void Enemy::Actions(const Player &player)
{
    // An attack is for the during of an attack animation sequence followed by a state
    // change that lasts for the duration of the attack cooldown period.
    if (mStatus == "attack")
    {
        // reset attack cooldown
        mCanAttack.ToggleForCooldownTime(true);
        std::cout << "attack" << std::endl;
    }
    else if (mStatus == "move")
    {
        mDirection = GetPlayerDistanceDirection(player).second;
    }
    else
    {
        mDirection = sf::Vector2f();
    }
}
