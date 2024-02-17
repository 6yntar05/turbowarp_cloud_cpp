#include "utils.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace utils {

void parseCommandLine(int argc, char* argv[], ServerOptions& options) {
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Produce help message")

        ("host,H", po::value<std::string>(&options.wshost)->default_value("0.0.0.0"), "Server host")
        ("port,P", po::value<int>(&options.wsport)->default_value(8080), "Server port")

        ("dbhost,d", po::value<std::string>(&options.dbhost)->default_value("127.0.0.1"), "Database host")
        ("dbport,t", po::value<int>(&options.dbport)->default_value(5432), "Database port")
        ("dbusername,u", po::value<std::string>(&options.dbusername)->default_value("postgres"), "Database username")
        ("dbpassword,p", po::value<std::string>(&options.dbpassword)->default_value(""), "Database password")
        ("dbname,n", po::value<std::string>(&options.dbdatabase)->default_value("postgres"), "Database name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        std::exit(0);
    }
}

}  // namespace utils
