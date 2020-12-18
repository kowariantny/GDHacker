#include <iostream>
#include <Windows.h>

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
				printf("Opened process Id %d (%x)\n", PID, PID);
				CloseHandle(process_handle);
			}
			else
			{
				_err = GetLastError();
				printf("Process not opened: %d (%x)\n", _err, _err);
			}
		}
	}
	else printf("window not found\n");

	system("pause");
}

