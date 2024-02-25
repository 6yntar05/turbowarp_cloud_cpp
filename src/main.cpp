#include <spdlog/spdlog.h>

#include <cstdlib>
#include <memory>

#include "db/db.hpp"
#include "session/server.hpp"
#include "session/server_builder.hpp"
#include "session/standard_headers.hpp"
#include "session/turbowarp/methods.hpp"
#include "utils/utils.hpp"

int main(int argc, char* argv[]) {
    utils::ServerOptions options;

    spdlog::set_level(spdlog::level::debug);
    utils::parseCommandLine(argc, argv, options);
    {
        spdlog::debug("Server Host: {}", options.wshost);
        spdlog::debug("Server Port: {}", options.wsport);

        spdlog::debug("DBHost: {}", options.dbhost);
        spdlog::debug("DBPort: {}", options.dbport);
        spdlog::debug("DBUsername: {}", options.dbusername);
        spdlog::debug("DBPassowrd: {}", options.dbpassword);
    }

    std::unique_ptr<db::db> db_connection = std::make_unique<db::db>(
        db::backends::postgres, options.dbusername, options.dbpassword, options.dbdatabase,
        db::addr{options.dbhost, std::to_string(options.dbport)});
    db_connection->connect();   // pass to server
                                // and create write methods

    turbowarp::method::AvailableMethods::base_init();

    boost::asio::io_context io_context(1);
    session::server::server_ptr server = session::build_server(
        io_context,
        {asio::ip::make_address(options.wshost), boost::asio::ip::port_type(options.wsport)},
        "./cert", "./privkey");
    server->run();
    io_context.run();

    return 0;
}
