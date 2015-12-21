#include "application.h"
#include "dataprocessor.h"
#include <fstream>

// Public methods.

// Singleton Pattern access.
Application& Application::getInstance()
{
    static Application app;
    return app;
}

// Program event loop.
int Application::run(const std::string& filename)
{
    std::cout << "<-- Application::run [CmdCalculator START]" << std::endl;
    std::cout << "<-- Application::run [CmdCalculator: processing" << filename << "]" << std::endl;

    std::ifstream inputfile(filename, std::ios::in);
    DataProcessor* dp = new DataProcessor();
    std::string readline;

    try
    {
        // 1. Process input file.
        while (inputfile.is_open() && std::getline(inputfile, readline) )
        {
            if (!dp->parseDataValue(readline))
            {
                if(!dp->parseDataCmd(readline))
                {
                    std::cout << "<-- Application::run [ERROR: unable to process fileline <<" << readline << ">>]" << std::endl;
                }
            }
        }
        inputfile.close();
    }
    catch(...)
    {
        std::cout << "<-- Application::run [ERROR: problem opening inputfile]" << std::endl;
        inputfile.close();
    }

    // Clean up allocated data on heap.
    if (dp != nullptr)
    {
        delete dp;
    }

    std::cout << "<-- Application::run [CmdCalculator END]" << std::endl;

    return 0;
}

// Parse passed cmd lines args, acepting only 1 argument beeing input filename,
// if not satisfied exit and show usage message.
bool Application::parseCmdLine(int argc, char* argv[], std::string& filename)
{
    bool ret = false;

    if (argc <= 1 || argc > 2)
    {
        printUsage();
    }
    else
    {
        filename = argv[1];  // Pointer array to second cmd arg.
        ret = true;
    }

    return ret;
}

// Private methods.

// Print to std console usage message.
void Application::printUsage()
{
    std::cout << "<-- Application::printUsage [CmdCalculator filename {where filename is input filename}]" << std::endl;
}
