#include "AllStructs.h"
#include "Functions.h"

void CommandFlags::SetFlagByIndex(int argumentIndex)
{
    argumentFlags[argumentIndex] = true;
    switch (argumentIndex)
    {
        case 0:
            outputEnabled = true;
            break;
        case 1:
            printEnabled = true;
            break;
        case 2:
            statsEnabled = true;
            break;
        case 3:
            windowEnabled = true;
            break;
        case 4:
            fromEnabled = true;
            break;
        case 5:
            toEnabled = true;
            break;
    }
}


void ArgumentValues::SetValueByIndex(int index, long long value)
{
    switch (index)
    {
        case 2:
            statsCount = value;
            break;
        case 3:
            windowDuration = value;
            break;
        case 4:
            fromTime = value;
            break;
        case 5:
            toTime = value;
            break;
    }
}


long long LogValues::ConvertLocalTimeToInt()
{
    if (localTimeRight - localTimeLeft + 1 < 23)
        return -1;

    int startPos = localTimeLeft + 1;
    int endPos = FindSymbol(logEntry, localTimeLeft, '/');
    int day = ConvertStringToInt(logEntry, startPos, endPos);

    startPos = endPos + 1;
    endPos = FindSymbol(logEntry, startPos, '/');
    char* month = CopyString(logEntry, startPos, endPos);

    startPos = endPos + 1;
    endPos = FindSymbol(logEntry, startPos, ':');
    int year = ConvertStringToInt(logEntry, startPos, endPos);

    startPos = endPos + 1;
    endPos = FindSymbol(logEntry, startPos, ':');
    int hour = ConvertStringToInt(logEntry, startPos, endPos);

    startPos = endPos + 1;
    endPos = FindSymbol(logEntry, startPos, ':');
    int minute = ConvertStringToInt(logEntry, startPos, endPos);

    startPos = endPos + 1;
    endPos = FindSymbol(logEntry, startPos, ' ');
    int second = ConvertStringToInt(logEntry, startPos, endPos);

    startPos = endPos + 1;
    bool minus = logEntry[startPos] == '-' ? -1 : 1;
    hour += minus * ConvertStringToInt(logEntry, startPos + 1, startPos + 3);
    minute += minus * ConvertStringToInt(logEntry, startPos + 3, startPos + 5);

    if (endPos >= localTimeRight)
        return -1;

    return TranslateTime(day, month, year, hour, minute, second);
}


template<typename T>
void MyList<T>::Append(T element)
{
    length++;

    if (length > maxLength)
    {
        T* newList = new T[maxLength * 2];
        for (int i = 0; i < maxLength; i++)
            newList[i] = list[i];

        delete[] list;
        list = newList;
        maxLength *= 2;
    }

    list[length - 1] = element;
}


template struct MyList<char*>;
template struct MyList<long*>;