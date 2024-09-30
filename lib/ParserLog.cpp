#include <iostream>
#include "Structs/AllStructs.h"
#include "Functions.h"
#include <fstream>

int ParserLog(IsCommands flags, ValuesArgs args)
{
    std::ifstream fileLog;
    fileLog.open(args.pathFileLog);

    if (!fileLog.is_open())
    {
        printf("Cannot open the log file %s\n", args.pathFileLog);
        return 1;
    }

    std::ofstream fileOutput;
    if (flags.output)
    {
        fileOutput.open(args.pathFileOutput);
        if (!fileOutput.is_open())
            printf("Cannot create or open the file\n%s\n", args.pathFileOutput);
    }

    if (!fileOutput.is_open())
        return 1;

    char buffer[65536];

    MyList<char*> requests;
    MyList<long*> valuesStats;

    long long lastTime = -1;
    long long resultCounter = 1;
    long long counter = 0;
    long long fromMax = -1;
    long long toMax = -1;

    while (fileLog.getline(buffer, 65536))
    {
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
 
        int leftRequest = start;
        int rightRequest = end;

        start = end + 1;
        end = FindSymbol(buffer, start + 1, ' ');
        int num = StringToInt(buffer, start + 1, end);
        if (start == -1 || end == -1 || end - start < 2 || num < 500 || num > 599)
            continue;
        
        lineLog.status = num;
        lineLog.timeInt = lineLog.LocalTimeToInt();
        if (lineLog.timeInt < args.fromT || lineLog.timeInt > args.toT)
            continue;
        
        char* request = CopyString(buffer, leftRequest, rightRequest + 1);

        bool flag = true;
        for (long long i = 0; i < requests.length; i++)
        {
            if (IsEqualStrings(requests.list[i], request))
            {
                valuesStats.list[i][0]++;
                flag = false;
                break;
            }
        }

        if (flag)
        {
            requests.Append(request);
            long* val = new long[2];
            val[0] = 1;
            val[1] = (long)(requests.length - 1);
            valuesStats.Append(val);
        }

        if (lastTime == -1)
        {
            lastTime = lineLog.timeInt;
            counter = 1;
        }
        else if (lineLog.timeInt - lastTime <= args.windowT)
        {
            counter++;
            if (resultCounter < counter)
            {
                fromMax = lastTime;
                toMax = lineLog.timeInt;
            }
        }
        else
        {
            resultCounter = resultCounter < counter ? counter : resultCounter;
            counter = 1;
            lastTime = lineLog.timeInt;
        }
        
        if (flags.print)
            std::cout << buffer << std::endl;

        if (flags.output)
            fileOutput << buffer << std::endl;
    }

    printf("\n-----------STATS for %d requests-----------\n", args.statsN > valuesStats.length ? 
    (int)valuesStats.length : args.statsN);
    
    QuickSort(valuesStats.list, 0, valuesStats.length - 1, valuesStats.length, args.statsN);

    for (int i = 0; i < args.statsN && i < valuesStats.length; i++)
        printf("[%d] %s  ---  %ld\n", i + 1, requests.list[valuesStats.list[valuesStats.length - 1 - i][1]], 
        valuesStats.list[valuesStats.length - 1 - i][0]);
    
    printf("\n");
    
    printf("The maximum number of requests lasting %d seconds per interval from %lld to %lld is %lld\n\n", args.windowT, 
    fromMax, toMax, resultCounter);

    fileLog.close();
    fileOutput.close();

    return 0;
}