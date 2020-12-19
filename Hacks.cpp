#include "Hacks.h"
#include "ProcessTools.h"
#include <algorithm>
#include <iostream>

void ChangeSpeed(float game_speed)
{
    HANDLE proc_handle = GetProcess(_GAME_PROCESS_NAME);
    if (proc_handle == INVALID_HANDLE_VALUE)
        return;

    uintptr_t engine_addr = GetModuleAddress(
        GetProcessId(proc_handle), 
        _ENGINE_MODULE_NAME
    );
    if (!engine_addr)
    {
        CloseHandle(proc_handle);
        return;
    }

    uintptr_t speed_addr = engine_addr + _GAME_SPEED_OFFSET;
    WriteProcessMemory(
        proc_handle, 
        (LPVOID)speed_addr, 
        &game_speed, 
        sizeof(game_speed), 
        NULL
    );

    CloseHandle(proc_handle);
}

void FreezeTributes()
{
    HANDLE proc_handle = GetProcess(_GAME_PROCESS_NAME);
    if (proc_handle == INVALID_HANDLE_VALUE)
        return;

    uintptr_t game_addr = GetModuleAddress(
        GetProcessId(proc_handle),
        _GAME_MODULE_NAME
    );
    if (!game_addr)
    {
        CloseHandle(proc_handle);
        return;
    }

    uintptr_t tributes_addr = game_addr + _FREEZE_TRIBUTES_OFFSET;
    WriteProcessMemory(
        proc_handle,
        (LPVOID)tributes_addr,
        _FREEZE_TRIBUTES_INJECTION.data(),
        _FREEZE_TRIBUTES_INJECTION.size(),
        NULL
    );

    CloseHandle(proc_handle);
}
