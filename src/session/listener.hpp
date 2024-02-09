#ifndef LISTENER
#define LISTENER

#include "standart_headers.hpp"

namespace session {
    class listener : public std::enable_shared_from_this<listener> {

        ////// types
    public:
        struct handlers {
            struct context {
                const shared_ptr<listener> &owner;
            };

            handler<context, std::tuple<tcp::socket>, std::tuple<const beast::error_code &>> on_accept = {
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

        explicit listener(asio::io_context &ioc, const tcp::endpoint &endpoint, handlers handlers)
                : ioc_(ioc), acceptor_(ioc, endpoint), endpoint_(endpoint),
                  handlers_(std::move(handlers)) {}

        void start() {
            if (!acceptor_.is_open()) {
                acceptor_.open(endpoint_.protocol());
            }

            do_accept();
        }

        void stop() {
            if (acceptor_.is_open()) {
                acceptor_.close();
            }
        }

        ////// inner methods
    private:

        void do_accept() {
            acceptor_.async_accept(
                    [self = shared_from_this()](const beast::error_code &ec, tcp::socket socket) {
                        if (ec == asio::error::operation_aborted) {
                            // when listener.stop()
                            return;
                        }
                        handlers::context context{self};

                        if (ec) {
                            self->handlers_.on_accept.failure(context, ec);
                            return;
                        }

                        self->handlers_.on_accept.success(context, std::move(socket));

                        self->do_accept();
                    });
        }

    };
};


#endif
