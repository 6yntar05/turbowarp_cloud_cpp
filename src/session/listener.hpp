#ifndef LISTENER
#define LISTENER

#include "standart_headers.hpp"

namespace session
{
    class listener : public std::enable_shared_from_this<listener> {

        ////// types
    public:
        struct handlers {
            struct context {
                const shared_ptr<listener> owner;
            };

            handler<context, std::tuple<tcp::socket>, std::tuple<const beast::error_code&>> on_accept = {
                .success = default_handlers::just_say("accept success"),
                .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
            };
        };

        ////// fields
    private:
        asio::io_context& _ioc;
        tcp::endpoint _endpoint;
        tcp::acceptor _acceptor;
        handlers _handlers;

        ////// public methods
    public:

        explicit listener(asio::io_context& ioc, const tcp::endpoint& endpoint, handlers handlers)
            : _ioc(ioc), _acceptor(ioc, endpoint), _endpoint(endpoint),
              _handlers(std::move(handlers)) {}

        void start() {
            if (!_acceptor.is_open()) {
                _acceptor.open(_endpoint.protocol());
            }

            do_accept();
        }

        void stop() {
            if (_acceptor.is_open()) {
                _acceptor.close();
            }
        }

        ////// inner methods
    private:

        void do_accept() {
            _acceptor.async_accept(
                [self = shared_from_this()](const beast::error_code& ec, tcp::socket socket) {
                    if (ec == asio::error::operation_aborted) {
                        // when listener.stop()
                        return;
                    }
                    handlers::context context{self};

                    if (ec) {
                        self->_handlers.on_accept.failure(context, ec);
                        return;
                    }

                    self->_handlers.on_accept.success(context, std::move(socket));

                    self->do_accept();
                });
        }

    };
};


#endif
