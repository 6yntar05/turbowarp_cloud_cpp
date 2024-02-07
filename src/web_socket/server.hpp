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

    /* Класс для работы с WebSocket */
    /*
     * @param server_config: ServerConfig, смотри инфу в классе
     * @param web_soket: хранения вебсокета
     * 
     * --- Использование в коде ---
     *
     * Для работы сервера последовательно выполните:
     * web_soket::ServerConfig server_config("name", 25565);
     * web_soket::Server server(server_config);
     *
     * (Не обязательно) web_soket::turn_off_logging(server);
     *
     * server.init();
     *
     * (Не обязательно) web_soket::set_message_handler(server);
     * web_soket::set_tls_init_handler(server);
     *
     * server.run();
     */
    class Server {
        public:
            Server(ServerConfig& config);

            /* Инициализация сервера */
            /*
             * Устанавливает ServerConfig
             * Запускает init_asio
             */
            // bool init(ServerConfig& config);
            bool init();

            /* Запуск сервера */
            /*
             * Запускает listen, start_acept, run по очереди
             * listen использует порт, заданный в ServerConfig
             * Возвращает bool - успешность запуска сервера,
             * при ошибке вернет false
             */
            bool run();

            /* Остановка сервера */
            /*
             * TODO
             */
            void stop();

            WebsocketServer& get_websoket_server();

            /* Получение ServerConfig */
            ServerConfig& get_config();

        private:
            static WebsocketServer websocket_server;
            ServerConfig config;
    };

    /* Выключение стандартного вывода мб */
    void turn_off_logging(Server& server);
    /* Вывод сообщений в кастомную функцию */
    void set_message_handler(Server& server);
    /* Подключение tls */
    void set_tls_init_handler(Server& server);
}

#endif
