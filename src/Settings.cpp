#include "Settings.h"

const std::unordered_map<std::string, WeaponData> WEAPON_DATA = {
    {"sword", {100, 15, "../graphics/weapons/sword"}},
    {"lance", {400, 30, "../graphics/weapons/lance"}},
    {"axe", {300, 20, "../graphics/weapons/axe"}},
    {"rapier", {50, 8, "../graphics/weapons/rapier"}},
    {"sai", {80, 10, "../graphics/weapons/sai"}}};

const std::unordered_map<std::string, PlayerData> PLAYER_DATA = {
    {"up", {"../graphics/player/up"}},
    {"down", {"../graphics/player/down"}},
    {"left", {"../graphics/player/left"}},
    {"right", {"../graphics/player/right"}},
    {"up_idle", {"../graphics/player/up_idle"}},
    {"down_idle", {"../graphics/player/down_idle"}},
    {"left_idle", {"../graphics/player/left_idle"}},
    {"right_idle", {"../graphics/player/right_idle"}},
    {"up_attack", {"../graphics/player/up_attack"}},
    {"down_attack", {"../graphics/player/down_attack"}},
    {"left_attack", {"../graphics/player/left_attack"}},
    {"right_attack", {"../graphics/player/right_attack"}}};