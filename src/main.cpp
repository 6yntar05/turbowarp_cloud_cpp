#include <vector>

#include "CONAN_BUILD_TEST.h"

// #include "web_socket/server_config.hpp"
// #include "web_socket/server.hpp"

#include "web_socket/server_beast.hpp"
// #include "web_socket/test.hpp"
#include "web_socket/test.hpp"

int main() {
    // Просто тесты сборки
    turbowarp_cloud_cpp();

    // Дальше приклюхи
    std::vector<std::string> vec;
    vec.push_back("test_package");

    turbowarp_cloud_cpp_print_vector(vec);

    // Boost::asio init
    // boost::asio::io_context io_context(1);

    // Можно поменять имя и порт
    // web_soket::ServerConfig server_config;
    // web_soket::Server server(server_config);
    //
    // /* --- Инициализация сервера ---*/
    // // web_soket::turn_off_logging(server);
    //
    // bool is_success = true;
    //
    // if (is_success) {
    //     is_success = server.init();
    // }
    //
    // web_soket::set_message_handler(server);
    // web_soket::set_tls_init_handler(server);
    //
    // /* --- Запуск сервера ---*/
    // if (is_success) {
    //     std::cout << server.get_config().get_name() << " server start on " <<
    //         server.get_config().get_port() << " port" << std::endl;
    //
    //     is_success = server.run();
    // }
    //
    // /* --- Вывод если Server::run выдал ошибку ---*/
    // if (!is_success) {
    //     std::cout << server.get_config().get_name() <<
    //         " server aborting with errors" << std::endl;
    // }

    auto const address = net::ip::make_address("0.0.0.0");
    auto const port = 30001;
    auto const threads = 4;

    // The io_context is required for all I/O
    net::io_context ioc{ threads };

    net::ssl::context ctx(net::ssl::context::tlsv13);
    load_server_certificate(ctx);

    // Create and launch a listening port
    std::make_shared<web_socket::listener>(ioc, tcp::endpoint{ address, port }, ctx)->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for (auto i = threads - 1; i > 0; --i) {
        v.emplace_back(
            [&ioc] {
                ioc.run();
            });
    }
    ioc.run();

    return EXIT_SUCCESS;
}
