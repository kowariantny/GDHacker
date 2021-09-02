#include "Hacks.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc < 2)
        return 0;

    switch (atoi(argv[1]))
    {
    case 0:
        if (argc > 2)
            ChangeSpeed(atof(argv[2]));
        break;

    case 1:
        FreezeTributes();
        break;

    case 2:
        if (argc > 2)
            PlayStatsToggle(atoi(argv[2]));
        break;

    case 3:
        if (argc > 2)
            FreezeExp(atoi(argv[2]));
        break;

    case 4:     
        FasterCamera();
        break;
    }
}


