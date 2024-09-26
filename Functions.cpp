#include <iostream>

bool IsEqualStrings(char* a, char* b)
{   
    for (int i = 0;; i++)
    {
        if (a[i] != b[i] || ((a[i] == '\0') != (b[i] == '\0')))
            return false;
        if (a[i] == '\0' || b[i] == '\0')
            return true;
    }

    return true;
}

bool IsEqualStringsFragment(char* a, char* b, int ceillingB)
{
    for (int i = 0; i < ceillingB; i++)
    {
        if (a[i] != b[i] || ((a[i] == '\0') != (b[i] == '\0')))
            return false;
        if (a[i] == '\0' || b[i] == '\0')
            return true;
    }

    return true;
}

int StringLength(char* str)
{
    int l = 0;
    while (str[l] != '\0')
        l++;
    
    return l;
}

int StringToInt(char* str) //Возвращает -1, если строка имеет не цифру.
{
    int result = 0;
    int r = 1;
    for (int i = StringLength(str) - 1; i > -1; i--)
    {
        if (str[i] > 57 || str[i] < 48)
            return -1;

        result += (str[i] - 48) * r;
        r *= 10;
    }

    return result;
}

int StringToInt(char* str, int start, int end) //Возвращает -1, если промежуток [start, end] имеет не цифру.
{
    int result = 0;
    int r = 1;
    for (int i = end - 1; i >= start; i--)
    {
        if (str[i] > '9' || str[i] < '0')
            return -1;

        result += (str[i] - 48) * r;
        r *= 10;
    }

    return result;
}