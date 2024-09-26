#include <iostream>
#include <time.h>
#include "Functions.h"

struct IsCommands
{
    bool log = false;
    bool output = false; //0
    bool print = false; //1
    bool stats = false; //2
    bool window = false; //3
    bool from = false; //4
    bool to = false; //5
    bool args[6];
    
    void IndexToField(int i)
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
};

struct ValuesArgs
{
    char* pathFileLog = nullptr;
    char* pathFileOutput = nullptr;
    int statsN = 10;
    int windowT = 0;
    int fromT = 0;
    int toT = time(0);
    void IndexToFieldValue(int i, int value)
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
};

char* fullArgs[] = {"--output", "--print", "--stats", "--window", "--from", "--to"};
char* reduceArgs[] = {"-o", "-p", "-s", "-w", "-f", "-t"};

int IndexFullArgument(char* str) //Выводит индекс полного аргумента, если не полный аргумент выводит -1
{
    for (int i = 0; i < 6; i++)
        if (IsEqualStringsFragment(fullArgs[i], str, StringLength(fullArgs[i])))
            return i;
    
    return -1;
}

int IndexReduceArgument(char* str) //Выводит индекс сокращенного аргумента, если не сокращенный аргумент выводит -1
{
    if (StringLength(str) != 2)
        return -1;

    for (int i = 0; i < 6; i++)
        if (IsEqualStrings(str, reduceArgs[i]))
            return i;
    
    return -1;
}

int Parse(int argc, char** argv, IsCommands& flags, ValuesArgs& args)
{
    //Определение: слово - argv[i]
    //Постулат 1: Если какое-то слово является названием аргумента, то это и есть аргумент
    //Постулат 2: Если какое-то слово, не являющееся аргументом, идет после аргумента, то такой случай имеет действие в 2 этапа с разными приоритетами
    //  Этап 1 (приоритет 0): Пытаемся присвоить аргументу слово
    //  Этап 2 (приоритет 1): Это лог
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    int lastArg = -1;

    for (int i = 1; i < argc; i++)
    {
        int lengthThisArg = StringLength(argv[i]);
        int fullArg = IndexFullArgument(argv[i]);
        int reduceArg = IndexReduceArgument(argv[i]);

        if (lastArg == 0)
        {
            if (args.pathFileOutput != nullptr)
            {
                printf("Writting the 2nd same argument\n%s\n", argv[i - 1]);
                return 1;
            }
            
            if (fullArg != -1 || reduceArg != -1)
            {
                printf("The argument cannot be a value\n%s\n", argv[i]);
                return 1;
            }

            args.pathFileOutput = argv[i];
            flags.IndexToField(0);
            lastArg = -1;
            continue;
        }

        if (fullArg == -1 && reduceArg == -1)
        {
            if (lastArg != -1 && lastArg != 1)
            {
                int num = StringToInt(argv[i]);
                if (num == -1)
                {
                    printf("Cannot {%s} without argument\n", argv[i - 1]);
                    return 1;
                }

                args.IndexToFieldValue(lastArg, num);
                lastArg = -1;
            } else
            {
                if (flags.log)
                {
                    printf("The 2nd log\n%s\n", argv[i]);
                    return 1;
                } else
                {
                    flags.log = true;
                    args.pathFileLog = argv[i];
                    lastArg = -1;
                    continue;
                }
            }
        }
        else if (reduceArg != -1)
        {
            if (lastArg != -1 && lastArg != 1)
            {
                printf("Cannot be {%s} without argument\n", argv[i - 1]);
                return 1;
            }
            if (flags.args[reduceArg])
            {
                printf("Writting the 2nd same argument\n%s\n", argv[i]);
                return 1;
            }

            flags.IndexToField(reduceArg);
            lastArg = reduceArg;
        }
        else if (fullArg != -1)
        {
            if (flags.args[fullArg])
            {
                printf("Writting the 2nd same argument\n%s\n", argv[i]);
                return 1;
            }

            if (lengthThisArg == StringLength(fullArgs[fullArg]))
            {

                flags.IndexToField(fullArg);
                lastArg = fullArg;
            } else
            {
                if (argv[i][StringLength(fullArgs[fullArg])] != '=' || lengthThisArg <= StringLength(fullArgs[fullArg]) + 1)
                {
                    printf("Incorrect argument\n%s\n", argv[i]);
                    return 1;
                }

                if (fullArg == 0)
                {
                    flags.IndexToField(fullArg);
                    args.pathFileOutput = argv[i] + StringLength(fullArgs[fullArg]) + 1;
                    lastArg = -1;
                    continue;
                }

                flags.IndexToField(fullArg);
                args.IndexToFieldValue(fullArg, StringToInt(argv[i] + StringLength(fullArgs[fullArg]) + 1));
                lastArg = -1;
            }
        }
    }

    if (lastArg != -1 && lastArg != 1)
    {
        printf("Cannot be {%s} without argument\n", argv[argc - 1]);
        return 1;
    }

    if (flags.output && args.pathFileOutput == nullptr)
    {
        printf("Argument output is empty\n");
        return 1;
    }

    if (args.pathFileLog == nullptr)
    {
        printf("Cannot analyze without log file\n");
        return 1;
    }

    return 0;
}