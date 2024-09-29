#include "AllStructs.h"
#include "../Functions.h"
#include <iostream> //Убрать

void IsCommands::IndexToField(int i)
{
    args[i] = true;
    switch (i)
    {
    case 0:
        output = true;
        break;
    case 1:
        print = true;
        break;
    case 2:
        stats = true;
        break;
    case 3:
        window = true;
        break;
    case 4:
        from = true;
        break;
    case 5:
        to = true;
        break;
    }
}

void ValuesArgs::IndexToFieldValue(int i, int value)
{
    switch (i)
    {
    case 2:
        statsN = value;
        break;
    case 3:
        windowT = value;
        break;
    case 4:
        fromT = value;
        break;
    case 5:
        toT = value;
        break;
    }
}

long long ValuesLog::LocalTimeToInt() //[localTime]
{
    if (localTimeRight - localTimeLeft + 1 < 23)
        return -1;
    
    int start = localTimeLeft + 1;
    int end = FindSymbol(str, localTimeLeft, '/');
    int day = StringToInt(str, start, end);

    start = end + 1;
    end = FindSymbol(str, start, '/');
    char* month = CopyString(str, start, end);

    start = end + 1;
    end = FindSymbol(str, start, ':');
    int year = StringToInt(str, start, end);

    start = end + 1;
    end = FindSymbol(str, start, ':');
    int hour = StringToInt(str, start, end);

    start = end + 1;
    end = FindSymbol(str, start, ':');
    int minute = StringToInt(str, start, end);

    start = end + 1;
    end = FindSymbol(str, start, ' ');
    int second = StringToInt(str, start, end);

    if (end >= localTimeRight)
        return -1;

    return TranslateTime(day, month, year, hour, minute, second);
}