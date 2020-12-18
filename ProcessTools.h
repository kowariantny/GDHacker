#pragma once
#include <Windows.h>

uintptr_t GetModuleAddress(DWORD PID, LPCSTR module_name);
HANDLE GetProcess(LPCSTR proc_name);

template <class T>
int WriteProcess(HANDLE proc_handle, void* addr, T value)
{
    return WriteProcessMemory(
        proc_handle,
        addr,
        &value,
        sizeof(T),
        NULL
    );
}