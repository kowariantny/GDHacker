#pragma once
#include <Windows.h>
HANDLE getProcess(LPCSTR process_name);
void printPID(DWORD PID);
void writeMemory(HANDLE process_handle, void* addr, DWORD value);
uintptr_t getModuleAddress(DWORD PID, LPCSTR module_name);
