#include <iostream>
#include <boost/program_options.hpp>
#include "utils.h"

namespace utils {

void parseCommandLine(int argc, char* argv[], ServerOptions& options) {

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message")
        ("host,H", po::value<std::string>(&options.host)->default_value("127.0.0.1"), "Server host")
        ("port,p", po::value<int>(&options.port)->default_value(12309), "Server port")
        ("username,u", po::value<std::string>(&options.username)->default_value("postgres"), "Database username")
        ("password,P", po::value<std::string>(&options.password)->default_value(""), "Database password");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        std::exit(0);
    }
}

} // namespace utils
