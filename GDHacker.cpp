#include "Hacks.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv)
{
    uintptr_t offset = FindExpOffset(_FREEZE_EXP_OFFSET);
    if (offset)
        FreezeExp(offset);
}


