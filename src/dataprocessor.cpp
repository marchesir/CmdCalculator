#include "dataprocessor.h"
#include <iostream>
#include <string>
#include <sstream>

std::map<std::string, int> s_data;
// Supppoted commands.
static const char* s_commands = { "average" };

// Public methods.

// Based on a single fileline parse for possible data name values pairs as such:
// <VALUE_NAME> = <INTEGER>
bool DataProcessor::parseDataValue(const std::string& fileline)
{
    bool ret = false;
    std::string s = fileline;
    std::string delimiter = "=";
    size_t pos = 0;
    std::string token;

    if ((pos = s.find(delimiter)) != std::string::npos)
    {
        ret = true;
        token = fileline.substr(0, pos);
        token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        s.erase(0, pos + delimiter.length());
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
        int toint = string2Int(s);
        if (!token.empty() && toint != -1)
        {
            // value_name/value ok, add to s_Data lookup map.
            std::cout << "<-- DataProcessor::decodeDataAsValue [token:" << token << "=" << s << "]" << std::endl;
            s_Data[token] = toint;
        }
    }

    return ret;
}

// Based on a single fileline parse for possible commands as such:
// average (<VALUE_NAME1>, <VALUE_NAME2,…)
// Notes: only averge command supported at present.
bool DataProcessor::parseDataCmd(const std::string& fileline)
{
    bool ret = false;
    std::string s = fileline;
    std::string delimiter = "(";
    size_t pos = 0;
    std::string token;
    std::string cmd;
    std::vector<int> vals;

    if ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        s.erase(0, pos + delimiter.length());

        // Check command suppoted.
        std::cout << "<-- DataProcessor::decodeDataAsCmd [token:" << token << "]" << std::endl;
        cmd = token;
        if (cmd.compare(s_commands) == 0)
        {
            s.erase(s.length()-1);  // remove trailing ")".
            std::stringstream ss(s);
            while (getline(ss, token, ','))
            {
                ret = true;
                // Check if only 1 value names exists, if not report error.
                token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
                std::cout << "<-- DataProcessor::decodeDataAsCmd [token:" << token << "]" << std::endl;
                if (s_Data.count(token) != 1)
                {
                    ret = false;
                    break;
                }
                else
                {
                    vals.push_back(s_Data[token]);
                }
            }

            // Run found command and calulate result and print to stdout.
            if (ret)
            {
                int res = runCmd(cmd, vals);
                if (res != -1)
                {
                    std::cout << "<-- DataProcessor::decodeDataAsCmd [Result:" << res << "]" << std::endl;
                }
                else
                {
                    ret = false;
                }
            }
        }
    }

    return ret;
}

// Private methods.

// Method to run parsed cmd and calulate result.
// Always check to avoid zero divsion.
int DataProcessor::runCmd(const std::string& cmd, const std::vector<int>& vals)
{
    int ret = -1;
    int total = 0;

    // average.
    if (cmd.compare(s_commands) == 0 && vals.size() > 1)
    {
        for (unsigned int i = 0; i < vals.size(); ++i)
        {
            total = total + vals[i];
        }
        ret = total / vals.size()-1;
    }

    return ret;
}

// Takes a string in input and makes sure only int is produced in output, on error
// -1 will be returned.
int DataProcessor::string2Int(const std::string& input)
{
    int ret = -1;

    try
    {
      if (input.size() > 0 && input.find_first_not_of("0123456789") == std::string::npos)
      {
          ret =  std::stoi(input);
      }
  }
  catch (...)
  {
      ret = -1;
  }

  return ret;
}
