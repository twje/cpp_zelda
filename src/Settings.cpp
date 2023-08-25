#include "Settings.h"

const std::map<std::string, WeaponData> WEAPON_DATA = {
    {"sword", {100, 15}},
    {"lance", {400, 30}},
    {"axe", {300, 20}},
    {"rapier", {50, 8}},
    {"sai", {80, 10}}};

const std::map<std::string, MagicData> MAGIC_DATA = {
    {"flame", {5, 20}},
    {"heal", {20, 10}}};

const std::map<std::string, MonsterData> MONSTER_DATA = {
    {"squid", {100, 100, 20, 3, 3, 80, 360, "slash", "../audio/attack/slash.wav"}},
    {"raccoon", {300, 250, 40, 2, 3, 120, 400, "claw", "../audio/attack/claw.wav"}},
    {"spirit", {100, 110, 8, 4, 3, 60, 350, "thunder", "../audio/attack/fireball.wav"}},
    {"bamboo", {70, 120, 6, 3, 3, 50, 300, "leaf_attack", "../audio/attack/slash.wav"}}};

const std::map<std::string, uint16_t> PLAYER_STATS = {
    {"health", 100},
    {"energy", 60},
    {"attack", 10},
    {"magic", 4},
    {"speed", 5}};
