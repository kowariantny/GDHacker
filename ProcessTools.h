#pragma once
#include <Windows.h>

uintptr_t GetModuleAddress(DWORD PID, LPCSTR module_name);
HANDLE GetProcess(LPCSTR proc_name);
