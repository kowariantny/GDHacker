#include <iostream>
#include <Windows.h>
#include "ProcessTools.h"

int main()
{
	DWORD PID = 0;
	DWORD _err;

	HWND tutorial_window = FindWindow(0, "Step 2");

	if (tutorial_window != NULL)
	{
		printf("window found\n");
		GetWindowThreadProcessId(tutorial_window, &PID);

		if (PID != NULL)
		{
			HANDLE process_handle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ 
												| PROCESS_VM_WRITE, false, PID);

			if (process_handle != NULL)
			{
				printPID(PID);
				CloseHandle(process_handle);
			}
			else
			{
				_err = GetLastError();
				printf("Process not opened: %d (%x)\n", _err, _err);
			}
		}
	}
	else
	{
		printf("window not found\n"
			"attempting to find window by process\n");

		PID = getProcess("Tutorial-x86_64.exe");

		if (PID != NULL)
		{
			printPID(PID);
		}
		else
		{
			printf("unable to find process\n");
		}
	}

	system("pause");
}

