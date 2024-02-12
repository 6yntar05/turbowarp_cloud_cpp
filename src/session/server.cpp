#include "server.hpp"

namespace session {

    server::server(asio::io_context &ioc, server::config_t config) : ioc(ioc), config(std::move(config)) {}

    void server::run() {
        if (!_listener) {
            _listener = std::make_shared<listener>(ioc, config.endpoint, listener_handlers());
        }
        _listener->start();
    }

    listener::handlers server::listener_handlers() {
        return listener::handlers{
                .on_accept = decltype(listener::handlers::on_accept){
                        .success = [self = shared_from_this()](auto ctx, auto socket) {
                            std::cout << "tcp accept success" << std::endl;
                            make_shared<session>(std::move(socket), self->config.ssl_context,
                                                 self->session_handlers())
                                    ->handshake();
                        },
                        .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
                },
        };
    }

    session::handlers server::session_handlers() {
        return session::handlers{
                .on_accept = decltype(session::handlers::on_accept){
                        .success = [](auto context) {
                            context.owner->read();
                        },
                        .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
                },

                .on_read = decltype(session::handlers::on_read){
                        .success = [](auto context, auto bytes_transferred, auto data) {
                            std::cout << "receive data" << std::endl;
                            context.owner->read();
                        },
                        .failure = default_handlers::just_say_arg<beast::error_code>("read error: "),
                }
        };
    }
}