#include <Windows.h>
#include "ProcessTools.h"
#include "Defaults.h"

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
		return;

	uintptr_t speed_addr = engine_addr + _GAME_SPEED_OFFSET;
	WriteProcess<float>(proc_handle, (void*)speed_addr, game_speed);
}