#include <iostream>
#include <Windows.h>
#include <tlHelp32.h>

DWORD getProcess(LPCSTR process_name)
{
	HANDLE process_handle;
	PROCESSENTRY32 process_data;
	DWORD PID = NULL;
	DWORD _err;

	ZeroMemory(&process_data, sizeof(PROCESSENTRY32));
	process_data.dwSize = sizeof(PROCESSENTRY32);

	process_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		_err = GetLastError();
		printf("CreateToolHelp32Snapshot fail\n");
		return NULL;
	}

	if (Process32First(process_handle, &process_data) == false)
	{
		_err = GetLastError();
		printf("Process32First fail\n");
		CloseHandle(process_handle);
		return NULL;
	}

	do
	{
		HANDLE process_handle_iter = OpenProcess(
			PROCESS_QUERY_INFORMATION,
			false,
			process_data.th32ProcessID
		);

		if (process_handle_iter != NULL)
		{
			if (strcmp(process_data.szExeFile, process_name) == 0)
			{
				PID = process_data.th32ProcessID;
				CloseHandle(process_handle);
				CloseHandle(process_handle_iter);

				return PID;
			}

			CloseHandle(process_handle_iter);
		}

	} while (Process32Next(process_handle, &process_data) != false);

	CloseHandle(process_handle);

	return PID;
}
void printPID(DWORD PID)
{
	printf("Opened process Id %d (%x)\n", PID, PID);
}