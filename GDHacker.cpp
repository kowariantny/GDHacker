#include "Hacks.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv)
{
    uintptr_t offset = FindOffset(_FREEZE_TRIBUTES_OFFSET);
    if (offset)
        FreezeTributes(offset);
}


