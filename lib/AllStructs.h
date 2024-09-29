#pragma once

struct IsCommands
{
    bool log = false;
    bool output = false;
    bool print = false;
    bool stats = false;
    bool window = false;
    bool from = false;
    bool to = false;
    bool args[6];
    void IndexToField(int i);
};

struct ValuesArgs
{
    char* pathFileLog = nullptr;
    char* pathFileOutput = nullptr;
    int statsN = 10;
    int windowT = 0;
    long long fromT = 0;
    long long toT = 17274350860000;

    void IndexToFieldValue(int i, int value);
};

struct ValuesLog
{
    char* str;
    int localTimeLeft;
    int localTimeRight;
    int status;
    long long timeInt;

    long long LocalTimeToInt();
};
