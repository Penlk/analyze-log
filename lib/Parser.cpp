#include <iostream>
#include "Functions.h"
#include "AllStructs.h"

char* fullArgs[] = {"--output", "--print", "--stats", "--window", "--from", "--to"};
char* reduceArgs[] = {"-o", "-p", "-s", "-w", "-f", "-t"};

int IndexFullArgument(char* str) //Выводит индекс полного аргумента, если не полный аргумент выводит -1
{
    for (int i = 0; i < 6; i++)
        if (AreStringsEqual(fullArgs[i], str, GetStringLength(fullArgs[i])))
            return i;
    
    return -1;
}

int IndexReduceArgument(char* str) //Выводит индекс сокращенного аргумента, если не сокращенный аргумент выводит -1
{
    if (GetStringLength(str) != 2)
        return -1;

    for (int i = 0; i < 6; i++)
        if (AreStringsEqual(str, reduceArgs[i]))
            return i;
    
    return -1;
}

int Parse(int argc, char** argv, CommandFlags& flags, ArgumentValues& args)
{
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    int lastArg = -1;

    for (int i = 1; i < argc; i++)
    {
        int lengthThisArg = GetStringLength(argv[i]);
        int fullArgIndex = IndexFullArgument(argv[i]);
        int reduceArgIndex = IndexReduceArgument(argv[i]);

        if (lastArg == 0)
        {
            if (args.pathFileOutput != nullptr)
            {
                printf("Writting the 2nd same argument\n%s\n", argv[i - 1]);
                return 1;
            }
            
            if (fullArgIndex != -1 || reduceArgIndex != -1)
            {
                printf("The argument cannot be a value\n%s\n", argv[i]);
                return 1;
            }

            args.pathFileOutput = argv[i];
            flags.SetFlagByIndex(0);
            lastArg = -1;
            continue;
        }

        if (fullArgIndex == -1 && reduceArgIndex == -1)
        {
            if (lastArg != -1 && lastArg != 1)
            {
                long long num = ConvertStringToInt(argv[i]);
                if (num == -1)
                {
                    printf("The argument {%s} cannot be executed without argument\n", argv[i - 1]);
                    return 1;
                }

                args.SetValueByIndex(lastArg, num);
                lastArg = -1;
            } else
            {
                if (flags.logEnabled)
                {
                    printf("Cannot be exist the two or more logs\n%s\n", argv[i]);
                    return 1;
                } else
                {
                    flags.logEnabled = true;
                    args.pathFileLog = argv[i];
                    lastArg = -1;
                    continue;
                }
            }
        }
        else if (reduceArgIndex != -1)
        {
            if (lastArg != -1 && lastArg != 1)
            {
                printf("The argument {%s} cannot be executed without argument\n", argv[i - 1]);
                return 1;
            }
            if (flags.argumentFlags[reduceArgIndex])
            {
                printf("Writting the 2nd same argument\n%s\n", argv[i]);
                return 1;
            }

            flags.SetFlagByIndex(reduceArgIndex);
            lastArg = reduceArgIndex;
        }
        else if (fullArgIndex != -1)
        {
            if (flags.argumentFlags[fullArgIndex])
            {
                if (argv[i][GetStringLength(fullArgs[fullArgIndex])] != '=' && lengthThisArg > GetStringLength(fullArgs[fullArgIndex]))
                {
                    if (flags.logEnabled)
                    {
                        printf("Cannot be exist the two or more logs\n%s\n", argv[i]);
                        return 1;
                    } else
                    {
                        flags.logEnabled = true;
                        args.pathFileLog = argv[i];
                        lastArg = -1;
                        continue;
                    }
                }

                printf("Writting the 2nd same argument\n%s\n", argv[i]);
                return 1;
            }

            if (lengthThisArg == GetStringLength(fullArgs[fullArgIndex]))
            {
                flags.SetFlagByIndex(fullArgIndex);
                lastArg = fullArgIndex;
            } else
            {
                if (argv[i][GetStringLength(fullArgs[fullArgIndex])] != '=' || lengthThisArg <= GetStringLength(fullArgs[fullArgIndex]) + 1)
                {
                    printf("Incorrect argument\n%s\n", argv[i]);
                    return 1;
                }

                if (fullArgIndex == 0)
                {
                    flags.SetFlagByIndex(fullArgIndex);
                    args.pathFileOutput = argv[i] + GetStringLength(fullArgs[fullArgIndex]) + 1;
                    lastArg = -1;
                    continue;
                }

                flags.SetFlagByIndex(fullArgIndex);
                args.SetValueByIndex(fullArgIndex, ConvertStringToInt(argv[i] + GetStringLength(fullArgs[fullArgIndex]) + 1));
                lastArg = -1;
            }
        }
    }

    if (lastArg != -1 && lastArg != 1)
    {
        printf("Cannot be {%s} without argument\n", argv[argc - 1]);
        return 1;
    }

    if (flags.outputEnabled && args.pathFileOutput == nullptr)
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