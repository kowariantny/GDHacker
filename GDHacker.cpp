#include "Hacks.h"
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv)
{
    
    std::ifstream myfile; 
    myfile.open("offset.txt");


    uintptr_t offset;
    myfile >> std::hex >> offset;
    myfile.close();

    //std::cout << std::hex << offset;

    

    FreezeTributes(offset);
}


