#include "Settings.h"

const std::map<std::string, WeaponData> WEAPON_DATA = {
    {"sword", {100, 15}},
    {"lance", {400, 30}},
    {"axe", {300, 20}},
    {"rapier", {50, 8}},
    {"sai", {80, 10}}};

const std::map<std::string, MagicData> MAGIC_DATA = {
    {"sword", {5, 20}},
    {"lance", {20, 10}}};

const std::map<std::string, uint16_t> PLAYER_STATS = {
    {"health", 100},
    {"energy", 60},
    {"attack", 10},
    {"magic", 4},
    {"speed", 5}};