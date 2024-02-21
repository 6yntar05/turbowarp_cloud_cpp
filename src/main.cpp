#include <spdlog/spdlog.h>

#include <cstdlib>

#include "session/server.hpp"
#include "session/server_builder.hpp"
#include "session/standard_headers.hpp"
#include "utils/utils.hpp"

#include "session/turbowarp/api.hpp"

int main(int argc, char* argv[]) {
    // utils::ServerOptions options;

    // spdlog::set_level(spdlog::level::debug);
    // utils::parseCommandLine(argc, argv, options);
    // {
    //     spdlog::debug("Server Host: {}", options.wshost);
    //     spdlog::debug("Server Port: {}", options.wsport);

    //     spdlog::debug("DBHost: {}", options.dbhost);
    //     spdlog::debug("DBPort: {}", options.dbport);
    //     spdlog::debug("DBUsername: {}", options.dbusername);
    //     spdlog::debug("DBPassowrd: {}", options.dbpassword);
    // }

    // boost::asio::io_context io_context(1);
    // session::server::server_ptr server = session::build_server(
    //     io_context,
    //     {asio::ip::make_address(options.wshost), boost::asio::ip::port_type(options.wsport)},
    //     "./cert", "./privkey");
    // server->run();
    // io_context.run();

    boost::json::value jv = {
        {"method", "handshake"},
        {"project_id", "123"},
        {"user", "larinenok"}
    };

    std::cout << turbowarp::JsonParser::analize_data(boost::json::serialize(jv)) << std::endl;

    jv = {
        {"method", "set"},
        {"name", "123"},
        {"value", "larinenok"}
    };

    std::cout << turbowarp::JsonParser::analize_data(boost::json::serialize(jv)) << std::endl;

    jv = {
        {"method", "create"},
        {"name", "123"},
        {"value", "larinenok"}
    };

    std::cout << turbowarp::JsonParser::analize_data(boost::json::serialize(jv)) << std::endl;

    jv = {
        {"method", "rename"},
        {"name", "123"},
        {"new_name", "larinenok"}
    };

    std::cout << turbowarp::JsonParser::analize_data(boost::json::serialize(jv)) << std::endl;

    jv = {
        {"method", "delete"},
        {"name", "123"},
    };

    std::cout << turbowarp::JsonParser::analize_data(boost::json::serialize(jv)) << std::endl;

    return 0;
}
