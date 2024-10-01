#include <limits>
#pragma once

struct CommandFlags
{
    bool logEnabled = false;
    bool outputEnabled = false;
    bool printEnabled = false;
    bool statsEnabled = false;
    bool windowEnabled = false;
    bool fromEnabled = false;
    bool toEnabled = false;
    bool* argumentFlags = new bool[6]{false, false, false, false, false, false};
    void SetFlagByIndex(int argumentIndex);
};


struct ArgumentValues
{
    char* pathFileLog = nullptr;
    char* pathFileOutput = nullptr;
    int statsCount = 10;
    int windowDuration = 0;
    long long fromTime = 0;
    long long toTime = std::numeric_limits<long long>::max();

    void SetValueByIndex(int argumentIndex, long long value);
};


struct LogValues
{
    char* logEntry;
    int localTimeLeft;
    int localTimeRight;
    int status;
    long long timeInt;

    long long ConvertLocalTimeToInt();
};


template<typename T>
struct MyList
{
    T* list = new T[1];
    long long maxLength = 1;
    long long length = 0;

    void Append(T element);
};
