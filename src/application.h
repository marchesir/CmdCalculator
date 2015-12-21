#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>

class Application
{
public:
    static Application& getInstance();
    int run(const std::string& filename);
    bool parseCmdLine(int argc, char* argv[], std::string& filename);

private:
    // Utility methods.
    void printUsage();

    // Private constructor/Destructor required by Singleton pattern.
    Application() {};
    ~Application() {};

    // Avoid copy constructor.
    Application(const Application&);
    Application& operator=(const Application&);
};
#endif
