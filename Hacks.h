#pragma once
#include <vector>

const char* const _GAME_PROCESS_NAME = "Grim Dawn.exe";
const char* const _ENGINE_MODULE_NAME = "Engine.dll";
const char* const _GAME_MODULE_NAME = "Game.dll";

const uintptr_t _GAME_SPEED_OFFSET = 0x416780;

const uintptr_t _FREEZE_TRIBUTES_OFFSET = 0x37ABFF;
const std::vector<unsigned char> _FREEZE_TRIBUTES_INJECT(6, 0x90);

const uintptr_t _PLAYSTATS_OFFSET = 0xF7AD;
const std::vector<unsigned char> _PLAYSTATS_INJECT[2] = {
    std::vector<unsigned char>{0x75, 0x1B},
    std::vector<unsigned char>(2, 0x90)
};

const uintptr_t _FREEZE_EXP_OFFSET = 0x1E503A;
const std::vector<unsigned char> _FREEZE_EXP_INJECT[2] = {
    std::vector<unsigned char>{0x01, 0x51, 0x7C},
    std::vector<unsigned char>(3, 0x90)
};

void ChangeSpeed(float game_speed);
void FreezeTributes();
void PlayStatsToggle(bool state);
void FreezeExp(bool state);