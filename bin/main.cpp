#include <iostream>
#include "Parser.h"
#include "Functions.h"
#include "AllStructs.h"
#include "ParserLog.h"
#include <time.h>

int main(int argc, char* argv[])
{
    long long times = time(0);
    CommandFlags flags;
    ArgumentValues args;

    if(Parse(argc, argv, flags, args))
        return 1;

    ParserLog(flags, args);

    std::cout << "ALLTIME: " << time(0) - times << std::endl;
    return 0;
}
