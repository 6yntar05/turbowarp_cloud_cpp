#pragma once

#include <string>

namespace utils {

struct ServerOptions 
{
    std::string host;
    int port;
    std::string username;
    std::string password;
    std::string database;
};

void parseCommandLine(int argc, char* argv[], ServerOptions& options);

} // namespace utils
