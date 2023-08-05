
#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <map>
#include <string>

#include "GuiStyle.h"

// Map
constexpr char *CAPTION = "Zelda";
constexpr uint16_t WIDTH = 1280;
constexpr uint16_t HEIGHT = 720;
constexpr uint16_t BPP = 32;
constexpr uint16_t FPS = 60;
constexpr uint16_t TILESIZE = 64;

// UI
constexpr uint16_t BAR_HEIGHT = 20;
constexpr uint16_t HEALTH_BAR_WIDTH = 200;
constexpr uint16_t ENERGY_BAR_WIDTH = 140;

enum class Direction
{
    HORIZONTAL,
    VERTICAL
};

enum class SpriteType
{
    GRASS,
    OBJECT,
    INVISIBLE
};

struct WeaponData
{
    int mCooldown;
    int mDamage;
};

extern const std::map<std::string, WeaponData> WEAPON_DATA;

// GUI
extern const GuiStyle DEFAULT_STYLE;