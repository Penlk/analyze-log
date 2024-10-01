#include <iostream>
#include "AllStructs.h"
#include "Functions.h"
#include <fstream>
#include <deque>

int ParserLog(CommandFlags flags, ArgumentValues args)
{
    std::ifstream fileLog;
    fileLog.open(args.pathFileLog);

    if (!fileLog.is_open())
    {
        std::cerr << "Cannot open the log file\n" << args.pathFileLog << std::endl;
        return 1;
    }

    std::ofstream fileOutput;
    if (flags.outputEnabled)
    {
        fileOutput.open(args.pathFileOutput);
        if (!fileOutput.is_open())
        {
            std::cerr << "Cannot create or open the file\n" << args.pathFileOutput << std::endl;
            return 1;
        }
    }

    if (!fileOutput.is_open())
    {
        std::cerr << "Nothint to do without output file\n";
        return 1;
    }

    char buffer[65536];

    MyList<char*> requests;
    MyList<long*> valuesStats;

    long long lastTime = -1;
    long long resultCounter = 0;
    long long counter = 0;
    long long fromMax = -1;
    long long toMax = -1;
    
    std::deque<long long> prefix;

    while (fileLog.getline(buffer, 65536))
    {
        buffer[65535] = '\0';

        LogValues lineLog;
        int start = FindSymbol(buffer, 0, '[');
        int end = FindSymbol(buffer, start, ']');
        if (start == -1 || end == -1)
            continue;
        
        lineLog.logEntry = buffer;
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
        int num = ConvertStringToInt(buffer, start + 1, end);
        lineLog.status = num;
        lineLog.timeInt = lineLog.ConvertLocalTimeToInt();

        if (lineLog.timeInt < args.fromTime || lineLog.timeInt > args.toTime)
            continue;
        
        while (counter > 0 && lineLog.timeInt - prefix.back() >= args.windowDuration)
        {
            prefix.pop_back();
            counter--;
        }

        counter++;
        prefix.push_front(lineLog.timeInt);
        if (resultCounter < counter)
        {
            resultCounter = counter;
            fromMax = prefix.back();
            toMax = lineLog.timeInt;
        }

        if (start == -1 || end == -1 || end - start < 2 || num < 500 || num > 599)
            continue;
        
        char* request = CopyString(buffer, leftRequest, rightRequest + 1);

        bool flag = true;
        for (long long i = 0; i < requests.length; i++)
        {
            if (AreStringsEqual(requests.list[i], request))
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
        
        if (flags.printEnabled)
            std::cout << buffer << std::endl;

        if (flags.outputEnabled)
            fileOutput << buffer << std::endl;
    }

    printf("\n----------------------STATS for %lld requests----------------------\n", args.statsCount > valuesStats.length ? 
    valuesStats.length : args.statsCount);
    
    QuickSort(valuesStats.list, 0, valuesStats.length - 1, valuesStats.length, args.statsCount);

    for (int i = 0; i < args.statsCount && i < valuesStats.length; i++)
    {
        printf("[%d] %s  ---  %ld\n", i + 1, requests.list[valuesStats.list[valuesStats.length - 1 - i][1]], 
        valuesStats.list[valuesStats.length - 1 - i][0]);
    }

    printf("-------------------------------------------------------------------\n");
    
    if (args.windowDuration == 0)
        resultCounter = 0;
    
    printf("\nThe maximum number of requests lasting %d seconds per interval from %lld to %lld is %lld\n\n", args.windowDuration, 
    fromMax, toMax, resultCounter);

    return 0;
}