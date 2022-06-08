#include "ProcessTools.h"
#include <tlHelp32.h>
#include <iostream>
#include <iomanip>
#include <fstream>

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
            if (!_stricmp(proc_data.szExeFile, proc_name))
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
        if (!_stricmp(module_name, module_data.szModule))
        {
            CloseHandle(module_snapshot);
            return (uintptr_t)module_data.modBaseAddr;
        }
    } while (Module32Next(module_snapshot, &module_data));

    CloseHandle(module_snapshot);
    return 0;
}

void WriteProcess(
    LPCSTR proc_name, 
    LPCSTR module_name, 
    const uintptr_t offset,
    LPCVOID data_addr,
    const SIZE_T data_size,
    LPCVOID data_control
)
{
    HANDLE proc_handle = GetProcess(proc_name);
    if (proc_handle == INVALID_HANDLE_VALUE)
        return;

    uintptr_t module_addr = GetModuleAddress(
        GetProcessId(proc_handle),
        module_name
    );
    if (!module_addr)
    {
        CloseHandle(proc_handle);
        return;
    }

    if (ControlTributes(data_control, data_size, proc_handle, module_addr, offset))
    {
        WriteProcessMemory(
            proc_handle,
            (LPVOID)(module_addr + offset),
            data_addr,
            data_size,
            NULL
        );
        writeLog("Tributes have been frozen (hopefully)");
    }
    else // std::cout << "Program needs updating or Tributes are already frozen." << std::endl;
        writeLog("Offset needs updating or Tributes were frozen already in previous run");
    
    CloseHandle(proc_handle);
}

bool ControlTributes(
    LPCVOID data_control,
    const SIZE_T data_size,
    HANDLE proc_handle,
    uintptr_t module_addr,
    const uintptr_t offset
)
{
    if (data_control != NULL)
    {
        unsigned char* control_buffer = new unsigned char[data_size];
        SIZE_T number_of_bytes = 0;

        ReadProcessMemory(
            proc_handle,
            (LPCVOID)(module_addr + offset),
            control_buffer,
            data_size,
            &number_of_bytes
        );

        // printBytes(data_size, control_buffer);
        //printBytes(number_of_bytes, (BYTE*)data_control);

        if ((data_size != number_of_bytes)
            || memcmp(data_control, control_buffer, number_of_bytes))
        {
            delete[] control_buffer;
            CloseHandle(proc_handle);
            return false;
        }

        delete[] control_buffer;
    }
}

void printBytes(const SIZE_T data_size, BYTE *data)
{
    for (int i = 0; i < data_size; i++)
        std::cout << std::hex << std::setw(2) << (int)data[i] << " ";

    std::cout << std::endl;
}

void writeLog(std::string text)
{
    std::ofstream o; //ofstream is the class for fstream package
    o.open("log.txt"); //open is the method of ofstream
    o << text << std::endl;
    o.close();
}