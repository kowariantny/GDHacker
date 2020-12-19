#include "ProcessTools.h"
#include <tlHelp32.h>

HANDLE GetProcess(LPCSTR proc_name)
{
    PROCESSENTRY32 proc_data;
    ZeroMemory(&proc_data, sizeof(PROCESSENTRY32));
    proc_data.dwSize = sizeof(PROCESSENTRY32);

    HANDLE proc_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (proc_snapshot == INVALID_HANDLE_VALUE)
        return INVALID_HANDLE_VALUE;

    if (!Process32First(proc_snapshot, &proc_data))
    {
        CloseHandle(proc_snapshot);
        return INVALID_HANDLE_VALUE;
    }

    do
    {
        HANDLE proc_iter = OpenProcess(
            PROCESS_VM_OPERATION | 
            PROCESS_VM_READ | 
            PROCESS_VM_WRITE | 
            PROCESS_QUERY_INFORMATION,
            false,
            proc_data.th32ProcessID
        );

        if (proc_iter)
        {
            if (!strcmp(proc_data.szExeFile, proc_name))
            {
                CloseHandle(proc_snapshot);
                return proc_iter;
            }

            CloseHandle(proc_iter);
        }

    }
    while (Process32Next(proc_snapshot, &proc_data));

    CloseHandle(proc_snapshot);
    return INVALID_HANDLE_VALUE;
}

uintptr_t GetModuleAddress(DWORD PID, LPCSTR module_name)
{
    HANDLE module_snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE | 
        TH32CS_SNAPMODULE32, 
        PID
    );
    if (module_snapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32 module_data;
    module_data.dwSize = sizeof(module_data);

    if (!Module32First(module_snapshot, &module_data))
    {
        CloseHandle(module_snapshot);
        return 0;
    }

    do
    {
        if (!strcmp(module_name, module_data.szModule))
        {
            CloseHandle(module_snapshot);
            return (uintptr_t)module_data.modBaseAddr;
        }
    } while (Module32Next(module_snapshot, &module_data));

    CloseHandle(module_snapshot);
    return 0;
}