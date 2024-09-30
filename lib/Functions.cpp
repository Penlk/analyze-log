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

long long StringToInt(char* str) //Возвращает -1, если строка имеет не цифру.
{
    long long result = 0;
    long long r = 1;
    for (int i = StringLength(str) - 1; i > -1; i--)
    {
        if (str[i] > 57 || str[i] < 48)
            return -1;

        result += (long long)((str[i] - 48) * r);
        r *= 10;
    }

    return result;
}

long long StringToInt(char* str, int start, int end) //Возвращает -1, если промежуток [start, end] имеет не цифру.
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


int MonthDays(char* month) //Без високосного кода
{
    // Выводит -1, если формат месяца неправильный
    if (IsEqualStrings(month, "Jan") || IsEqualStrings(month, "Mar") || IsEqualStrings(month, "May") || 
    IsEqualStrings(month, "Jul") || IsEqualStrings(month, "Aug") || IsEqualStrings(month, "Oct") || IsEqualStrings(month, "Dec"))
        return 31;
    else if (IsEqualStrings(month, "Feb"))
        return 28;
    else if (IsEqualStrings(month, "Apr") || IsEqualStrings(month, "Jun") || IsEqualStrings(month, "Sep") || IsEqualStrings(month, "Nov"))
        return 30;
    
    return -1;
}

char* IndexToMonth(int index)
{
    char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return months[index];
}

long long TranslateTime(int days, char* month, int year, int hours, int minutes, int seconds) //Гарантировано, что все данные в правильном формате
{
    long long result = (days - 1) * 24 * 60 * 60 + hours * 60 * 60 + minutes * 60 + seconds;
    for (int i = 1970; i < year; i++)
        result += (i % 400 == 0 || (i % 100 != 0 && i % 4 == 0)) * 24 * 60 * 60 + 365 * 24 * 60 * 60;
    

    //WARNING
    //Плохая реализация, переделать
    for (int m = 0; !IsEqualStrings(IndexToMonth(m), month) && m < 12; m++)
        result += MonthDays(IndexToMonth(m)) * 24 * 60 * 60;
    
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        if (!IsEqualStrings(month, "Jan") || !IsEqualStrings(month, "Feb"))
            result += 24 * 60 * 60;
    
    return result;
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
        do
            i++;
        while (arr[i][0] < pivot);

        do
            j--;
        while (arr[j][0] > pivot);

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