#pragma once
#include <Windows.h>
#include <string>

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

void printBytes(const SIZE_T data_size, BYTE* data);
bool ControlTributes(
    LPCVOID data_control,
    const SIZE_T data_size,
    HANDLE proc_handle,
    uintptr_t module_addr,
    const uintptr_t offset
);


uintptr_t UpdateOffset(
    LPCSTR proc_name,
    LPCSTR module_name,
    LPCVOID data_control,
    const uintptr_t offset,
    const SIZE_T data_size
);

uintptr_t UpdateExpOffset(
    LPCSTR proc_name,
    LPCSTR module_name,
    LPCVOID data_control,
    const uintptr_t offset,
    const SIZE_T data_size
);
