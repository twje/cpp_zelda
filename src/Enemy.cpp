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

// -----
// Enemy
// -----
Enemy::Enemy(GroupManager& groupManager, const std::string& name, sf::Vector2f position, const Group& obstacles, IEnemyCallbacks& callbacks)
    : Entity(groupManager, obstacles),
      mName(name),
      mCallbacks(callbacks),
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
      mCanAttack(400, true),
      mIsVulnerable(300, true)
{
    mAnimation->SetAnimationSequence(mStatus);
    UpdateSequenceFrame();
    SetPosition(position);
    mHitBox = InflateRect(GetGlobalBounds(), 0, -10);
}

void Enemy::Update(const sf::Time &timestamp)
{
    HitReaction();
    Move(timestamp, mSpeed);
    Animate(timestamp);
    Cooldown(timestamp);
    CheckDeath();
}

void Enemy::HitReaction()
{
    if (!mIsVulnerable.Value())
    {
        mDirection.x *= -mResistance;
        mDirection.y *= -mResistance;
    }
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

    if (mIsVulnerable.Value())
    {
        SetAlpha(255);
    }
    else
    {
        SetAlpha(WaveValue());
    }
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
    mIsVulnerable.Update(timestamp);
}

void Enemy::CheckDeath()
{
    if (mHealth <= 0)
    {
        Kill();
        mCallbacks.TriggerDeathParticles(GetRectCenter(GetGlobalBounds()), mName);
    }
}

void Enemy::EnemyUpdate(const Player &player)
{
    GetStatus(player);
    Actions(player);
}

void Enemy::InflictDemage(const Player &player, uint16_t demage)
{
    if (mIsVulnerable.Value())
    {
        mDirection = GetPlayerDistanceDirection(player).second;
        mHealth = std::max(mHealth - demage, 0);
        mIsVulnerable.ToggleForCooldownTime();
    }
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
        // restart attack cooldown
        mCanAttack.ToggleForCooldownTime(true);
        mCallbacks.DemagePlayer(mAttackDamage, mAttackType);        
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
