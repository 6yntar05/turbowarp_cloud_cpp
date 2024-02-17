#include "session/server.hpp"

namespace session {

server::server(server::config_t config) : config(std::move(config)) {}

void server::run() {
    if (!_listener) {
        _listener =
            std::make_shared<listener>(config.io_context, config.endpoint, listener_handlers());
    }
    _listener->start();
}

listener::handlers server::listener_handlers() {
    return listener::handlers{
        .on_accept =
            decltype(listener::handlers::on_accept){
                .success =
                    [self = shared_from_this()](auto ctx, auto socket) {
                        spdlog::debug("tcp accept success");
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
        .on_accept =
            decltype(session::handlers::on_accept){
                .success = [](auto context) { context.owner->read(); },
                .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
            },

        .on_read =
            decltype(session::handlers::on_read){
                .success =
                    [](auto context, auto bytes_transferred, auto data) {
                        spdlog::debug("receive data: {}", data.data());
                        context.owner->send(data);
                    },
                .failure = default_handlers::just_say_arg<beast::error_code>("read error: "),
            },

        .on_write =
            decltype(session::handlers::on_write){
                .success =
                    [](auto context, auto bytes_transferred) {
                        spdlog::debug("sent data");
                        context.owner->read();
                    },
                .failure = default_handlers::just_say_arg<beast::error_code>("write error: "),
            },
    };
}

}  // namespace session