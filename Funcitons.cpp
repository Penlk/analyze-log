#include <iostream>
using namespace std;

bool IsEqualStrings(char* a, char* b)
{
    for (int i = 0; ;i++)
    {
        if (a[i] != b[i])
            return false;
        
    }

    return true;
}