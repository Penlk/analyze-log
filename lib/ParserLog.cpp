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

    MyList<char*> requests;
    MyList<long*> valuesStats;

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
 
        int leftRequest = start;
        int rightRequest = end;

        start = end + 1;
        end = FindSymbol(buffer, start + 1, ' ');
        int num = StringToInt(buffer, start + 1, end);
        if (start == -1 || end == -1 || end - start < 2 || num < 500 || num > 599)
            continue;
        
        lineLog.status = num;
        lineLog.LocalTimeToInt();
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


        
        if (flags.print)
            std::cout << buffer << std::endl;

        // end = FindSymbol(buffer, end, '\0');
        // buffer[end] = '\n';
        if (flags.output)
            fileOutput << buffer << std::endl;
    }

    printf("\n-----------STATS for %d requests-----------\n", args.statsN > valuesStats.length ? (int)valuesStats.length : args.statsN);
    QuickSort(valuesStats.list, 0, valuesStats.length - 1, valuesStats.length, args.statsN);
    for (int i = 0; i < args.statsN && i < valuesStats.length; i++)
        printf("[%d] %s  ---  %ld\n", i + 1, requests.list[valuesStats.list[valuesStats.length - 1 - i][1]], 
        valuesStats.list[valuesStats.length - 1 - i][0]);
    printf("\n");
    fileLog.close();
    fileOutput.close();
    return 0;
}