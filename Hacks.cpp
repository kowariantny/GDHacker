#include "Hacks.h"
#include "ProcessTools.h"

void ChangeSpeed(float game_speed)
{
    WriteProcess(
        _GAME_PROCESS_NAME,
        _ENGINE_MODULE_NAME,
        _GAME_SPEED_OFFSET,
        &game_speed,
        sizeof(game_speed)
    );
}

void FreezeTributes()
{
    WriteProcess(
        _GAME_PROCESS_NAME,
        _GAME_MODULE_NAME,
        _FREEZE_TRIBUTES_OFFSET,
        _FREEZE_TRIBUTES_INJECT.data(),
        _FREEZE_TRIBUTES_INJECT.size()
    );
}

void PlayStatsToggle(bool state)
{
    WriteProcess(
        _GAME_PROCESS_NAME,
        _GAME_PROCESS_NAME,
        _PLAYSTATS_OFFSET,
        _PLAYSTATS_INJECT[state].data(),
        _PLAYSTATS_INJECT[state].size()
    );
}

void FreezeExp(bool state)
{
    WriteProcess(
        _GAME_PROCESS_NAME,
        _GAME_MODULE_NAME,
        _FREEZE_EXP_OFFSET,
        _FREEZE_EXP_INJECT[state].data(),
        _FREEZE_EXP_INJECT[state].size()
    );
}

void FasterCamera(int level)
{
    std::vector<unsigned char> _FASTER_CAMERA_INJECT{ 0xF3, 0x0F, 0x59, 0x35
        , (unsigned char)( 0xD2 + (level*4)), 0xC5, 0x41, 0x00 };

    WriteProcess(
        _GAME_PROCESS_NAME,
        _GAME_MODULE_NAME,
        _FASTER_CAMERA_OFFSET,
        _FASTER_CAMERA_INJECT.data(),
        _FASTER_CAMERA_INJECT.size()
    );
}

void UnlockConsole()
{
    WriteModule(
        _GAME_PROCESS_NAME,
        _GAME_PROCESS_NAME,
        2,
        _CONSOLE_UNLOCK_OFFSETS,
        _CONSOLE_UNLOCK_INJECTS
    );
}