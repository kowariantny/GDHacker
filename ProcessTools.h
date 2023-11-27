#pragma once
#include <Windows.h>
#include <vector>

uintptr_t GetModuleAddress(DWORD PID, LPCSTR module_name);
HANDLE GetProcess(LPCSTR proc_name);

void WriteProcess(
    LPCSTR proc_name,
    LPCSTR module_name,
    const uintptr_t offset,
    LPCVOID data_addr,
    SIZE_T data_size
);

void WriteModule(
    LPCSTR proc_name,
    LPCSTR module_name,
    const int N,
    const uintptr_t offsets[],
    const std::vector<unsigned char> injects[]
);