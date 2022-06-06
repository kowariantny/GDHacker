#pragma once
#include <Windows.h>

uintptr_t GetModuleAddress(DWORD PID, LPCSTR module_name);
HANDLE GetProcess(LPCSTR proc_name);

void WriteProcess(
    LPCSTR proc_name,
    LPCSTR module_name,
    const uintptr_t offset,
    LPCVOID data_addr,
    const SIZE_T data_size,
    LPCVOID data_control = NULL
);
