#pragma once
#include <vector>

const char* const _GAME_PROCESS_NAME = "Grim Dawn.exe";
const char* const _ENGINE_MODULE_NAME = "Engine.dll";
const char* const _GAME_MODULE_NAME = "Game.dll";

const uintptr_t _GAME_SPEED_OFFSET = 0x414780;

const uintptr_t _FREEZE_TRIBUTES_OFFSET = 0x37AD3F;
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

const uintptr_t _FASTER_CAMERA_OFFSET = 0x216972;

const uintptr_t _CONSOLE_UNLOCK_OFFSETS[2] = { 0x25BAEB, 0x28ECDC };
const std::vector<unsigned char> _CONSOLE_UNLOCK_INJECTS[2] = {
    std::vector<unsigned char>{0xE9, 0xEC, 0x31, 0x03, 0x00, 0x90},
    std::vector<unsigned char>{0xC7, 0x41, 0x10, 0x01, 0x00, 0x00, 0x00, 0x4C, 0x8B, 0xF2, 0x48, 0x8B, 0xF9, 0xE9, 0x03, 0xCE, 0xFC, 0xFF}
};

void ChangeSpeed(float game_speed);
void FreezeTributes();
void PlayStatsToggle(bool state);
void FreezeExp(bool state);
void FasterCamera(int level);
void UnlockConsole();