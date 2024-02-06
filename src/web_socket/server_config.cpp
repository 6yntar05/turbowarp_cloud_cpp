#include "web_socket/server_config.hpp"

using namespace web_soket;

ServerConfig::ServerConfig(std::string name, uint16_t port) {
    this->name = name;
    this->port = port;
}

std::string& ServerConfig::get_name() {
    return this->name;
}

uint16_t& ServerConfig::get_port() {
    return this->port;
}
