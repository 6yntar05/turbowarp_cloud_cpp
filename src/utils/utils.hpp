#pragma once

#include <string>

namespace utils {

struct ServerOptions {
    // Websockets
    std::string wshost;
    int wsport;
    // Database
    std::string dbhost;
    int dbport;
    std::string dbusername;
    std::string dbpassword;
    std::string dbdatabase;
};

void parseCommandLine(int argc, char* argv[], ServerOptions& options);

}  // namespace utils
