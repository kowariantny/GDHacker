#pragma once
#include <vector>
#include <string>

const char* const _GAME_PROCESS_NAME = "Grim Dawn.exe";
const char* const _ENGINE_MODULE_NAME = "Engine.dll";
const char* const _GAME_MODULE_NAME = "Game.dll";

const uintptr_t _GAME_SPEED_OFFSET = 0x416780;

const uintptr_t _FREEZE_TRIBUTES_OFFSET = 0x37DF8F;
const std::vector<unsigned char> _FREEZE_TRIBUTES_INJECT(6, 0x90);
const std::vector<unsigned char> _FREEZE_TRIBUTES_CONTROL{ 0x89, 0x83, 0x30, 0x13, 0x00, 0x00 };

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
const std::vector<unsigned char> _FREEZE_EXP_CONTROL{ 0x01, 0x51, 0x7C, 0x40, 0x32, 0xFF, 0x8B, 0x41, 0x74 };


void ChangeSpeed(float game_speed);
void FreezeTributes(uintptr_t offset);
void PlayStatsToggle(bool state);
void FreezeExp(uintptr_t offset);
void writeLog(std::string text);

uintptr_t FindOffset(uintptr_t offset);
uintptr_t FindExpOffset(uintptr_t offset);