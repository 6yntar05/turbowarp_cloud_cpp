#ifndef server_config_hpp
#define server_config_hpp

#include <cstdint>
#include <string>

namespace web_soket {
    /* Класс для хранения мета данных */
    /*
     * @param name: Название сервера (по приколу)
     * @param port: Используемый порт
     */
    class ServerConfig {
        public:
            ServerConfig(std::string name = "turbowarp_cloud", uint16_t port = 30001);

            /* Получение имени сервера */
            std::string& get_name();
            /* Получение порта сервера */
            uint16_t& get_port();

        private:
            std::string name;
            uint16_t port;
    };
}

#endif
