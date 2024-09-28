#include "AllStructs.h"
#include "../Functions.h"

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
    int start = 1;
    int end = FindSymbol(localTime, start, '/');
    int day = StringToInt(localTime, start, end);

    start = end + 1;
    end = FindSymbol(localTime, start, '/');
    char* month = CopyString(localTime, start, end);

    start = end + 1;
    end = FindSymbol(localTime, start, ':');
    int year = StringToInt(localTime, start, end);

    start = end + 1;
    end = FindSymbol(localTime, start, ':');
    int hour = StringToInt(localTime, start, end);

    start = end + 1;
    end = FindSymbol(localTime, start, ':');
    int minute = StringToInt(localTime, start, end);

    start = end + 1;
    end = FindSymbol(localTime, start, ' ');
    int second = StringToInt(localTime, start, end);

    return TranslateTime(day, month, year, hour, minute, second);
}