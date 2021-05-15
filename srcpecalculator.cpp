#include "application.h"

// Main entrypoint for executable.
int main(int argc, char* argv[])
{
    std::string fn = "";
    if (Application::getInstance().parseCmdLine(argc, argv, fn))
    {
        return Application::getInstance().run(fn);
    }
}
