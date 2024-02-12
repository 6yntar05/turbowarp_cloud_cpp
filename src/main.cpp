#include <cstdlib>
#include <iostream>

#include "utils.h"

utils::ServerOptions options;

int main(int argc, char* argv[]) {
    utils::parseCommandLine(argc, argv, options);
    return 0;
}
