#include <iostream>
#include "Functions.h"
#include "AllStructs.h"

int FindArgumentIndex(char* str, char** args, int argCount) 
{
    for (int i = 0; i < argCount; i++) 
        if (AreStringsEqual(args[i], str, GetStringLength(args[i])))
            return i;

    return -1;
}


enum NamesArgs {output, print, stats, window, from, to, nothing = -1};


int Parse(int argc, char** argv, CommandFlags& flags, ArgumentValues& args)
{
    char* fullArgs[] = {"--output", "--print", "--stats", "--window", "--from", "--to"};
    char* reduceArgs[] = {"-o", "-p", "-s", "-w", "-f", "-t"};
    const int argCount = 6;

    NamesArgs lastArg = nothing;

    for (int i = 1; i < argc; i++)
    {
        int lengthThisArg = GetStringLength(argv[i]);
        int fullArgIndex = FindArgumentIndex(argv[i], fullArgs, argCount);
        int reduceArgIndex = FindArgumentIndex(argv[i], reduceArgs, argCount);

        if (lastArg == output)
        {
            if (args.pathFileOutput != nullptr)
            {
                std::cerr << "Writting the 2nd same argument\n" << argv[i - 1] << std::endl;
                return 1;
            }
            
            if (fullArgIndex != -1 || reduceArgIndex != -1)
            {
                std::cerr << "The argument cannot be a value\n" << argv[i] << std::endl;
                return 1;
            }

            args.pathFileOutput = argv[i];
            flags.SetFlagByIndex(0);
            lastArg = nothing;
            continue;
        }

        if (fullArgIndex == -1 && reduceArgIndex == -1)
        {
            if (lastArg != nothing && lastArg != print)
            {
                long long num = ConvertStringToInt(argv[i]);
                if (num == -1)
                {
                    std::cerr << "The argument " << argv[i - 1] << " cannot be executed without argument\n";
                    return 1;
                }

                args.SetValueByIndex(lastArg, num);
                lastArg = nothing;
            } else
            {
                if (flags.logEnabled)
                {
                    std::cerr << "Cannot be exist the two or more logs\n" << argv[i] << std::endl;
                    return 1;
                } else
                {
                    flags.logEnabled = true;
                    args.pathFileLog = argv[i];
                    lastArg = nothing;
                    continue;
                }
            }
        }
        else if (reduceArgIndex != -1)
        {
            if (lastArg != nothing && lastArg != print)
            {
                std::cerr << "The argument " << argv[i - 1] << " cannot be executed without argument\n";
                return 1;
            }
            if (flags.argumentFlags[reduceArgIndex])
            {
                std::cerr << "Writting the 2nd same argument\n" << argv[i] << std::endl;
                return 1;
            }

            flags.SetFlagByIndex(reduceArgIndex);
            lastArg = (NamesArgs)reduceArgIndex;
        }
        else if (fullArgIndex != -1)
        {
            if (flags.argumentFlags[fullArgIndex])
            {
                if (argv[i][GetStringLength(fullArgs[fullArgIndex])] != '=' && lengthThisArg > GetStringLength(fullArgs[fullArgIndex]))
                {
                    if (flags.logEnabled)
                    {
                        std::cerr << "Cannot be exist the two or more logs\n" << argv[i] << std::endl;
                        return 1;
                    } else
                    {
                        flags.logEnabled = true;
                        args.pathFileLog = argv[i];
                        lastArg = nothing;
                        continue;
                    }
                }

                std::cerr << "Writting the 2nd same argument\n" << argv[i] << std::endl;
                return 1;
            }

            if (lengthThisArg == GetStringLength(fullArgs[fullArgIndex]))
            {
                flags.SetFlagByIndex(fullArgIndex);
                lastArg = (NamesArgs)fullArgIndex;
            } else
            {
                if (argv[i][GetStringLength(fullArgs[fullArgIndex])] != '=' || lengthThisArg <= GetStringLength(fullArgs[fullArgIndex]) + 1)
                {
                    std::cerr << "Incorrect argument\n" << argv[i] << std::endl;
                    return 1;
                }

                if (fullArgIndex == 0)
                {
                    flags.SetFlagByIndex(fullArgIndex);
                    args.pathFileOutput = argv[i] + GetStringLength(fullArgs[fullArgIndex]) + 1;
                    lastArg = nothing;
                    continue;
                }

                flags.SetFlagByIndex(fullArgIndex);
                args.SetValueByIndex(fullArgIndex, ConvertStringToInt(argv[i] + GetStringLength(fullArgs[fullArgIndex]) + 1));
                lastArg = nothing;
            }
        }
    }

    if (lastArg != nothing && lastArg != print)
    {
        std::cerr << "Cannot be " << argv[argc - 1] << " without argument\n";
        return 1;
    }

    if (flags.outputEnabled && args.pathFileOutput == nullptr)
    {
        std::cerr << "Argument output is empty\n";
        return 1;
    }

    if (args.pathFileLog == nullptr)
    {
        std::cerr << "Cannot analyze without log file\n";
        return 1;
    }

    return 0;
}