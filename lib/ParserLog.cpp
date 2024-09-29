#include <iostream>
#include "AllStructs.h"
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

    std::ofstream fileOutput;
    if (flags.output)
        fileOutput.open(args.pathFileOutput);

    char buffer[65536];

    while (fileLog.getline(buffer, 65536))
    {
        //std::cout << buffer << std::endl;
        buffer[65535] = '\0';

        ValuesLog lineLog;
        int start = FindSymbol(buffer, 0, '[');
        int end = FindSymbol(buffer, start, ']');
        if (start == -1 || end == -1)
            continue;
        
        lineLog.str = buffer;
        lineLog.localTimeLeft = start;
        lineLog.localTimeRight = end;

        start = FindSymbol(buffer, end, '"');
        end = FindSymbol(buffer, start + 1, '"');
        if (start == -1 || end == -1 || buffer[end + 1] == '\0')
            continue;

        start = end + 1;
        end = FindSymbol(buffer, start + 1, ' ');
        int num = StringToInt(buffer, start + 1, end);
        if (start == -1 || end == -1 || end - start < 2 || num < 500 || num > 599)
            continue;
        
        lineLog.status = num;
        lineLog.LocalTimeToInt();
        if (lineLog.timeInt < args.fromT || lineLog.timeInt > args.toT)
            continue;
        
        if (flags.print)
            std::cout << buffer << std::endl;

        // end = FindSymbol(buffer, end, '\0');
        // buffer[end] = '\n';
        if (flags.output)
        {
            fileOutput << buffer << std::endl;
        }
    }
    

    fileLog.close();
    fileOutput.close();
    return 0;
}