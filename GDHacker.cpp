#include <iostream>
#include <Windows.h>
#include "ProcessTools.h"

int main()
{
	HANDLE process_handle = getProcess("Tutorial-x86_64.exe");

	if (process_handle != NULL)
	{
		printf("process found\n");
	}
	else
	{
		printf("unable to find process\n");
	}

	system("pause");
}


