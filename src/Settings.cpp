#include "Settings.h"

const std::map<std::string, WeaponData> WEAPON_DATA = {
    {"sword", {100, 15, "../graphics/weapons/sword/full.png"}},
    {"lance", {400, 30, "../graphics/weapons/lance/full.png"}},
    {"axe", {300, 20, "../graphics/weapons/axe/full.png"}},
    {"rapier", {50, 8, "../graphics/weapons/rapier/full.png"}},
    {"sai", {80, 10, "../graphics/weapons/sai/full.png"}}};

const std::map<std::string, PlayerData> PLAYER_DATA = {
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
