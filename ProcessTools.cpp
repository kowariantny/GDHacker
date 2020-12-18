#include <iostream>
#include <Windows.h>
#include <tlHelp32.h>

HANDLE getProcess(LPCSTR process_name)
{
	HANDLE process_handle;
	PROCESSENTRY32 process_data;
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
			PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION,
			false,
			process_data.th32ProcessID
		);

		if (process_handle_iter != NULL)
		{
			if (strcmp(process_data.szExeFile, process_name) == 0)
			{
				CloseHandle(process_handle);

				return process_handle_iter;
			}

			CloseHandle(process_handle_iter);
		}

	} while (Process32Next(process_handle, &process_data) != false);

	CloseHandle(process_handle);

	return NULL;
}
void printPID(DWORD PID)
{
	printf("Opened process Id %d (%x)\n", PID, PID);
}

void writeMemory(HANDLE process_handle, void* addr, DWORD value)
{
	if (WriteProcessMemory(
		process_handle,
		addr,
		&value,
		sizeof(value),
		NULL
	))
	{
		printf("Wrote %d at address %p\n", value, addr);
	}
	else
		printf("error writing to memory\n");
}

uintptr_t getModuleAddress(DWORD PID, LPCSTR module_name)
{
	uintptr_t address = 0;
	HANDLE module_handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
	if (module_handle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 module_data;
		module_data.dwSize = sizeof(module_data);

		if (Module32First(module_handle, &module_data))
		{
			do
			{
				if (strcmp(module_name, module_data.szModule) == 0)
				{
					address = (uintptr_t)module_data.modBaseAddr;
					break;
				}
			} while (Module32Next(module_handle, &module_data));
		}
	}
	return address;
}