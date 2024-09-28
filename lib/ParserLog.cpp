#include "/Structs/AllStructs.h"
#include "Functions.h"
#include <fstream>

int ParserLog(IsCommands flags, ValuesArgs args)
{
    std::ifstream fileLog;
    fileLog.open(args.pathFileLog);

    if (!fileLog.is_open())
    {
        printf("Cannot open the file %s\n", args.pathFileLog);
        return 1;
    }

    char buffer[8192];

    while (fileLog.getline(buffer, 8192))
    {
        ValuesLog asdf;
        int start = 0;
        int end = FindSymbol(buffer, start, ' ');

    }
    

    fileLog.close();
    return 0;
}