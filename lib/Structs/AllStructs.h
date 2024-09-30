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
    bool* args = new bool[6]{false, false, false, false, false, false};
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

    void IndexToFieldValue(int i, long long value);
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

template<typename T>
struct MyList
{
    T* list = new T[1];
    long long maxLength = 1;
    long long length = 0;

    void Append(T str);
};
