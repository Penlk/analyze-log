#include <iostream>
#include <ctime>

#include "AllStructs.h"
#include "Functions.h"
#include "Parser.h"
#include "ParserLog.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Not enough arguments\n";
        return 1;
    }

    long long times = time(0);
    CommandFlags flags;
    ArgumentValues args;

    if(Parse(argc, argv, flags, args))
        return EXIT_FAILURE;

    ParserLog(flags, args);

    std::cout << "ALLTIME: " << time(0) - times << std::endl;
    return 0;
}
