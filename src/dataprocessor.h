#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <map>
#include <vector>
#include <string>

class DataProcessor
{
public:
    DataProcessor() {}
    ~DataProcessor() {};

    bool parseDataValue(const std::string& fileline);
    bool parseDataCmd(const std::string& fileline);

private:
    std::map<std::string, int> s_Data;
    int string2Int(const std::string& input);
    int runCmd(const std::string& cmd, const std::vector<int>& vals);

    // Avoid copy constructor.
    DataProcessor(const DataProcessor&);
    DataProcessor& operator=(const DataProcessor&);
};
#endif
