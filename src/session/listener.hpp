#pragma once

#include "session/standard_headers.hpp"

namespace session {

class listener : public std::enable_shared_from_this<listener> {
    ////// types
public:
    struct handlers {
        struct context {
            const shared_ptr<listener> &owner;
        };

        handler<context, std::tuple<tcp::socket>, std::tuple<const beast::error_code &>> on_accept =
            {
                .success = default_handlers::just_say("accept success"),
                .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
            };
    };

    ////// fields
private:
    asio::io_context &ioc_;
    tcp::endpoint endpoint_;
    tcp::acceptor acceptor_;
    handlers handlers_;

    ////// public methods
public:
    explicit listener(asio::io_context &ioc, const tcp::endpoint &endpoint, handlers handlers);

    void start();

    void stop();

    ////// inner methods
private:
    void do_accept();
};

};  // namespace session
