#include <iostream>
#include <web_socket/server_config.hpp>

#include "web_socket/server.hpp"

using namespace web_soket;

// Если не инициализировать config будет ошибка :с
/* --- Статическая инициалицая ---*/
WebsocketServer Server::websocket_server;
ServerConfig Server::config = ServerConfig();

bool Server::init(ServerConfig& server_config) {
    config = server_config;
    websocket_server.init_asio();

    return true;
}

bool Server::run() {
    try {
        websocket_server.listen(config.get_port());
    } catch(websocketpp::exception const &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    websocketpp::lib::error_code ec;
    websocket_server.start_accept(ec);
    if (ec) {
        std::cerr << ec.message() << std::endl;
        return false;
    }

    try {
        websocket_server.run();
    } catch(websocketpp::exception const &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}

// TODO
void Server::stop() {}

ServerConfig& Server::get_config() {
    return config;
}

void Server::turn_off_logging() {
    websocket_server.clear_access_channels(websocketpp::log::alevel::all);
    websocket_server.clear_error_channels(websocketpp::log::elevel::all);
}

void on_message(WebsocketServer* server, ConnectionHdl hdl,
                websocketpp::config::asio::message_type::ptr msg) {
    std::cout << "on_message: " << msg->get_payload() << std::endl;
    server->send(hdl, msg->get_payload(), websocketpp::frame::opcode::text);
}

void Server::set_message_handler() {
    websocket_server.set_message_handler(
        websocketpp::lib::bind(&on_message, &websocket_server, ::_1, ::_2));
}

websocketpp::lib::shared_ptr<SslContext> on_tls_init(ConnectionHdl hdl) {
    auto ctx = websocketpp::lib::make_shared<SslContext>(SslContext::sslv23);

    //ctx->use_certificate_chain_file("cert.pem");
    //ctx->use_private_key_file("key.pem", SslContext::pem);
    return ctx;
}

void Server::set_tls_init_handler() {
    websocket_server.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init, ::_1));
}
