
#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <map>
#include <string>

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
constexpr uint16_t ITEM_BOX_SIZE = 80;

enum class Direction
{
    HORIZONTAL,
    VERTICAL
};

enum class SpriteType
{
    GRASS,
    OBJECT,
    INVISIBLE,
    ENEMY,
    WEAPON
};

struct WeaponData
{
    uint16_t mCooldown;
    uint16_t mDamage;
};

struct MagicData
{
    uint16_t mStrength;
    uint16_t mCost;
};

struct MonsterData
{
    uint16_t health;
    uint16_t exp;
    uint16_t damage;
    uint16_t speed;
    uint16_t resistance;
    uint16_t attack_radius;
    uint16_t notice_radius;
    std::string attack_type;
    std::string attack_sound;
};

extern const std::map<std::string, WeaponData> WEAPON_DATA;
extern const std::map<std::string, MagicData> MAGIC_DATA;
extern const std::map<std::string, MonsterData> MONSTER_DATA;
extern const std::map<std::string, uint16_t> PLAYER_STATS;
