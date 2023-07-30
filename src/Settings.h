
#pragma once

#include <cstdint>
#include <map>
#include <string>

constexpr char *CAPTION = "Zelda";
constexpr uint16_t WIDTH = 1280;
constexpr uint16_t HEIGHT = 720;
constexpr uint16_t BPP = 32;
constexpr uint16_t FPS = 60;
constexpr uint16_t TILESIZE = 64;

struct WeaponData
{
    int mCooldown;
    int mDamage;
    std::string mGraphics;
};

struct PlayerData
{
    std::string mGraphics;
};

extern const std::map<std::string, WeaponData> WEAPON_DATA;
extern const std::map<std::string, PlayerData> PLAYER_DATA;