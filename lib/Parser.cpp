#include <iostream>
#include "Functions.h"
#include "Structs/AllStructs.h"

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

        // printf("[%d]Arg: %s\tFull: %d\t Reduce: %d\t [", i, argv[i], fullArg, reduceArg);
        // for (int i = 0; i < 6; i++)
        //     printf("%d, ", (int)flags.args[i]);
        // printf("]\n");

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
                if (argv[i][StringLength(fullArgs[fullArg])] != '=' && lengthThisArg > StringLength(fullArgs[fullArg]))
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