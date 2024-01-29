#include "CONAN_BUILD_TEST.h"
#include <vector>
#include <string>
#include <boost/asio/io_context.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

// Объявление функции on_open
void on_open(websocketpp::connection_hdl hdl) {
    // Действия при открытии соединения
    std::cout << "Connection opened" << std::endl;
}

int main() {
    turbowarp_cloud_cpp();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    turbowarp_cloud_cpp_print_vector(vec);

    // Boost::asio init
    boost::asio::io_context io_context(1);

    // Пример использования WebSocket из websocketpp
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    using websocketpp::lib::bind;

    // Создаем endpoint
    websocketpp::client<websocketpp::config::asio_tls_client> client;

    // Устанавливаем обработчик соединения
    //client.set_open_handler(bind(&on_open, std::placeholders::_1));

    // Создаем объект соединения
    websocketpp::lib::error_code ec;
    //auto con = client.get_connection("ws://echo.websocket.org", ec);

    // Подключаемся
    //client.connect(con);

    // Запускаем цикл обработки
    //client.run();
}
