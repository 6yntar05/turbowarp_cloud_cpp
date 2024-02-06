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

    /* --- Инициализация сервера ---*/
    web_soket::Server::turn_off_logging();

    bool is_success = true;

    if (is_success) {
        is_success = web_soket::Server::init(server_config);
    }

    web_soket::Server::set_message_handler();
    web_soket::Server::set_tls_init_handler();

    /* --- Запуск сервера ---*/
    if (is_success) {
        std::cout << web_soket::Server::get_config().get_name() << " server start on " <<
            web_soket::Server::get_config().get_port() << " port" << std::endl;

        is_success = web_soket::Server::run();
    }

    /* --- Вывод если Server::run выдал ошибку ---*/
    if (!is_success) {
        std::cout << web_soket::Server::get_config().get_name() <<
            " server aborting with errors" << std::endl;
    }
}
