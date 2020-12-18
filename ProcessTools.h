#pragma once
#include <Windows.h>
HANDLE getProcess(LPCSTR process_name);
void printPID(DWORD PID);
uintptr_t getModuleAddress(DWORD PID, LPCSTR module_name);

template <class T>
int WriteMemory(HANDLE process_handle, void* addr, T value)
{
	return WriteProcessMemory(
		process_handle,
		addr,
		&value,
		sizeof(T),
		NULL
	);
}