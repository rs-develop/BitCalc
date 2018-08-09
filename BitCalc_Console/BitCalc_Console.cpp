
#include <iostream>
#include <string>

#include "BitCalc.h"

//-------------------------------------------------------------------------------------------------------------
static void show_help(std::string name)
{
    std::cerr << "Usage: " << name << " [HEX VALUE]\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-v,--version\t\tOutput version information"
              << std::endl;
}//end show help

//-------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            show_help(argv[0]);
            return 1;
        }//end if

        BitCalc calc;

        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.compare(0, 2, "0x") == 0)
                arg = arg.substr(2, arg.size());
            if ((arg == "-h") || (arg == "--help"))
            {
                show_help(argv[0]);
                return 0;
            }//end help
            else if ((arg == "-v") || (arg == "--version"))
            {
                std::cout << calc.getBitCalcVersion() << std::endl;
            }//end version
            else if (arg.find_first_not_of("0123456789abcdefABCDEF", 0) == std::string::npos)
            {
                //Add hex string to bit calc
                calc.insertByteValue(arg);
                calc.printAllToStdOut();
            }
            else
            {
                std::cerr << "Error: " << arg << " is a invalid hex value." << std::endl;
                show_help(argv[0]);
            }//end
        }//end for

    }//end try
    catch (BitCalcBaseException &ex)
    {
        std::cout << ex.what() << std::endl;
    }//end catch

    return 0;
}//end main

//-------------------------------------------------------------------------------------------------------------
