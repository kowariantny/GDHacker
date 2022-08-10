#include "Hacks.h"
#include "ProcessTools.h"
#include <fstream>

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

void FreezeTributes(uintptr_t offset)
{
    WriteProcess(
        _GAME_PROCESS_NAME,
        _GAME_MODULE_NAME,
        offset,
        _FREEZE_TRIBUTES_INJECT.data(),
        _FREEZE_TRIBUTES_INJECT.size(),
        _FREEZE_TRIBUTES_CONTROL.data()
    );
}

uintptr_t FindOffset(uintptr_t offset)
{
    return UpdateOffset(
        _GAME_PROCESS_NAME,
        _GAME_MODULE_NAME,
        _FREEZE_TRIBUTES_CONTROL.data(),
        offset,
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

void writeLog(std::string text)
{
    std::ofstream o; //ofstream is the class for fstream package
    o.open("log.txt"); //open is the method of ofstream
    o << text << std::endl;
    o.close();
}