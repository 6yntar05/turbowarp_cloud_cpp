#include <cstdlib>
#include <iostream>
#include <spdlog/spdlog.h>

#include "utils/utils.h"
#include "session/test_main.hpp"

utils::ServerOptions options;

int main(int argc, char* argv[]) {
    spdlog::set_level(spdlog::level::debug);
    utils::parseCommandLine(argc, argv, options);
    
    spdlog::debug("Host: {}", options.host);
    spdlog::debug("Port: {}", options.port);
    spdlog::debug("Username: {}", options.username);
    spdlog::debug("Passowrd: {}", options.password);

    //minimal_vs();
    session::normal_ws();
    return 0;
}
