#include <cstdlib>
#include <iostream>

#include "utils/utils.h"

utils::ServerOptions options;

int main(int argc, char* argv[]) {
    utils::parseCommandLine(argc, argv, options);
    std::cout << "Host:" << options.host << std::endl;
    std::cout << "Port:" << options.port << std::endl;
    std::cout << "Username:" << options.username << std::endl;
    std::cout << "Passowrd:" << options.password << std::endl;
    return 0;
}
