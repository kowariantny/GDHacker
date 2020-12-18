#include <iostream>
#include <Windows.h>
#include <inttypes.h>
#include "ProcessTools.h"

int main()
{
	HANDLE process_handle = getProcess("Grim Dawn.exe");

	if (process_handle != NULL)
	{
		printf("process found\n");
		uintptr_t engine_address = getModuleAddress(GetProcessId(process_handle), "Engine.dll");
		if (engine_address == 0)
		{
			printf("Couldn't retrieve module address\n");
		}
		else
		{
			printf("Here's a pointer for you: %" PRIxPTR "\n", engine_address);

			uintptr_t game_speed_address = engine_address + 0x416780;
			printf("Translated pointer %" PRIxPTR "\n", game_speed_address);
			
			float game_speed = 2.0;
			int result = WriteMemory<float>(process_handle, (void*)game_speed_address, game_speed);
			printf(result != 0 ? "yes\n" : "no\n");
		}
		//printf("Here's a pointer for you: %" PRIxPTR "\n", p);
		// writeMemory(process_handle, (void*)0x011066B0, 1000);
		// Engine.dll
	}
	else
	{
		printf("unable to find process\n");
	}

	system("pause");
}


