#include "Settings.h"

const std::map<std::string, WeaponData> WEAPON_DATA = {
    {"sword", {100, 15, "../graphics/weapons/sword"}},
    {"lance", {400, 30, "../graphics/weapons/lance"}},
    {"axe", {300, 20, "../graphics/weapons/axe"}},
    {"rapier", {50, 8, "../graphics/weapons/rapier"}},
    {"sai", {80, 10, "../graphics/weapons/sai"}}};

const std::map<std::string, PlayerData> PLAYER_DATA = {
    {"up_0", {"../graphics/player/up/up_0.png"}},
    {"up_1", {"../graphics/player/up/up_1.png"}},
    {"up_2", {"../graphics/player/up/up_2.png"}},
    {"up_3", {"../graphics/player/up/up_3.png"}},
    {"down_0", {"../graphics/player/down/down_0.png"}},
    {"down_1", {"../graphics/player/down/down_1.png"}},
    {"down_2", {"../graphics/player/down/down_2.png"}},
    {"down_3", {"../graphics/player/down/down_3.png"}},
    {"left_0", {"../graphics/player/left/left_0.png"}},
    {"left_1", {"../graphics/player/left/left_1.png"}},
    {"left_2", {"../graphics/player/left/left_2.png"}},
    {"left_3", {"../graphics/player/left/left_3.png"}},
    {"right_0", {"../graphics/player/right/right_0.png"}},
    {"right_1", {"../graphics/player/right/right_1.png"}},
    {"right_2", {"../graphics/player/right/right_2.png"}},
    {"right_3", {"../graphics/player/right/right_3.png"}},
    {"up_idle", {"../graphics/player/up_idle/idle_up.png"}},
    {"down_idle", {"../graphics/player/down_idle/idle_down.png"}},
    {"left_idle", {"../graphics/player/left_idle/idle_left.png"}},
    {"right_idle", {"../graphics/player/right_idle/idle_right.png"}},
    {"up_attack", {"../graphics/player/up_attack/attack_up.png"}},
    {"down_attack", {"../graphics/player/down_attack/attack_down.png"}},
    {"left_attack", {"../graphics/player/left_attack/attack_left.png"}},
    {"right_attack", {"../graphics/player/right_attack/attack_right.png"}}};