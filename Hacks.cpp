#include <Windows.h>
#include "ProcessTools.h"
#include "Defaults.h"

void changeSpeed(float game_speed)
{
	HANDLE process_handle = getProcess(_GAME_PROCESS_NAME);
	if (process_handle != NULL)
	{
		uintptr_t engine_address = getModuleAddress(
			GetProcessId(process_handle), 
			_ENGINE_MODULE_NAME
		);

		if (engine_address != 0)
		{
			uintptr_t game_speed_address = engine_address + _GAME_SPEED_OFFSET;
			WriteMemory<float>(process_handle, (void*)game_speed_address, game_speed);
		}
	}
}