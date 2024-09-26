#include <time.h>
struct ValuesArgs
{
    char* pathFileLog = nullptr;
    char* pathFileOutput = nullptr;
    int statsN = 10;
    int windowT = 0;
    int fromT = 0;
    int toT = time(0);
    void IndexToFieldValue(int i, int value);
};

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

int Parse(int argc, char** argv, IsCommands& flags, ValuesArgs& args);