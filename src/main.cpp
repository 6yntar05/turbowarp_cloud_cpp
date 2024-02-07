#include <vector>

#include "CONAN_BUILD_TEST.h"

#include "web_socket/server_config.hpp"
#include "web_socket/server.hpp"

int main() {
    // Просто тесты сборки
    turbowarp_cloud_cpp();

    // Дальше приклюхи
    std::vector<std::string> vec;
    vec.push_back("test_package");

    turbowarp_cloud_cpp_print_vector(vec);

    // Boost::asio init
    boost::asio::io_context io_context(1);

    // Можно поменять имя и порт
    web_soket::ServerConfig server_config;
    web_soket::Server server(server_config);

    /* --- Инициализация сервера ---*/
    web_soket::turn_off_logging(server);

    bool is_success = true;

    if (is_success) {
        is_success = server.init();
    }

    web_soket::set_message_handler(server);
    web_soket::set_tls_init_handler(server);

    /* --- Запуск сервера ---*/
    if (is_success) {
        std::cout << server.get_config().get_name() << " server start on " <<
            server.get_config().get_port() << " port" << std::endl;

        is_success = server.run();
    }

    /* --- Вывод если Server::run выдал ошибку ---*/
    if (!is_success) {
        std::cout << server.get_config().get_name() <<
            " server aborting with errors" << std::endl;
    }
}
