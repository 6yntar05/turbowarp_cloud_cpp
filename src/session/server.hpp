#ifndef SERVER_HPP
#define SERVER_HPP

#include "standard_headers.hpp"
#include "listener.hpp"
#include "session.hpp"

namespace session {

    class server : public std::enable_shared_from_this<server> {

        ////// types
    public:
        struct config_t {
            tcp::endpoint endpoint;
            ssl::context &ssl_context;
        };

        ////// fields
    private:
        asio::io_context &ioc;
        std::shared_ptr<listener> _listener = nullptr;
        config_t config;

        ////// public methods
    public:
        server(asio::io_context &ioc, config_t config);

        void run();

        ////// inner methods
    private:
        listener::handlers listener_handlers();

        session::handlers session_handlers();
    };
} // session

#endif //SERVER_HPP
