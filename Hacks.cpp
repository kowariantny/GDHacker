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
