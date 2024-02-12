#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace utils {

struct ServerOptions 
{
    std::string host;
    int port;
    std::string username;
    std::string password;
};

void parseCommandLine(int argc, char* argv[], ServerOptions& options);

} // namespace utils

#endif // UTILS_HPP
