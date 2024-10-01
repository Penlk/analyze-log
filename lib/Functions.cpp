#include <iostream>

bool AreStringsEqual(char* a, char* b)
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


bool AreStringsEqual(char* a, char* b, int ceillingB)
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


int GetStringLength(char* str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    
    return length;
}


long long ConvertStringToInt(char* str) //Возвращает -1, если строка имеет не цифру.
{
    long long result = 0;
    long long r = 1;
    for (int i = GetStringLength(str) - 1; i > -1; i--)
    {
        if (str[i] > 57 || str[i] < 48)
            return -1;

        result += (long long)((str[i] - 48) * r);
        r *= 10;
    }

    return result;
}


long long ConvertStringToInt(char* str, int start, int end) //Возвращает -1, если промежуток [start, end] имеет не цифру.
{
    long long result = 0;
    long long r = 1;
    for (int i = end - 1; i >= start; i--)
    {
        if (str[i] > '9' || str[i] < '0')
            return -1;

        result += (long long)((str[i] - 48) * r);
        r *= 10;
    }

    return result;
}


char* CopyString(char* str, int start, int end)
{
    char* result = new char[end - start + 1];

    for (int i = start; i < end; i++)
        result[i - start] = str[i];
    
    result[end - start] = '\0';
    return result;
}


bool IsLeapYear(int year)
{
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}


int GetMonthIndex(char* month)
{
    char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    for (int i = 0; i < 12; ++i)
    {
        if (AreStringsEqual(months[i], month))
            return i;
    }

    return -1; // Неправильный формат месяца.
}


long long TranslateTime(int days, char* month, int year, int hours, int minutes, int seconds) //Гарантировано, что все данные в правильном формате
{
    int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long long allSeconds = (days - 1) * 86400 + hours * 3600 + minutes * 60 + seconds;

    for (int i = 1970; i < year; i++)
        allSeconds += (i % 400 == 0 || (i % 100 != 0 && i % 4 == 0)) * 24 * 60 * 60 + 365 * 24 * 60 * 60;
    
    int monthIndex = GetMonthIndex(month);
    if (monthIndex == -1)
        return -1;

    daysInMonths[1] += IsLeapYear(year);
    for (int m = 0; m < monthIndex; m++)
        allSeconds += daysInMonths[m] * 86400;
    
    return allSeconds;
}


int FindSymbol(char* str, int start, char symbol) //Возвращает -1, если не натыкается на '\0' || '\n'
{
    int end = start;
    while (str[end] != symbol)
    {
        if (str[end] == '\0' || str[end] == '\n')
            return -1;
        
        end++;
    }

    return end;
}


long Partition(long** arr, long l, long r)
{
    long pivot = arr[l][0];

    int i = l - 1;
    int j = r + 1;

    while (true)
    {
        do {i++;} while (arr[i][0] < pivot);

        do {j--;} while (arr[j][0] > pivot);

        if (i >= j)
            return j;

        long* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


void QuickSort(long** arr, long l, long r, long length, long n)
{
    if (l >= r)
        return;

    long mid = Partition(arr, l, r);

    if (length - l <= n || length - mid <= n)
        QuickSort(arr, l, mid, length, n);

    QuickSort(arr, mid + 1, r, length, n);
}