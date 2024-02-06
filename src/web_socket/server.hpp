#ifndef server_hpp
#define server_hpp

#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>

#include "web_socket/server_config.hpp"

namespace web_soket {
    using WebsocketServer = websocketpp::server<websocketpp::config::asio_tls>;
    using ConnectionHdl = websocketpp::connection_hdl;
    using SslContext = websocketpp::lib::asio::ssl::context;
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;

    /* Класс для работы с WevSocket */
    /*
     * @param server_config: ServerConfig, смотри инфу в классе
     * @param web_soket: хранения вебсокета
     */
    class Server {
        public:
            /* Инициализация сервера */
            /*
             * Устанавливает ServerConfig
             * Запускает init_asio
             */
            static bool init(ServerConfig& config);

            /* Запуск сервера */
            /*
             * Запускает listen, start_acept, run по очереди
             * listen использует порт, заданный в ServerConfig
             * Возвращает bool - успешность запуска сервера,
             * при ошибке вернет false
             */
            static bool run();

            /* Остановка сервера */
            /*
             * TODO
             */
            static void stop();

            /* Выключение стандартного вывода мб */
            static void turn_off_logging();
            /* Вывод сообщений в кастомную функцию */
            static void set_message_handler();
            /* Подключение tls */
            static void set_tls_init_handler();

            /* Получение ServerConfig */
            static ServerConfig& get_config();

        private:
            static WebsocketServer websocket_server;
            static ServerConfig config;
    };
}

#endif
