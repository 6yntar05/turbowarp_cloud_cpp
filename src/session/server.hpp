#ifndef SERVER_HPP
#define SERVER_HPP

#include "standart_headers.hpp"
#include "listener.hpp"
#include "session.hpp"

namespace session {

    class server : public std::enable_shared_from_this<server> {

        ////// types
    public:
        struct config_t {
            tcp::endpoint endpoint; // = {net::ip::make_address("..."), <port number>}
            ssl::context &ssl_context;
        };

        ////// fields
    private:
        asio::io_context &ioc;
        std::shared_ptr<listener> _listener = nullptr;
        config_t config;

        ////// public methods
    public:
        server(asio::io_context &ioc, config_t config) : ioc(ioc), config(std::move(config)) {}

        void run() {
            if (!_listener) {
                _listener = std::make_shared<listener>(ioc, config.endpoint, listener_handlers());
            }
            _listener->start();
        }

        ////// inner methods
    private:
        listener::handlers listener_handlers() {
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

        session::handlers session_handlers() {
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
    };
} // session

#endif //SERVER_HPP
