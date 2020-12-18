#include <stdlib.h>
#include "Hacks.h"

int main(int argc, char** argv)
{
    if (argc < 3)
        return 0;

    switch (atoi(argv[1]))
    {
    case 0:
        ChangeSpeed(atof(argv[2]));
        break;

    default:
        break;
    }
}


